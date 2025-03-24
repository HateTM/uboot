cmd_u-boot-mtk.bin := ./tools/mkimage -T mtk_image -a 0x41e00000 -e 0x41e00000 -n "media=snand;nandinfo=2k+64" -d u-boot.bin u-boot-mtk.bin >/dev/null  && cat /dev/null
