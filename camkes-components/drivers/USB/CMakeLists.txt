set(USB_sources src/usb.c)
set(USB_LIBS muslc sel4muslcsys)
DeclareCAmkESComponent(
    USB
    SOURCES ${USB_sources}
    LIBS ${USB_LIBS}
)
