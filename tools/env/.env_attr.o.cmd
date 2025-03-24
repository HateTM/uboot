cmd_tools/env/env_attr.o := /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-musl-gcc -Wp,-MD,tools/env/.env_attr.o.d -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer   -std=gnu11   -I./tools -idirafterinclude -idirafter./arch/arm/include -idirafter ./tools/env -DUSE_HOSTCC -DTEXT_BASE=  -c -o tools/env/env_attr.o tools/env/env_attr.c

source_tools/env/env_attr.o := tools/env/env_attr.c

deps_tools/env/env_attr.o := \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdc-predef.h \
  tools/env/../../env/attr.c \
    $(wildcard include/config/regex.h) \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdint.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/bits/alltypes.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/bits/stdint.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdio.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/features.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/sys/glibc-types.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/sys/cdefs.h \
  include/linux/linux_string.h \
  include/env_attr.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/errno.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/bits/errno.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/linux/string.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/string.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/strings.h \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/malloc.h \

tools/env/env_attr.o: $(deps_tools/env/env_attr.o)

$(deps_tools/env/env_attr.o):
