cmd_arch/arm/mach-mediatek/mt7986/lowlevel_init.o := /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-musl-gcc -Wp,-MD,arch/arm/mach-mediatek/mt7986/.lowlevel_init.o.d -nostdinc -isystem /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/../lib/gcc/aarch64-openwrt-linux-musl/8.4.0/include -Iinclude   -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -D__ASSEMBLY__ -fno-PIE -g -D__ARM__ -fno-pic -mstrict-align -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -mgeneral-regs-only -fno-common -ffixed-x18 -pipe -march=armv8-a+crc -D__LINUX_ARM_ARCH__=8 -I./arch/arm/mach-mediatek/include   -c -o arch/arm/mach-mediatek/mt7986/lowlevel_init.o arch/arm/mach-mediatek/mt7986/lowlevel_init.S

source_arch/arm/mach-mediatek/mt7986/lowlevel_init.o := arch/arm/mach-mediatek/mt7986/lowlevel_init.S

deps_arch/arm/mach-mediatek/mt7986/lowlevel_init.o := \
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

arch/arm/mach-mediatek/mt7986/lowlevel_init.o: $(deps_arch/arm/mach-mediatek/mt7986/lowlevel_init.o)

$(deps_arch/arm/mach-mediatek/mt7986/lowlevel_init.o):
