set(BusyBox_sources src/busybox.c)
set(BusyBox_LIBS muslc sel4muslcsys sel4vfs)
DeclareCAmkESComponent(
    BusyBox
    SOURCES ${BusyBox_sources}
    LIBS ${BusyBox_LIBS}
)
