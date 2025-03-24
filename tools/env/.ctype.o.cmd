cmd_tools/env/ctype.o := /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-musl-gcc -Wp,-MD,tools/env/.ctype.o.d -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer   -std=gnu11   -I./tools -idirafterinclude -idirafter./arch/arm/include -idirafter ./tools/env -DUSE_HOSTCC -DTEXT_BASE=  -c -o tools/env/ctype.o tools/env/ctype.c

source_tools/env/ctype.o := tools/env/ctype.c

deps_tools/env/ctype.o := \
  /home/hatetm/temp_data/sdk/openwrt-21.02/staging_dir/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl/include/stdc-predef.h \
  tools/env/../../lib/ctype.c \
  include/linux/ctype.h \

tools/env/ctype.o: $(deps_tools/env/ctype.o)

$(deps_tools/env/ctype.o):
