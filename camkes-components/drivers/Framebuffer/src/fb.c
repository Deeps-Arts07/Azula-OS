#include <stdio.h>
#include <stdint.h>
#include <camkes.h>

#if defined(__x86_64__) || defined(__i386__)
extern uint32_t pci_port_in32(uint16_t port);
extern void pci_port_out32(uint16_t port, uint32_t val);

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

static uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
    pci_port_out32(PCI_CONFIG_ADDRESS, address);
    return pci_port_in32(PCI_CONFIG_DATA);
}
#elif defined(__aarch64__) || defined(__arm__)
extern volatile void *pci_mmio;

static uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t ecam_offset = (bus << 20) | (slot << 15) | (func << 12) | (offset & 0xFC);
    return *(volatile uint32_t *)((uint8_t *)pci_mmio + ecam_offset);
}
#endif

void init_start(void) {
    printf("[Framebuffer] Starting PCI bus scan...\n");

    int found = 0;
    for (uint8_t slot = 0; slot < 32; slot++) {
        uint32_t id = pci_read(0, slot, 0, 0x00);
        if (id == 0xFFFFFFFF) continue;

        uint16_t vendor_id = id & 0xFFFF;
        uint16_t device_id = (id >> 16) & 0xFFFF;

        uint32_t class_info = pci_read(0, slot, 0, 0x08);
        uint8_t class_code = (class_info >> 24) & 0xFF;

        // Display Controller (0x03)
        if (class_code == 0x03) {
            printf("[Framebuffer] Found Display Controller at 00:%02x.0 (Vendor: 0x%04x, Device: 0x%04x)\n", slot, vendor_id, device_id);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("[Framebuffer] Azula Framebuffer Initialized\n");
    } else {
        printf("[Framebuffer] Error: No display controller found.\n");
    }
    // TODO: libplatsupport initialization (VESA/pl111)
}
