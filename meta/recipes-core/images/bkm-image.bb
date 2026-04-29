DESCRIPTION = "Custom Raspberry Pi 3 image with sensor display app"
LICENSE = "MIT"

require recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL += "sensors python3 python3-pyserial"
