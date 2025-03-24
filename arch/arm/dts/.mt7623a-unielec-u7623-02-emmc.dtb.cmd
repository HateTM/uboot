cmd_arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb := mkdir -p arch/arm/dts/ ; (cat arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dts; ) > arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.pre.tmp; cc -E -Wp,-MD,arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.d.pre.tmp -nostdinc -I./arch/arm/dts -I./arch/arm/dts/include -Iinclude -I./include -I./arch/arm/include -include ./include/linux/kconfig.h -D__ASSEMBLY__ -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.dts.tmp arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.pre.tmp ; ./scripts/dtc/dtc -O dtb -o arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb -b 0 -i arch/arm/dts/ -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num  -a 0x8 -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num  -d arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.d.dtc.tmp arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.dts.tmp || (echo "Check /home/hatetm/temp_data/sdk/openwrt-21.02/uboot/uboot/arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.pre.tmp for errors" && false) ; sed "s:arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.pre.tmp:arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dts:" arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.d.pre.tmp arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.d.dtc.tmp > arch/arm/dts/.mt7623a-unielec-u7623-02-emmc.dtb.d

source_arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb := arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dts

deps_arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb := \
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
  arch/arm/dts/mt7623.dtsi \
  arch/arm/dts/include/dt-bindings/clock/mt7623-clk.h \
  arch/arm/dts/include/dt-bindings/gpio/gpio.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/irq.h \
  arch/arm/dts/include/dt-bindings/interrupt-controller/arm-gic.h \
  arch/arm/dts/include/dt-bindings/phy/phy.h \
  arch/arm/dts/include/dt-bindings/power/mt7623-power.h \
  arch/arm/dts/include/dt-bindings/reset/mt7623-reset.h \
  arch/arm/dts/skeleton.dtsi \
  arch/arm/dts/mt7623-u-boot.dtsi \

arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb: $(deps_arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb)

$(deps_arch/arm/dts/mt7623a-unielec-u7623-02-emmc.dtb):
