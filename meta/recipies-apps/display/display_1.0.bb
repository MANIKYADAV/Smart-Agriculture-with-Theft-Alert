SUMMARY = "Python Display Service for UART Sensor Data"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://display.py \
           file://display.service \
          "

S = "${WORKDIR}"

inherit systemd python3native

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/display.py ${D}${bindir}/display.py

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/display.service ${D}${systemd_system_unitdir}/display.service
}

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "display.service"

RDEPENDS:${PN} = "python3 python3-pip python3-smbus2"
