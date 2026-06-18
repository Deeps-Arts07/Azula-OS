#include <stdio.h>
#include <stdint.h>
#include <camkes.h>

#if defined(__x86_64__) || defined(__i386__)

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

static uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
    pci_port_out32(PCI_CONFIG_ADDRESS, address);
    return pci_port_in32(PCI_CONFIG_DATA);
}
#elif defined(__aarch64__) || defined(__arm__)

static uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t ecam_offset = (bus << 20) | (slot << 15) | (func << 12) | (offset & 0xFC);
    return *(volatile uint32_t *)((uint8_t *)pci_mmio + ecam_offset);
}
#endif

void init_start(void) {
    printf("[USB] Starting PCI bus scan...\n");

    int found = 0;
    for (uint8_t slot = 0; slot < 32; slot++) {
        uint32_t id = pci_read(0, slot, 0, 0x00);
        if (id == 0xFFFFFFFF) continue;

        uint16_t vendor_id = id & 0xFFFF;
        uint16_t device_id = (id >> 16) & 0xFFFF;

        uint32_t class_info = pci_read(0, slot, 0, 0x08);
        uint8_t class_code = (class_info >> 24) & 0xFF;
        uint8_t subclass = (class_info >> 16) & 0xFF;

        // Serial Bus Controller (0x0C), USB (0x03)
        if (class_code == 0x0C && subclass == 0x03) {
            printf("[USB] Found USB Host Controller at 00:%02x.0 (Vendor: 0x%04x, Device: 0x%04x)\n", slot, vendor_id, device_id);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("[USB] Azula USB Host Initialized\n");
    } else {
        printf("[USB] Error: No USB controller found.\n");
    }
    // TODO: libusbdrivers initialization
}
