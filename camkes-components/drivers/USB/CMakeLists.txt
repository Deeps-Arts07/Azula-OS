set(USB_sources src/usb.c)
set(USB_LIBS muslc sel4muslcsys sel4vfs)
DeclareCAmkESComponent(
    USB
    SOURCES ${USB_sources}
    LIBS ${USB_LIBS}
)
