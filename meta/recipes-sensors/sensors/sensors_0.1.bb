SUMMARY = "Python application to display sensor values from STM32"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://display.py"

S = "${WORKDIR}"

RDEPENDS:${PN} += "python3 python3-pyserial"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/display.py ${D}${bindir}/display
}
