#!/usr/bin/env bash
set -e

# Azula OS: Build Environment Setup Script
# Target: Ubuntu/Debian (WSL2 compatible)

echo "Setting up Azula OS development environment..."

# 1. Update and install standard dependencies
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    python3-dev \
    python3-pip \
    python3-setuptools \
    python3-venv \
    curl \
    wget \
    git \
    libxml2-utils \
    ncurses-dev \
    device-tree-compiler \
    u-boot-tools \
    cpio \
    libcap-dev \
    libpixman-1-dev \
    libglib2.0-dev \
    libslirp-dev

# 2. Install QEMU for both x86-64 and AArch64
sudo apt-get install -y qemu-system-x86 qemu-system-arm qemu-utils

# 3. Install Cross-compilation toolchains
# For ARM AArch64
sudo apt-get install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
# For standard ARM if needed (32-bit)
sudo apt-get install -y gcc-arm-none-eabi

# 4. Install Google's 'repo' tool for managing seL4 projects
if ! command -v repo &> /dev/null; then
    echo "Installing repo tool..."
    mkdir -p ~/.bin
    curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo
    chmod a+rx ~/.bin/repo
    echo 'export PATH="$HOME/.bin:$PATH"' >> ~/.bashrc
    export PATH="$HOME/.bin:$PATH"
fi

# 5. Set up Python virtual environment for seL4 dependencies
if [ ! -d "sel4-venv" ]; then
    python3 -m venv sel4-venv
fi
source sel4-venv/bin/activate
pip install --upgrade pip
pip install setuptools build
pip install \
    sel4-deps \
    camkes-deps \
    pylint \
    autopep8 \
    aenum \
    sh \
    pyfdt \
    lxml \
    six

echo ""
echo "==========================================================="
echo "Development environment setup complete!"
echo "Please restart your shell or run 'source ~/.bashrc' to ensure 'repo' is in your PATH."
echo "Before building, remember to activate the python environment:"
echo "  source sel4-venv/bin/activate"
echo "==========================================================="
