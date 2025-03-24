cmd_arch/arm/dts/mt8512-bm1-emmc.dtb := mkdir -p arch/arm/dts/ ; (cat arch/arm/dts/mt8512-bm1-emmc.dts; ) > arch/arm/dts/.mt8512-bm1-emmc.dtb.pre.tmp; cc -E -Wp,-MD,arch/arm/dts/.mt8512-bm1-emmc.dtb.d.pre.tmp -nostdinc -I./arch/arm/dts -I./arch/arm/dts/include -Iinclude -I./include -I./arch/arm/include -include ./include/linux/kconfig.h -D__ASSEMBLY__ -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/dts/.mt8512-bm1-emmc.dtb.dts.tmp arch/arm/dts/.mt8512-bm1-emmc.dtb.pre.tmp ; ./scripts/dtc/dtc -O dtb -o arch/arm/dts/mt8512-bm1-emmc.dtb -b 0 -i arch/arm/dts/ -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num  -a 0x8 -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num  -d arch/arm/dts/.mt8512-bm1-emmc.dtb.d.dtc.tmp arch/arm/dts/.mt8512-bm1-emmc.dtb.dts.tmp || (echo "Check /home/hatetm/temp_data/sdk/openwrt-21.02/uboot/uboot/arch/arm/dts/.mt8512-bm1-emmc.dtb.pre.tmp for errors" && false) ; sed "s:arch/arm/dts/.mt8512-bm1-emmc.dtb.pre.tmp:arch/arm/dts/mt8512-bm1-emmc.dts:" arch/arm/dts/.mt8512-bm1-emmc.dtb.d.pre.tmp arch/arm/dts/.mt8512-bm1-emmc.dtb.d.dtc.tmp > arch/arm/dts/.mt8512-bm1-emmc.dtb.d

source_arch/arm/dts/mt8512-bm1-emmc.dtb := arch/arm/dts/mt8512-bm1-emmc.dts

deps_arch/arm/dts/mt8512-bm1-emmc.dtb := \
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
  arch/arm/dts/mt8512.dtsi \
  arch/arm/dts/include/dt-bindings/clock/mt8512-clk.h \
  arch/arm/dts/include/dt-bindings/gpio/gpio.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/irq.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/arm-gic.h \
  arch/arm/dts/include/dt-bindings/phy/phy.h \

arch/arm/dts/mt8512-bm1-emmc.dtb: $(deps_arch/arm/dts/mt8512-bm1-emmc.dtb)

$(deps_arch/arm/dts/mt8512-bm1-emmc.dtb):
