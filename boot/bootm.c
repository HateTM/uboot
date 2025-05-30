// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

#ifndef USE_HOSTCC
#include <common.h>
#include <bootstage.h>
#include <cli.h>
#include <cpu_func.h>
#include <env.h>
#include <errno.h>
#include <fdt_support.h>
#include <irq_func.h>
#include <lmb.h>
#include <log.h>
#include <malloc.h>
#include <mapmem.h>
#include <net.h>
#include <asm/cache.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <linux/sizes.h>
#if defined(CONFIG_CMD_USB)
#include <usb.h>
#endif
#else
#include "mkimage.h"
#endif

#include <command.h>
#include <bootm.h>
#include <image.h>

#ifndef CONFIG_SYS_BOOTM_LEN
/* use 8MByte as default max gunzip size */
#define CONFIG_SYS_BOOTM_LEN	0x800000
#endif

#define MAX_CMDLINE_SIZE	SZ_4K

#define IH_INITRD_ARCH IH_ARCH_DEFAULT

#ifndef USE_HOSTCC

DECLARE_GLOBAL_DATA_PTR;

bootm_headers_t images;		/* pointers to os/initrd/fdt images */

static const void *boot_get_kernel(struct cmd_tbl *cmdtp, int flag, int argc,
				   char *const argv[], bootm_headers_t *images,
				   ulong *os_data, ulong *os_len);

__weak void board_quiesce_devices(void)
{
}

__weak int mtk_ar_update_fw_ar_ver(uint32_t fw_ar_ver)
{
	return 0;
}

#ifdef CONFIG_LMB
static void boot_start_lmb(bootm_headers_t *images)
{
	ulong		mem_start;
	phys_size_t	mem_size;

	mem_start = env_get_bootm_low();
	mem_size = env_get_bootm_size();

	lmb_init_and_reserve_range(&images->lmb, (phys_addr_t)mem_start,
				   mem_size, NULL);
}
#else
#define lmb_reserve(lmb, base, size)
static inline void boot_start_lmb(bootm_headers_t *images) { }
#endif

static int bootm_start(struct cmd_tbl *cmdtp, int flag, int argc,
		       char *const argv[])
{
	memset((void *)&images, 0, sizeof(images));
	images.verify = env_get_yesno("verify");

	boot_start_lmb(&images);

	bootstage_mark_name(BOOTSTAGE_ID_BOOTM_START, "bootm_start");
	images.state = BOOTM_STATE_START;

	return 0;
}

static int bootm_find_os(struct cmd_tbl *cmdtp, int flag, int argc,
			 char *const argv[])
{
	const void *os_hdr;
	bool ep_found = false;
	int ret;

	/* get kernel image header, start address and length */
	os_hdr = boot_get_kernel(cmdtp, flag, argc, argv,
			&images, &images.os.image_start, &images.os.image_len);
	if (images.os.image_len == 0) {
		puts("ERROR: can't get kernel image!\n");
		return 1;
	}

	/* get image parameters */
	switch (genimg_get_format(os_hdr)) {
#if CONFIG_IS_ENABLED(LEGACY_IMAGE_FORMAT)
	case IMAGE_FORMAT_LEGACY:
		images.os.type = image_get_type(os_hdr);
		images.os.comp = image_get_comp(os_hdr);
		images.os.os = image_get_os(os_hdr);

		images.os.end = image_get_image_end(os_hdr);
		images.os.load = image_get_load(os_hdr);
		images.os.arch = image_get_arch(os_hdr);
		if(images.os.type == IH_TYPE_STANDALONE)
		{
			//printf("when type is standlone, then set os to uboot\n");
			images.os.os = IH_OS_U_BOOT;
		}
		break;
#endif
#if CONFIG_IS_ENABLED(FIT)
	case IMAGE_FORMAT_FIT:
		if (fit_image_get_type(images.fit_hdr_os,
				       images.fit_noffset_os,
				       &images.os.type)) {
			puts("Can't get image type!\n");
			bootstage_error(BOOTSTAGE_ID_FIT_TYPE);
			return 1;
		}

		if (fit_image_get_comp(images.fit_hdr_os,
				       images.fit_noffset_os,
				       &images.os.comp)) {
			puts("Can't get image compression!\n");
			bootstage_error(BOOTSTAGE_ID_FIT_COMPRESSION);
			return 1;
		}

		if (fit_image_get_os(images.fit_hdr_os, images.fit_noffset_os,
				     &images.os.os)) {
			puts("Can't get image OS!\n");
			bootstage_error(BOOTSTAGE_ID_FIT_OS);
			return 1;
		}

		if (fit_image_get_arch(images.fit_hdr_os,
				       images.fit_noffset_os,
				       &images.os.arch)) {
			puts("Can't get image ARCH!\n");
			return 1;
		}

		images.os.end = fit_get_end(images.fit_hdr_os);

		if (fit_image_get_load(images.fit_hdr_os, images.fit_noffset_os,
				       &images.os.load)) {
			puts("Can't get image load address!\n");
			bootstage_error(BOOTSTAGE_ID_FIT_LOADADDR);
			return 1;
		}
		break;
#endif
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	case IMAGE_FORMAT_ANDROID:
		images.os.type = IH_TYPE_KERNEL;
		images.os.comp = android_image_get_kcomp(os_hdr);
		images.os.os = IH_OS_LINUX;

		images.os.end = android_image_get_end(os_hdr);
		images.os.load = android_image_get_kload(os_hdr);
		images.ep = images.os.load;
		ep_found = true;
		break;
#endif
	default:
		puts("ERROR: unknown image format type!\n");
		return 1;
	}

	/* If we have a valid setup.bin, we will use that for entry (x86) */
	if (images.os.arch == IH_ARCH_I386 ||
	    images.os.arch == IH_ARCH_X86_64) {
		ulong len;

		ret = boot_get_setup(&images, IH_ARCH_I386, &images.ep, &len);
		if (ret < 0 && ret != -ENOENT) {
			puts("Could not find a valid setup.bin for x86\n");
			return 1;
		}
		/* Kernel entry point is the setup.bin */
	} else if (images.legacy_hdr_valid) {
		images.ep = image_get_ep(&images.legacy_hdr_os_copy);
#if CONFIG_IS_ENABLED(FIT)
	} else if (images.fit_uname_os) {
		int ret;

		ret = fit_image_get_entry(images.fit_hdr_os,
					  images.fit_noffset_os, &images.ep);
		if (ret) {
			puts("Can't get entry point property!\n");
			return 1;
		}
#endif
	} else if (!ep_found) {
		puts("Could not find kernel entry point!\n");
		return 1;
	}

	if (images.os.type == IH_TYPE_KERNEL_NOLOAD) {
		if (CONFIG_IS_ENABLED(CMD_BOOTI) &&
		    images.os.arch == IH_ARCH_ARM64) {
			ulong image_addr;
			ulong image_size;

			ret = booti_setup(images.os.image_start, &image_addr,
					  &image_size, true);
			if (ret != 0)
				return 1;

			images.os.type = IH_TYPE_KERNEL;
			images.os.load = image_addr;
			images.ep = image_addr;
		} else {
			images.os.load = images.os.image_start;
			images.ep += images.os.image_start;
		}
	}

	images.os.start = map_to_sysmem(os_hdr);

	return 0;
}

/**
 * bootm_find_images - wrapper to find and locate various images
 * @flag: Ignored Argument
 * @argc: command argument count
 * @argv: command argument list
 * @start: OS image start address
 * @size: OS image size
 *
 * boot_find_images() will attempt to load an available ramdisk,
 * flattened device tree, as well as specifically marked
 * "loadable" images (loadables are FIT only)
 *
 * Note: bootm_find_images will skip an image if it is not found
 *
 * @return:
 *     0, if all existing images were loaded correctly
 *     1, if an image is found but corrupted, or invalid
 */
int bootm_find_images(int flag, int argc, char *const argv[], ulong start,
		      ulong size)
{
	int ret;

	/* find ramdisk */
	ret = boot_get_ramdisk(argc, argv, &images, IH_INITRD_ARCH,
			       &images.rd_start, &images.rd_end);
	if (ret) {
		puts("Ramdisk image is corrupt or invalid\n");
		return 1;
	}

	/* check if ramdisk overlaps OS image */
	if (images.rd_start && (((ulong)images.rd_start >= start &&
				 (ulong)images.rd_start < start + size) ||
				((ulong)images.rd_end > start &&
				 (ulong)images.rd_end <= start + size) ||
				((ulong)images.rd_start < start &&
				 (ulong)images.rd_end >= start + size))) {
		printf("ERROR: RD image overlaps OS image (OS=0x%lx..0x%lx)\n",
		       start, start + size);
		return 1;
	}

#if CONFIG_IS_ENABLED(OF_LIBFDT)
	/* find flattened device tree */
	ret = boot_get_fdt(flag, argc, argv, IH_ARCH_DEFAULT, &images,
			   &images.ft_addr, &images.ft_len);
	if (ret) {
		puts("Could not find a valid device tree\n");
		return 1;
	}

	/* check if FDT overlaps OS image */
	if (images.ft_addr &&
	    (((ulong)images.ft_addr >= start &&
	      (ulong)images.ft_addr <= start + size) ||
	     ((ulong)images.ft_addr + images.ft_len >= start &&
	      (ulong)images.ft_addr + images.ft_len <= start + size))) {
		printf("ERROR: FDT image overlaps OS image (OS=0x%lx..0x%lx)\n",
		       start, start + size);
		return 1;
	}

	if (CONFIG_IS_ENABLED(CMD_FDT))
		set_working_fdt_addr(map_to_sysmem(images.ft_addr));
#endif

#if CONFIG_IS_ENABLED(FIT)
	if (IS_ENABLED(CONFIG_FPGA)) {
		/* find bitstreams */
		ret = boot_get_fpga(argc, argv, &images, IH_ARCH_DEFAULT,
				    NULL, NULL);
		if (ret) {
			printf("FPGA image is corrupted or invalid\n");
			return 1;
		}
	}

	/* find all of the loadables */
	ret = boot_get_loadable(argc, argv, &images, IH_ARCH_DEFAULT,
			       NULL, NULL);
	if (ret) {
		printf("Loadable(s) is corrupt or invalid\n");
		return 1;
	}
#endif

	return 0;
}

static int bootm_find_other(struct cmd_tbl *cmdtp, int flag, int argc,
			    char *const argv[])
{
	if (((images.os.type == IH_TYPE_KERNEL) ||
	     (images.os.type == IH_TYPE_KERNEL_NOLOAD) ||
	     (images.os.type == IH_TYPE_MULTI)) &&
	    (images.os.os == IH_OS_LINUX ||
		 images.os.os == IH_OS_VXWORKS))
		return bootm_find_images(flag, argc, argv, 0, 0);

	return 0;
}
#endif /* USE_HOSTC */

#if !defined(USE_HOSTCC) || defined(CONFIG_FIT_SIGNATURE)
/**
 * handle_decomp_error() - display a decompression error
 *
 * This function tries to produce a useful message. In the case where the
 * uncompressed size is the same as the available space, we can assume that
 * the image is too large for the buffer.
 *
 * @comp_type:		Compression type being used (IH_COMP_...)
 * @uncomp_size:	Number of bytes uncompressed
 * @ret:		errno error code received from compression library
 * @return Appropriate BOOTM_ERR_ error code
 */
static int handle_decomp_error(int comp_type, size_t uncomp_size, int ret)
{
	const char *name = genimg_get_comp_name(comp_type);

	/* ENOSYS means unimplemented compression type, don't reset. */
	if (ret == -ENOSYS)
		return BOOTM_ERR_UNIMPLEMENTED;

	if (uncomp_size >= CONFIG_SYS_BOOTM_LEN)
		printf("Image too large: increase CONFIG_SYS_BOOTM_LEN\n");
	else
		printf("%s: uncompress error %d\n", name, ret);

	/*
	 * The decompression routines are now safe, so will not write beyond
	 * their bounds. Probably it is not necessary to reset, but maintain
	 * the current behaviour for now.
	 */
	printf("Must RESET board to recover\n");
#ifndef USE_HOSTCC
	bootstage_error(BOOTSTAGE_ID_DECOMP_IMAGE);
#endif

	return BOOTM_ERR_RESET;
}
#endif

#ifndef USE_HOSTCC
static int bootm_load_os(bootm_headers_t *images, int boot_progress)
{
	image_info_t os = images->os;
	ulong load = os.load;
	ulong load_end;
	ulong blob_start = os.start;
	ulong blob_end = os.end;
	ulong image_start = os.image_start;
	ulong image_len = os.image_len;
	ulong flush_start = ALIGN_DOWN(load, ARCH_DMA_MINALIGN);
	bool no_overlap;
	void *load_buf, *image_buf;
	int err;

	load_buf = map_sysmem(load, 0);
	image_buf = map_sysmem(os.image_start, image_len);
	err = image_decomp(os.comp, load, os.image_start, os.type,
			   load_buf, image_buf, image_len,
			   CONFIG_SYS_BOOTM_LEN, &load_end);
	if (err) {
		err = handle_decomp_error(os.comp, load_end - load, err);
		bootstage_error(BOOTSTAGE_ID_DECOMP_IMAGE);
		return err;
	}
	/* We need the decompressed image size in the next steps */
	images->os.image_len = load_end - load;

	flush_cache(flush_start, ALIGN(load_end, ARCH_DMA_MINALIGN) - flush_start);

	debug("   kernel loaded at 0x%08lx, end = 0x%08lx\n", load, load_end);
	bootstage_mark(BOOTSTAGE_ID_KERNEL_LOADED);

	no_overlap = (os.comp == IH_COMP_NONE && load == image_start);

	if (!no_overlap && load < blob_end && load_end > blob_start) {
		debug("images.os.start = 0x%lX, images.os.end = 0x%lx\n",
		      blob_start, blob_end);
		debug("images.os.load = 0x%lx, load_end = 0x%lx\n", load,
		      load_end);

		/* Check what type of image this is. */
		if (images->legacy_hdr_valid) {
			if (image_get_type(&images->legacy_hdr_os_copy)
					== IH_TYPE_MULTI)
				puts("WARNING: legacy format multi component image overwritten\n");
			return BOOTM_ERR_OVERLAP;
		} else {
			puts("ERROR: new format image overwritten - must RESET the board to recover\n");
			bootstage_error(BOOTSTAGE_ID_OVERWRITTEN);
			return BOOTM_ERR_RESET;
		}
	}

	lmb_reserve(&images->lmb, images->os.load, (load_end -
						    images->os.load));
	return 0;
}

/**
 * bootm_disable_interrupts() - Disable interrupts in preparation for load/boot
 *
 * @return interrupt flag (0 if interrupts were disabled, non-zero if they were
 *	enabled)
 */
ulong bootm_disable_interrupts(void)
{
	ulong iflag;

	/*
	 * We have reached the point of no return: we are going to
	 * overwrite all exception vector code, so we cannot easily
	 * recover from any failures any more...
	 */
	iflag = disable_interrupts();
#ifdef CONFIG_NETCONSOLE
	/* Stop the ethernet stack if NetConsole could have left it up */
	eth_halt();
# ifndef CONFIG_DM_ETH
	eth_unregister(eth_get_dev());
# endif
#endif

#if defined(CONFIG_CMD_USB)
	/*
	 * turn off USB to prevent the host controller from writing to the
	 * SDRAM while Linux is booting. This could happen (at least for OHCI
	 * controller), because the HCCA (Host Controller Communication Area)
	 * lies within the SDRAM and the host controller writes continously to
	 * this area (as busmaster!). The HccaFrameNumber is for example
	 * updated every 1 ms within the HCCA structure in SDRAM! For more
	 * details see the OpenHCI specification.
	 */
	usb_stop();
#endif
	return iflag;
}

#define CONSOLE_ARG		"console="
#define CONSOLE_ARG_SIZE	sizeof(CONSOLE_ARG)

/**
 * fixup_silent_linux() - Handle silencing the linux boot if required
 *
 * This uses the silent_linux envvar to control whether to add/set a "console="
 * parameter to the command line
 *
 * @buf: Buffer containing the string to process
 * @maxlen: Maximum length of buffer
 * @return 0 if OK, -ENOSPC if @maxlen is too small
 */
static int fixup_silent_linux(char *buf, int maxlen)
{
	int want_silent;
	char *cmdline;
	int size;

	/*
	 * Move the input string to the end of buffer. The output string will be
	 * built up at the start.
	 */
	size = strlen(buf) + 1;
	if (size * 2 > maxlen)
		return -ENOSPC;
	cmdline = buf + maxlen - size;
	memmove(cmdline, buf, size);
	/*
	 * Only fix cmdline when requested. The environment variable can be:
	 *
	 *	no - we never fixup
	 *	yes - we always fixup
	 *	unset - we rely on the console silent flag
	 */
	want_silent = env_get_yesno("silent_linux");
	if (want_silent == 0)
		return 0;
	else if (want_silent == -1 && !(gd->flags & GD_FLG_SILENT))
		return 0;

	debug("before silent fix-up: %s\n", cmdline);
	if (*cmdline) {
		char *start = strstr(cmdline, CONSOLE_ARG);

		/* Check space for maximum possible new command line */
		if (size + CONSOLE_ARG_SIZE > maxlen)
			return -ENOSPC;

		if (start) {
			char *end = strchr(start, ' ');
			int start_bytes;

			start_bytes = start - cmdline + CONSOLE_ARG_SIZE - 1;
			strncpy(buf, cmdline, start_bytes);
			if (end)
				strcpy(buf + start_bytes, end);
			else
				buf[start_bytes] = '\0';
		} else {
			sprintf(buf, "%s %s", cmdline, CONSOLE_ARG);
		}
		if (buf + strlen(buf) >= cmdline)
			return -ENOSPC;
	} else {
		if (maxlen < sizeof(CONSOLE_ARG))
			return -ENOSPC;
		strcpy(buf, CONSOLE_ARG);
	}
	debug("after silent fix-up: %s\n", buf);

	return 0;
}

/**
 * process_subst() - Handle substitution of ${...} fields in the environment
 *
 * Handle variable substitution in the provided buffer
 *
 * @buf: Buffer containing the string to process
 * @maxlen: Maximum length of buffer
 * @return 0 if OK, -ENOSPC if @maxlen is too small
 */
static int process_subst(char *buf, int maxlen)
{
	char *cmdline;
	int size;
	int ret;

	/* Move to end of buffer */
	size = strlen(buf) + 1;
	cmdline = buf + maxlen - size;
	if (buf + size > cmdline)
		return -ENOSPC;
	memmove(cmdline, buf, size);

	ret = cli_simple_process_macros(cmdline, buf, cmdline - buf);

	return ret;
}

int bootm_process_cmdline(char *buf, int maxlen, int flags)
{
	int ret;

	/* Check config first to enable compiler to eliminate code */
	if (IS_ENABLED(CONFIG_SILENT_CONSOLE) &&
	    !IS_ENABLED(CONFIG_SILENT_U_BOOT_ONLY) &&
	    (flags & BOOTM_CL_SILENT)) {
		ret = fixup_silent_linux(buf, maxlen);
		if (ret)
			return log_msg_ret("silent", ret);
	}
	if (IS_ENABLED(CONFIG_BOOTARGS_SUBST) && IS_ENABLED(CONFIG_CMDLINE) &&
	    (flags & BOOTM_CL_SUBST)) {
		ret = process_subst(buf, maxlen);
		if (ret)
			return log_msg_ret("subst", ret);
	}

	return 0;
}

int bootm_process_cmdline_env(int flags)
{
	const int maxlen = MAX_CMDLINE_SIZE;
	bool do_silent;
	const char *env;
	char *buf;
	int ret;

	/* First check if any action is needed */
	do_silent = IS_ENABLED(CONFIG_SILENT_CONSOLE) &&
	    !IS_ENABLED(CONFIG_SILENT_U_BOOT_ONLY) && (flags & BOOTM_CL_SILENT);
	if (!do_silent && !IS_ENABLED(CONFIG_BOOTARGS_SUBST))
		return 0;

	env = env_get("bootargs");
	if (env && strlen(env) >= maxlen)
		return -E2BIG;
	buf = malloc(maxlen);
	if (!buf)
		return -ENOMEM;
	if (env)
		strcpy(buf, env);
	else
		*buf = '\0';
	ret = bootm_process_cmdline(buf, maxlen, flags);
	if (!ret) {
		ret = env_set("bootargs", buf);

		/*
		 * If buf is "" and bootargs does not exist, this will produce
		 * an error trying to delete bootargs. Ignore it
		 */
		if (ret == -ENOENT)
			ret = 0;
	}
	free(buf);
	if (ret)
		return log_msg_ret("env", ret);

	return 0;
}

/**
 * Execute selected states of the bootm command.
 *
 * Note the arguments to this state must be the first argument, Any 'bootm'
 * or sub-command arguments must have already been taken.
 *
 * Note that if states contains more than one flag it MUST contain
 * BOOTM_STATE_START, since this handles and consumes the command line args.
 *
 * Also note that aside from boot_os_fn functions and bootm_load_os no other
 * functions we store the return value of in 'ret' may use a negative return
 * value, without special handling.
 *
 * @param cmdtp		Pointer to bootm command table entry
 * @param flag		Command flags (CMD_FLAG_...)
 * @param argc		Number of subcommand arguments (0 = no arguments)
 * @param argv		Arguments
 * @param states	Mask containing states to run (BOOTM_STATE_...)
 * @param images	Image header information
 * @param boot_progress 1 to show boot progress, 0 to not do this
 * @return 0 if ok, something else on error. Some errors will cause this
 *	function to perform a reboot! If states contains BOOTM_STATE_OS_GO
 *	then the intent is to boot an OS, so this function will not return
 *	unless the image type is standalone.
 */
int do_bootm_states(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[], int states, bootm_headers_t *images,
		    int boot_progress)
{
	boot_os_fn *boot_fn;
	ulong iflag = 0;
	int ret = 0, need_boot_fn;

	images->state |= states;

	/*
	 * Work through the states and see how far we get. We stop on
	 * any error.
	 */
	if (states & BOOTM_STATE_START)
		ret = bootm_start(cmdtp, flag, argc, argv);

	if (!ret && (states & BOOTM_STATE_FINDOS))
		ret = bootm_find_os(cmdtp, flag, argc, argv);

	if (!ret && (states & BOOTM_STATE_FINDOTHER))
		ret = bootm_find_other(cmdtp, flag, argc, argv);

	/* Load the OS */
	if (!ret && (states & BOOTM_STATE_LOADOS)) {
		iflag = bootm_disable_interrupts();
		ret = bootm_load_os(images, 0);
		if (ret && ret != BOOTM_ERR_OVERLAP)
			goto err;
		else if (ret == BOOTM_ERR_OVERLAP)
			ret = 0;
	}

	/* Relocate the ramdisk */
#ifdef CONFIG_SYS_BOOT_RAMDISK_HIGH
	if (!ret && (states & BOOTM_STATE_RAMDISK)) {
		ulong rd_len = images->rd_end - images->rd_start;

		ret = boot_ramdisk_high(&images->lmb, images->rd_start,
			rd_len, &images->initrd_start, &images->initrd_end);
		if (!ret) {
			env_set_hex("initrd_start", images->initrd_start);
			env_set_hex("initrd_end", images->initrd_end);
		}
	}
#endif
#if CONFIG_IS_ENABLED(OF_LIBFDT) && defined(CONFIG_LMB)
	if (!ret && (states & BOOTM_STATE_FDT)) {
		boot_fdt_add_mem_rsv_regions(&images->lmb, images->ft_addr);
		ret = boot_relocate_fdt(&images->lmb, &images->ft_addr,
					&images->ft_len);
	}
#endif

	/* From now on, we need the OS boot function */
	if (ret)
		return ret;
	//printf("jiang images->os.os = %d\n", images->os.os);
	boot_fn = bootm_os_get_boot_func(images->os.os);
	need_boot_fn = states & (BOOTM_STATE_OS_CMDLINE |
			BOOTM_STATE_OS_BD_T | BOOTM_STATE_OS_PREP |
			BOOTM_STATE_OS_FAKE_GO | BOOTM_STATE_OS_GO);
	if (boot_fn == NULL && need_boot_fn) {
		if (iflag)
			enable_interrupts();
		printf("ERROR: booting os '%s' (%d) is not supported\n",
		       genimg_get_os_name(images->os.os), images->os.os);
		bootstage_error(BOOTSTAGE_ID_CHECK_BOOT_OS);
		return 1;
	}


	/* Call various other states that are not generally used */
	if (!ret && (states & BOOTM_STATE_OS_CMDLINE))
		ret = boot_fn(BOOTM_STATE_OS_CMDLINE, argc, argv, images);
	if (!ret && (states & BOOTM_STATE_OS_BD_T))
		ret = boot_fn(BOOTM_STATE_OS_BD_T, argc, argv, images);
	if (!ret && (states & BOOTM_STATE_OS_PREP)) {
		ret = bootm_process_cmdline_env(images->os.os == IH_OS_LINUX);
		if (ret) {
			printf("Cmdline setup failed (err=%d)\n", ret);
			ret = CMD_RET_FAILURE;
			goto err;
		}
		ret = boot_fn(BOOTM_STATE_OS_PREP, argc, argv, images);
	}

#ifdef CONFIG_TRACE
	/* Pretend to run the OS, then run a user command */
	if (!ret && (states & BOOTM_STATE_OS_FAKE_GO)) {
		char *cmd_list = env_get("fakegocmd");

		ret = boot_selected_os(argc, argv, BOOTM_STATE_OS_FAKE_GO,
				images, boot_fn);
		if (!ret && cmd_list)
			ret = run_command_list(cmd_list, -1, flag);
	}
#endif

	/* Check for unsupported subcommand. */
	if (ret) {
		puts("subcommand not supported\n");
		return ret;
	}

	/* Update firmware anti-rollback version */
	if (!ret && (states & BOOTM_STATE_OS_GO))
		ret = mtk_ar_update_fw_ar_ver(images->fw_ar_ver);

	/* Now run the OS! We hope this doesn't return */
	if (!ret && (states & BOOTM_STATE_OS_GO))
		ret = boot_selected_os(argc, argv, BOOTM_STATE_OS_GO,
				images, boot_fn);

	/* Deal with any fallout */
err:
	if (iflag)
		enable_interrupts();

	if (ret == BOOTM_ERR_UNIMPLEMENTED)
		bootstage_error(BOOTSTAGE_ID_DECOMP_UNIMPL);
	else if (ret == BOOTM_ERR_RESET)
		do_reset(cmdtp, flag, argc, argv);

	return ret;
}

#if CONFIG_IS_ENABLED(LEGACY_IMAGE_FORMAT)
/**
 * image_get_kernel - verify legacy format kernel image
 * @img_addr: in RAM address of the legacy format image to be verified
 * @verify: data CRC verification flag
 *
 * image_get_kernel() verifies legacy image integrity and returns pointer to
 * legacy image header if image verification was completed successfully.
 *
 * returns:
 *     pointer to a legacy image header if valid image was found
 *     otherwise return NULL
 */
static image_header_t *image_get_kernel(ulong img_addr, int verify)
{
	image_header_t *hdr = (image_header_t *)img_addr;

	if (!image_check_magic(hdr)) {
		puts("Bad Magic Number\n");
		bootstage_error(BOOTSTAGE_ID_CHECK_MAGIC);
		return NULL;
	}
	bootstage_mark(BOOTSTAGE_ID_CHECK_HEADER);

	if (!image_check_hcrc(hdr)) {
		puts("Bad Header Checksum\n");
		bootstage_error(BOOTSTAGE_ID_CHECK_HEADER);
		return NULL;
	}

	bootstage_mark(BOOTSTAGE_ID_CHECK_CHECKSUM);
	image_print_contents(hdr);

	if (verify) {
		puts("   Verifying Checksum ... ");
		if (!image_check_dcrc(hdr)) {
			printf("Bad Data CRC\n");
			bootstage_error(BOOTSTAGE_ID_CHECK_CHECKSUM);
			return NULL;
		}
		puts("OK\n");
	}
	bootstage_mark(BOOTSTAGE_ID_CHECK_ARCH);

	if (!image_check_target_arch(hdr)) {
		printf("Unsupported Architecture 0x%x\n", image_get_arch(hdr));
		bootstage_error(BOOTSTAGE_ID_CHECK_ARCH);
		return NULL;
	}
	return hdr;
}
#endif

/**
 * boot_get_kernel - find kernel image
 * @os_data: pointer to a ulong variable, will hold os data start address
 * @os_len: pointer to a ulong variable, will hold os data length
 *
 * boot_get_kernel() tries to find a kernel image, verifies its integrity
 * and locates kernel data.
 *
 * returns:
 *     pointer to image header if valid image was found, plus kernel start
 *     address and length, otherwise NULL
 */
static const void *boot_get_kernel(struct cmd_tbl *cmdtp, int flag, int argc,
				   char *const argv[], bootm_headers_t *images,
				   ulong *os_data, ulong *os_len)
{
#if CONFIG_IS_ENABLED(LEGACY_IMAGE_FORMAT)
	image_header_t	*hdr;
#endif
	ulong		img_addr;
	const void *buf;
	const char	*fit_uname_config = NULL;
	const char	*fit_uname_kernel = NULL;
#if CONFIG_IS_ENABLED(FIT)
	int		os_noffset;
#endif

	img_addr = genimg_get_kernel_addr_fit(argc < 1 ? NULL : argv[0],
					      &fit_uname_config,
					      &fit_uname_kernel);

	bootstage_mark(BOOTSTAGE_ID_CHECK_MAGIC);

	/* check image type, for FIT images get FIT kernel node */
	*os_data = *os_len = 0;
	buf = map_sysmem(img_addr, 0);
	switch (genimg_get_format(buf)) {
#if CONFIG_IS_ENABLED(LEGACY_IMAGE_FORMAT)
	case IMAGE_FORMAT_LEGACY:
		printf("## Booting kernel from Legacy Image at %08lx ...\n",
		       img_addr);
		hdr = image_get_kernel(img_addr, images->verify);
		if (!hdr)
			return NULL;
		bootstage_mark(BOOTSTAGE_ID_CHECK_IMAGETYPE);

		/* get os_data and os_len */
		switch (image_get_type(hdr)) {
		case IH_TYPE_KERNEL:
		case IH_TYPE_KERNEL_NOLOAD:
			*os_data = image_get_data(hdr);
			*os_len = image_get_data_size(hdr);
			break;
		case IH_TYPE_MULTI:
			image_multi_getimg(hdr, 0, os_data, os_len);
			break;
		case IH_TYPE_STANDALONE:
			*os_data = image_get_data(hdr);
			*os_len = image_get_data_size(hdr);
			break;
		default:
			printf("Wrong Image Type for %s command\n",
			       cmdtp->name);
			bootstage_error(BOOTSTAGE_ID_CHECK_IMAGETYPE);
			return NULL;
		}

		/*
		 * copy image header to allow for image overwrites during
		 * kernel decompression.
		 */
		memmove(&images->legacy_hdr_os_copy, hdr,
			sizeof(image_header_t));

		/* save pointer to image header */
		images->legacy_hdr_os = hdr;

		images->legacy_hdr_valid = 1;
		bootstage_mark(BOOTSTAGE_ID_DECOMP_IMAGE);
		break;
#endif
#if CONFIG_IS_ENABLED(FIT)
	case IMAGE_FORMAT_FIT:
		os_noffset = fit_image_load(images, img_addr,
				&fit_uname_kernel, &fit_uname_config,
				IH_ARCH_DEFAULT, IH_TYPE_KERNEL,
				BOOTSTAGE_ID_FIT_KERNEL_START,
				FIT_LOAD_IGNORED, os_data, os_len);
		if (os_noffset < 0)
			return NULL;

		images->fit_hdr_os = map_sysmem(img_addr, 0);
		images->fit_uname_os = fit_uname_kernel;
		images->fit_uname_cfg = fit_uname_config;
		images->fit_noffset_os = os_noffset;
		break;
#endif
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	case IMAGE_FORMAT_ANDROID:
		printf("## Booting Android Image at 0x%08lx ...\n", img_addr);
		if (android_image_get_kernel(buf, images->verify,
					     os_data, os_len))
			return NULL;
		break;
#endif
	default:
		printf("Wrong Image Format for %s command\n", cmdtp->name);
		bootstage_error(BOOTSTAGE_ID_FIT_KERNEL_INFO);
		return NULL;
	}

	debug("   kernel data at 0x%08lx, len = 0x%08lx (%ld)\n",
	      *os_data, *os_len, *os_len);

	return buf;
}

/**
 * switch_to_non_secure_mode() - switch to non-secure mode
 *
 * This routine is overridden by architectures requiring this feature.
 */
void __weak switch_to_non_secure_mode(void)
{
}

#else /* USE_HOSTCC */

#if defined(CONFIG_FIT_SIGNATURE)
static int bootm_host_load_image(const void *fit, int req_image_type,
				 int cfg_noffset)
{
	const char *fit_uname_config = NULL;
	ulong data, len;
	bootm_headers_t images;
	int noffset;
	ulong load_end;
	uint8_t image_type;
	uint8_t imape_comp;
	void *load_buf;
	int ret;

	fit_uname_config = fdt_get_name(fit, cfg_noffset, NULL);
	memset(&images, '\0', sizeof(images));
	images.verify = 1;
	noffset = fit_image_load(&images, (ulong)fit,
		NULL, &fit_uname_config,
		IH_ARCH_DEFAULT, req_image_type, -1,
		FIT_LOAD_IGNORED, &data, &len);
	if (noffset < 0)
		return noffset;
	if (fit_image_get_type(fit, noffset, &image_type)) {
		puts("Can't get image type!\n");
		return -EINVAL;
	}

	if (fit_image_get_comp(fit, noffset, &imape_comp)) {
		puts("Can't get image compression!\n");
		return -EINVAL;
	}

	/* Allow the image to expand by a factor of 4, should be safe */
	load_buf = malloc((1 << 20) + len * 4);
	ret = image_decomp(imape_comp, 0, data, image_type, load_buf,
			   (void *)data, len, CONFIG_SYS_BOOTM_LEN,
			   &load_end);
	free(load_buf);

	if (ret) {
		ret = handle_decomp_error(imape_comp, load_end - 0, ret);
		if (ret != BOOTM_ERR_UNIMPLEMENTED)
			return ret;
	}

	return 0;
}

int bootm_host_load_images(const void *fit, int cfg_noffset)
{
	static uint8_t image_types[] = {
		IH_TYPE_KERNEL,
		IH_TYPE_FLATDT,
		IH_TYPE_RAMDISK,
	};
	int err = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(image_types); i++) {
		int ret;

		ret = bootm_host_load_image(fit, image_types[i], cfg_noffset);
		if (!err && ret && ret != -ENOENT)
			err = ret;
	}

	/* Return the first error we found */
	return err;
}
#endif

#endif /* ndef USE_HOSTCC */
