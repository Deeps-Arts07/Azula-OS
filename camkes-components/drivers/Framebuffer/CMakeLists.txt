set(Framebuffer_sources src/fb.c)
set(Framebuffer_LIBS muslc sel4muslcsys)
DeclareCAmkESComponent(
    Framebuffer
    SOURCES ${Framebuffer_sources}
    LIBS ${Framebuffer_LIBS}
)
