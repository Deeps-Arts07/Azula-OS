set(AzulaInit_sources src/init.c)
set(AzulaInit_LIBS muslc sel4muslcsys sel4vfs)
DeclareCAmkESComponent(
    AzulaInit
    SOURCES ${AzulaInit_sources}
    LIBS ${AzulaInit_LIBS}
)
