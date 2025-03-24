cmd_tools/env/linux_string.o := /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-musl-gcc -Wp,-MD,tools/env/.linux_string.o.d -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer   -std=gnu11   -I./tools -idirafterinclude -idirafter./arch/arm/include -idirafter ./tools/env -DUSE_HOSTCC -DTEXT_BASE=  -c -o tools/env/linux_string.o tools/env/linux_string.c

source_tools/env/linux_string.o := tools/env/linux_string.c

deps_tools/env/linux_string.o := \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdc-predef.h \
  tools/env/../../lib/linux_string.c \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdio.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/features.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/sys/glibc-types.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/sys/cdefs.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/bits/alltypes.h \
  include/linux/ctype.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/linux/string.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/string.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/strings.h \

tools/env/linux_string.o: $(deps_tools/env/linux_string.o)

$(deps_tools/env/linux_string.o):
