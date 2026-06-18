# Testing and Emulation Guide

Azula OS heavily relies on QEMU for rapid iteration and testing across architectures.

## Prerequisites

Run the setup script inside a WSL2 or Debian/Ubuntu environment:
```bash
./build/setup-dev-env.sh
source sel4-venv/bin/activate
```

## Phase 1: Booting "Hello World" (Complete)

Phase 1 successfully implemented an unmodified seL4 microkernel booting a minimal CAmkES component that prints "hello world" over the serial console on both x86-64 and ARM AArch64.

### Building and Testing Locally
The build process relies on the Google `repo` tool. The CI automatically fetches the required dependencies. To run locally:
```bash
./build/setup-dev-env.sh
source sel4-venv/bin/activate
mkdir workspace && cd workspace
repo init -u https://github.com/seL4/camkes-manifest.git
repo sync
rm -rf kernel && ln -s ../kernel ./kernel
mkdir -p projects/camkes/apps && ln -s ../../../../camkes-components/HelloWorld projects/camkes/apps/HelloWorld
mkdir build && cd build
# For x86:
../init-build.sh -DCAMKES_APP=HelloWorld -DPLATFORM=pc99 -DSIMULATION=TRUE
# For ARM AArch64:
../init-build.sh -DCAMKES_APP=HelloWorld -DPLATFORM=qemu-arm-virt -DAARCH64=1 -DSIMULATION=TRUE
ninja
./simulate
```

## Automated Testing (CI)
All commits are built and run in headless QEMU via GitHub Actions. The CI scripts assert that the specific string `"hello world"` (or the equivalent component output) is emitted over the serial console.
