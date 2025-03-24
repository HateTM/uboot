	.arch armv8-a+crc
	.file	"asm-offsets.c"
// GNU C11 (OpenWrt GCC 8.4.0 r0-c067e3725) version 8.4.0 (aarch64-openwrt-linux-musl)
//	compiled by GNU C version 4.9.4, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version none
// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -nostdinc -I include -I ./arch/arm/include
// -I ./arch/arm/mach-mediatek/include
// -iprefix /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/../lib/gcc/aarch64-openwrt-linux-musl/8.4.0/
// -isysroot /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin//../..
// -idirafter /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/target-aarch64-openwrt-linux_musl/usr/include
// -D __KERNEL__ -D __UBOOT__ -D __ARM__ -D __LINUX_ARM_ARCH__=8
// -D DO_DEPS_ONLY -D KBUILD_BASENAME="asm_offsets"
// -D KBUILD_MODNAME="asm_offsets"
// -isystem /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/../lib/gcc/aarch64-openwrt-linux-musl/8.4.0/include
// -include ./include/linux/kconfig.h -MD lib/.asm-offsets.s.d
// lib/asm-offsets.c -mstrict-align -mgeneral-regs-only -march=armv8-a+crc
// -mlittle-endian -mabi=lp64 -auxbase-strip lib/asm-offsets.s -g -O2 -Wall
// -Werror -Wstrict-prototypes -Wno-format-security -Wno-pointer-sign
// -Wno-stringop-truncation -Wno-array-bounds -Wstringop-overflow=0
// -Wno-maybe-uninitialized -Wno-format-nonliteral
// -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-label
// -Wno-unused-function -Werror=date-time -Wno-packed-not-aligned
// -std=gnu11 -fno-builtin -ffreestanding -fshort-wchar
// -fno-strict-aliasing -fno-stack-protector
// -fno-delete-null-pointer-checks -fmacro-prefix-map=./= -fstack-usage
// -fno-pic -ffunction-sections -fdata-sections -ffixed-r9 -fno-common
// -ffixed-x18 -fverbose-asm
// options enabled:  -faggressive-loop-optimizations -falign-labels
// -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
// -fcaller-saves -fchkp-check-incomplete-type -fchkp-check-read
// -fchkp-check-write -fchkp-instrument-calls -fchkp-narrow-bounds
// -fchkp-optimize -fchkp-store-bounds -fchkp-use-static-bounds
// -fchkp-use-static-const-bounds -fchkp-use-wrappers -fcode-hoisting
// -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
// -fcrossjumping -fcse-follow-jumps -fdata-sections -fdefer-pop
// -fdevirtualize -fdevirtualize-speculatively -fdwarf2-cfi-asm
// -fearly-inlining -feliminate-unused-debug-types
// -fexpensive-optimizations -fforward-propagate -ffp-int-builtin-inexact
// -ffunction-cse -ffunction-sections -fgcse -fgcse-lm -fgnu-runtime
// -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
// -fif-conversion -fif-conversion2 -findirect-inlining -finline
// -finline-atomics -finline-functions-called-once -finline-small-functions
// -fipa-bit-cp -fipa-cp -fipa-icf -fipa-icf-functions -fipa-icf-variables
// -fipa-profile -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra
// -fipa-vrp -fira-hoist-pressure -fira-share-save-slots
// -fira-share-spill-slots -fisolate-erroneous-paths-dereference -fivopts
// -fkeep-static-consts -fleading-underscore -flifetime-dse -flra-remat
// -flto-odr-type-merging -fmath-errno -fmerge-constants
// -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
// -foptimize-sibling-calls -foptimize-strlen -fpartial-inlining -fpeephole
// -fpeephole2 -fplt -fprefetch-loop-arrays -free -freg-struct-return
// -freorder-blocks -freorder-functions -frerun-cse-after-loop
// -fsched-critical-path-heuristic -fsched-dep-count-heuristic
// -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
// -fsched-pressure -fsched-rank-heuristic -fsched-spec
// -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
// -fschedule-insns -fschedule-insns2 -fsection-anchors
// -fsemantic-interposition -fshow-column -fshrink-wrap
// -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
// -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstdarg-opt
// -fstore-merging -fstrict-volatile-bitfields -fsync-libcalls
// -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
// -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
// -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
// -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
// -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
// -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
// -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
// -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
// -funit-at-a-time -funwind-tables -fvar-tracking
// -fvar-tracking-assignments -fverbose-asm -fzero-initialized-in-bss
// -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -mgeneral-regs-only
// -mlittle-endian -mmusl -momit-leaf-frame-pointer
// -mpc-relative-literal-loads -mstrict-align

	.text
.Ltext0:
	.section	.text.startup.main,"ax",@progbits
	.align	2
	.p2align 3,,7
	.global	main
	.type	main, %function
main:
.LFB133:
	.file 1 "lib/asm-offsets.c"
	.loc 1 21 1 view -0
	.cfi_startproc
	.loc 1 23 2 view .LVU1
#APP
// 23 "lib/asm-offsets.c" 1
	
.ascii "->GENERATED_GBL_DATA_SIZE 448 (sizeof(struct global_data) + 15) & ~15"	//
// 0 "" 2
	.loc 1 26 2 view .LVU2
// 26 "lib/asm-offsets.c" 1
	
.ascii "->GENERATED_BD_INFO_SIZE 144 (sizeof(struct bd_info) + 15) & ~15"	//
// 0 "" 2
	.loc 1 29 2 view .LVU3
// 29 "lib/asm-offsets.c" 1
	
.ascii "->GD_SIZE 440 sizeof(struct global_data)"	//
// 0 "" 2
	.loc 1 31 2 view .LVU4
// 31 "lib/asm-offsets.c" 1
	
.ascii "->GD_BD 0 offsetof(struct global_data, bd)"	//
// 0 "" 2
	.loc 1 33 2 view .LVU5
// 33 "lib/asm-offsets.c" 1
	
.ascii "->GD_FLAGS 8 offsetof(struct global_data, flags)"	//
// 0 "" 2
	.loc 1 36 2 view .LVU6
// 36 "lib/asm-offsets.c" 1
	
.ascii "->GD_MALLOC_BASE 280 offsetof(struct global_data, malloc_base)"	//
// 0 "" 2
	.loc 1 39 2 view .LVU7
// 39 "lib/asm-offsets.c" 1
	
.ascii "->GD_RELOCADDR 112 offsetof(struct global_data, relocaddr)"	//
// 0 "" 2
	.loc 1 41 2 view .LVU8
// 41 "lib/asm-offsets.c" 1
	
.ascii "->GD_RELOC_OFF 152 offsetof(struct global_data, reloc_off)"	//
// 0 "" 2
	.loc 1 43 2 view .LVU9
// 43 "lib/asm-offsets.c" 1
	
.ascii "->GD_START_ADDR_SP 144 offsetof(struct global_data, start_addr_sp)"	//
// 0 "" 2
	.loc 1 45 2 view .LVU10
// 45 "lib/asm-offsets.c" 1
	
.ascii "->GD_NEW_GD 160 offsetof(struct global_data, new_gd)"	//
// 0 "" 2
	.loc 1 47 2 view .LVU11
// 47 "lib/asm-offsets.c" 1
	
.ascii "->GD_ENV_ADDR 64 offsetof(struct global_data, env_addr)"	//
// 0 "" 2
	.loc 1 49 2 view .LVU12
// lib/asm-offsets.c:50: }
	.loc 1 50 1 is_stmt 0 view .LVU13
#NO_APP
	mov	w0, 0	//,
	ret	
	.cfi_endproc
.LFE133:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/asm-generic/int-ll64.h"
	.file 3 "include/linux/types.h"
	.file 4 "include/errno.h"
	.file 5 "include/linux/string.h"
	.file 6 "./arch/arm/include/asm/u-boot-arm.h"
	.file 7 "include/env_internal.h"
	.file 8 "include/linux/libfdt_env.h"
	.file 9 "include/linux/../../scripts/dtc/libfdt/fdt.h"
	.file 10 "include/linux/libfdt.h"
	.file 11 "include/fdtdec.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x260
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0xc
	.4byte	.LASF41
	.4byte	.LASF42
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x4
	.byte	0x11
	.byte	0xc
	.4byte	0x35
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	0x5f
	.4byte	0x4c
	.uleb128 0x5
	.4byte	0x51
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	0x3c
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x6
	.4byte	0x58
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x4
	.byte	0x1f
	.byte	0x13
	.4byte	0x4c
	.string	""
	.uleb128 0x7
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x9
	.byte	0x8
	.4byte	0x58
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0xa
	.4byte	.LASF9
	.byte	0x2
	.byte	0x13
	.byte	0x17
	.4byte	0xa6
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.uleb128 0x7
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0xa
	.4byte	.LASF10
	.byte	0x2
	.byte	0x19
	.byte	0x16
	.4byte	0x85
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0xb
	.string	"u8"
	.byte	0x2
	.byte	0x24
	.byte	0xf
	.4byte	0x9a
	.uleb128 0xa
	.4byte	.LASF12
	.byte	0x3
	.byte	0x5b
	.byte	0x18
	.4byte	0x51
	.uleb128 0xa
	.4byte	.LASF13
	.byte	0x3
	.byte	0x90
	.byte	0x19
	.4byte	0xb4
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x5
	.byte	0xb
	.byte	0xf
	.4byte	0x7f
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x6
	.byte	0x12
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x6
	.byte	0x13
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x6
	.byte	0x14
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x6
	.byte	0x15
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x6
	.byte	0x16
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x6
	.byte	0x17
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x6
	.byte	0x18
	.byte	0xe
	.4byte	0xd2
	.uleb128 0x7
	.byte	0x10
	.byte	0x4
	.4byte	.LASF23
	.uleb128 0x4
	.4byte	0x5f
	.4byte	0x15c
	.uleb128 0xc
	.byte	0
	.uleb128 0x6
	.4byte	0x151
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x7
	.byte	0x74
	.byte	0x13
	.4byte	0x15c
	.uleb128 0xa
	.4byte	.LASF25
	.byte	0x8
	.byte	0x12
	.byte	0x10
	.4byte	0xde
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0x28
	.byte	0x9
	.byte	0xc
	.byte	0x8
	.4byte	0x209
	.uleb128 0xe
	.4byte	.LASF26
	.byte	0x9
	.byte	0xd
	.byte	0xa
	.4byte	0x16d
	.byte	0
	.uleb128 0xe
	.4byte	.LASF27
	.byte	0x9
	.byte	0xe
	.byte	0xa
	.4byte	0x16d
	.byte	0x4
	.uleb128 0xe
	.4byte	.LASF28
	.byte	0x9
	.byte	0xf
	.byte	0xa
	.4byte	0x16d
	.byte	0x8
	.uleb128 0xe
	.4byte	.LASF29
	.byte	0x9
	.byte	0x10
	.byte	0xa
	.4byte	0x16d
	.byte	0xc
	.uleb128 0xe
	.4byte	.LASF30
	.byte	0x9
	.byte	0x11
	.byte	0xa
	.4byte	0x16d
	.byte	0x10
	.uleb128 0xe
	.4byte	.LASF31
	.byte	0x9
	.byte	0x12
	.byte	0xa
	.4byte	0x16d
	.byte	0x14
	.uleb128 0xe
	.4byte	.LASF32
	.byte	0x9
	.byte	0x13
	.byte	0xa
	.4byte	0x16d
	.byte	0x18
	.uleb128 0xe
	.4byte	.LASF33
	.byte	0x9
	.byte	0x16
	.byte	0xa
	.4byte	0x16d
	.byte	0x1c
	.uleb128 0xe
	.4byte	.LASF34
	.byte	0x9
	.byte	0x19
	.byte	0xa
	.4byte	0x16d
	.byte	0x20
	.uleb128 0xe
	.4byte	.LASF35
	.byte	0x9
	.byte	0x1c
	.byte	0xa
	.4byte	0x16d
	.byte	0x24
	.byte	0
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0xa
	.byte	0xb
	.byte	0x1b
	.4byte	0x215
	.uleb128 0x9
	.byte	0x8
	.4byte	0x179
	.uleb128 0x7
	.byte	0x1
	.byte	0x2
	.4byte	.LASF37
	.uleb128 0x4
	.4byte	0xc7
	.4byte	0x22d
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.4byte	.LASF38
	.byte	0xb
	.byte	0x6f
	.byte	0xb
	.4byte	0x222
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0xb
	.byte	0x70
	.byte	0xb
	.4byte	0x222
	.uleb128 0xf
	.4byte	.LASF45
	.byte	0x1
	.byte	0x14
	.byte	0x5
	.4byte	0x35
	.8byte	.LFB133
	.8byte	.LFE133-.LFB133
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB133
	.8byte	.LFE133-.LFB133
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB133
	.8byte	.LFE133
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF43:
	.string	"error_message"
.LASF44:
	.string	"fdt_header"
.LASF37:
	.string	"_Bool"
.LASF10:
	.string	"__u32"
.LASF39:
	.string	"__dtb_dt_spl_begin"
.LASF14:
	.string	"errno"
.LASF28:
	.string	"off_dt_struct"
.LASF25:
	.string	"fdt32_t"
.LASF26:
	.string	"magic"
.LASF30:
	.string	"off_mem_rsvmap"
.LASF16:
	.string	"IRQ_STACK_START"
.LASF42:
	.string	"/home/hatetm/temp_data/sdk/openwrt-21.02/uboot/uboot"
.LASF35:
	.string	"size_dt_struct"
.LASF0:
	.string	"long unsigned int"
.LASF2:
	.string	"short unsigned int"
.LASF17:
	.string	"FIQ_STACK_START"
.LASF7:
	.string	"unsigned char"
.LASF15:
	.string	"___strtok"
.LASF9:
	.string	"__u8"
.LASF36:
	.string	"working_fdt"
.LASF21:
	.string	"_datarelro_start_ofs"
.LASF31:
	.string	"version"
.LASF12:
	.string	"ulong"
.LASF4:
	.string	"unsigned int"
.LASF18:
	.string	"_datarel_start_ofs"
.LASF11:
	.string	"long long unsigned int"
.LASF45:
	.string	"main"
.LASF38:
	.string	"__dtb_dt_begin"
.LASF22:
	.string	"IRQ_STACK_START_IN"
.LASF5:
	.string	"long long int"
.LASF24:
	.string	"default_environment"
.LASF1:
	.string	"char"
.LASF40:
	.ascii	"GNU C11 8.4.0 -mstrict-align -mgeneral-regs-only -march=armv"
	.ascii	"8-a+cr"
	.string	"c -mlittle-endian -mabi=lp64 -g -O2 -std=gnu11 -fno-builtin -ffreestanding -fshort-wchar -fno-strict-aliasing -fno-stack-protector -fno-delete-null-pointer-checks -fstack-usage -fno-pic -ffunction-sections -fdata-sections -ffixed-r9 -fno-common -ffixed-x18"
.LASF8:
	.string	"short int"
.LASF34:
	.string	"size_dt_strings"
.LASF32:
	.string	"last_comp_version"
.LASF29:
	.string	"off_dt_strings"
.LASF20:
	.string	"_datarellocal_start_ofs"
.LASF13:
	.string	"__be32"
.LASF3:
	.string	"long int"
.LASF23:
	.string	"long double"
.LASF6:
	.string	"signed char"
.LASF19:
	.string	"_datarelrolocal_start_ofs"
.LASF33:
	.string	"boot_cpuid_phys"
.LASF27:
	.string	"totalsize"
.LASF41:
	.string	"lib/asm-offsets.c"
	.ident	"GCC: (OpenWrt GCC 8.4.0 r0-c067e3725) 8.4.0"
	.section	.note.GNU-stack,"",@progbits
