#include <stdio.h>
#include <camkes.h>

int run(void) {
    printf("[AzulaInit] Starting Initialization Sequence...\n");
    
    printf("[AzulaInit] Initializing Framebuffer...\n");
    fb_init_start();
    
    printf("[AzulaInit] Initializing USB Driver...\n");
    usb_init_start();
    
    printf("[AzulaInit] Starting BusyBox Shell...\n");
    shell_init_start();

    printf("[AzulaInit] Boot Sequence Complete.\n");
    return 0;
}
