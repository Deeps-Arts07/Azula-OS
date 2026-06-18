#include <stdio.h>
#include <camkes.h>

void init_start(void) {
    printf("[Framebuffer] Initializing Display Controller...\n");
    printf("[Framebuffer] Azula Framebuffer Initialized\n");
    // TODO: libplatsupport initialization (VESA/pl111)
}
