#!/usr/bin/env bash
set -e

# Azula OS: Build Environment Setup Script
# Target: Ubuntu/Debian (WSL2 compatible)

ARCH="all"

for arg in "$@"; do
    case $arg in
        --arch=*)
        ARCH="${arg#*=}"
        shift
        ;;
    esac
done

echo "Setting up Azula OS development environment for arch: $ARCH..."

# Configure apt to cache downloaded packages
sudo rm -f /etc/apt/apt.conf.d/docker-clean
echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' | sudo tee /etc/apt/apt.conf.d/keep-cache

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
    libslirp-dev \
    qemu-utils

# 2. Install QEMU and Cross-compilation toolchains per architecture
if [ "$ARCH" = "x86" ] || [ "$ARCH" = "all" ]; then
    echo "Installing x86-64 specific dependencies..."
    sudo apt-get install -y qemu-system-x86
fi

if [ "$ARCH" = "arm" ] || [ "$ARCH" = "all" ]; then
    echo "Installing ARM specific dependencies..."
    sudo apt-get install -y qemu-system-arm
    sudo apt-get install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu gcc-arm-none-eabi
fi

# 3. Install Google's 'repo' tool for managing seL4 projects
if ! command -v repo &> /dev/null; then
    echo "Installing repo tool..."
    mkdir -p ~/.bin
    curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo
    chmod a+rx ~/.bin/repo
    echo 'export PATH="$HOME/.bin:$PATH"' >> ~/.bashrc
    export PATH="$HOME/.bin:$PATH"
fi

# 4. Set up Python virtual environment for seL4 dependencies
if [ ! -d "sel4-venv" ]; then
    python3 -m venv sel4-venv
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
else
    echo "Python virtual environment already exists. Skipping pip install."
fi

echo ""
echo "==========================================================="
echo "Development environment setup complete!"
echo "Please restart your shell or run 'source ~/.bashrc' to ensure 'repo' is in your PATH."
echo "Before building, remember to activate the python environment:"
echo "  source sel4-venv/bin/activate"
echo "==========================================================="
