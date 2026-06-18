# Testing and Emulation Guide

Azula OS heavily relies on QEMU for rapid iteration and testing across architectures.

## Prerequisites

Run the setup script inside a WSL2 or Debian/Ubuntu environment:
```bash
./build/setup-dev-env.sh
source sel4-venv/bin/activate
```

## Phase 1: Booting "Hello World"

*(Instructions will be updated as the build system is finalized)*

### Building for x86-64
```bash
# To be populated
```

### Running in QEMU (x86-64)
```bash
qemu-system-x86_64 -m 512 -nographic -kernel <path_to_image>
```

### Building for ARM AArch64
```bash
# To be populated
```

### Running in QEMU (ARM AArch64)
```bash
qemu-system-aarch64 -machine virt -cpu cortex-a57 -m 512 -nographic -kernel <path_to_image>
```

## Automated Testing (CI)
All commits are built and run in headless QEMU via GitHub Actions. The CI scripts assert that the specific string `"hello world"` (or the equivalent component output) is emitted over the serial console.
