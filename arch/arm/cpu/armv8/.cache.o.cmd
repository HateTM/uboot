cmd_arch/arm/cpu/armv8/cache.o := /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-musl-gcc -Wp,-MD,arch/arm/cpu/armv8/.cache.o.d -nostdinc -isystem /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/../lib/gcc/aarch64-openwrt-linux-musl/8.4.0/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -D__ASSEMBLY__ -fno-PIE -g -D__ARM__ -fno-pic -mstrict-align -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -mgeneral-regs-only -fno-common -ffixed-x18 -pipe -march=armv8-a+crc -D__LINUX_ARM_ARCH__=8 -I./arch/arm/mach-mediatek/include   -c -o arch/arm/cpu/armv8/cache.o arch/arm/cpu/armv8/cache.S

source_arch/arm/cpu/armv8/cache.o := arch/arm/cpu/armv8/cache.S

deps_arch/arm/cpu/armv8/cache.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
    $(wildcard include/config/spl/.h) \
    $(wildcard include/config/tpl/.h) \
    $(wildcard include/config/tools/.h) \
    $(wildcard include/config/tpl/build.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/tools/foo.h) \
    $(wildcard include/config/spl/foo.h) \
    $(wildcard include/config/tpl/foo.h) \
    $(wildcard include/config/option.h) \
    $(wildcard include/config/acme.h) \
    $(wildcard include/config/spl/acme.h) \
    $(wildcard include/config/tpl/acme.h) \
  include/asm-offsets.h \
  include/generated/generic-asm-offsets.h \
  include/config.h \
    $(wildcard include/config/boarddir.h) \
  include/config_uncmd_spl.h \
    $(wildcard include/config/spl/dm.h) \
    $(wildcard include/config/dm/serial.h) \
    $(wildcard include/config/dm/i2c.h) \
    $(wildcard include/config/dm/spi.h) \
    $(wildcard include/config/dm/stdio.h) \
  include/configs/mt7986.h \
    $(wildcard include/config/sys/maxargs.h) \
    $(wildcard include/config/sys/bootm/len.h) \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/sys/pbsize.h) \
    $(wildcard include/config/sys/prompt.h) \
    $(wildcard include/config/sys/noncached/memory.h) \
    $(wildcard include/config/sys/mmc/env/dev.h) \
    $(wildcard include/config/sys/uboot/base.h) \
    $(wildcard include/config/sys/text/base.h) \
    $(wildcard include/config/sys/uboot/start.h) \
    $(wildcard include/config/sys/init/sp/addr.h) \
    $(wildcard include/config/sys/nand/max/chips.h) \
    $(wildcard include/config/sys/sdram/base.h) \
    $(wildcard include/config/ipaddr.h) \
    $(wildcard include/config/serverip.h) \
    $(wildcard include/config/netmask.h) \
  include/linux/sizes.h \
  include/linux/const.h \
  arch/arm/include/asm/config.h \
    $(wildcard include/config/sys/boot/ramdisk/high.h) \
    $(wildcard include/config/arch/ls1021a.h) \
    $(wildcard include/config/cpu/pxa27x.h) \
    $(wildcard include/config/cpu/monahans.h) \
    $(wildcard include/config/cpu/pxa25x.h) \
    $(wildcard include/config/fsl/layerscape.h) \
  include/linux/kconfig.h \
  include/config_fallbacks.h \
    $(wildcard include/config/spl.h) \
    $(wildcard include/config/spl/pad/to.h) \
    $(wildcard include/config/spl/max/size.h) \
    $(wildcard include/config/sys/baudrate/table.h) \
    $(wildcard include/config/cmd/kgdb.h) \
  arch/arm/include/asm/macro.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/armv8/multientry.h) \
    $(wildcard include/config/armv8/psci.h) \
    $(wildcard include/config/armv8/ea/el3/first.h) \
    $(wildcard include/config/gicv3.h) \
    $(wildcard include/config/gicv2.h) \
  arch/arm/include/asm/system.h \
    $(wildcard include/config/armv7/lpae.h) \
    $(wildcard include/config/cpu/v7a.h) \
    $(wildcard include/config/sys/arm/cache/writethrough.h) \
    $(wildcard include/config/sys/arm/cache/writealloc.h) \
    $(wildcard include/config/sys/arm/cache/writeback.h) \
    $(wildcard include/config/armv7/psci.h) \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/stack/validation.h) \
    $(wildcard include/config/kasan.h) \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  arch/arm/include/asm/barriers.h \
  include/linux/linkage.h \
  arch/arm/include/asm/linkage.h \

arch/arm/cpu/armv8/cache.o: $(deps_arch/arm/cpu/armv8/cache.o)

$(deps_arch/arm/cpu/armv8/cache.o):
