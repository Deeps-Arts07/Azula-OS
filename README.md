# Azula OS

A lightweight, privacy-first operating system where the entire user interface is a hardened browser running on top of a formally verified seL4 microkernel.

## Overview
Azula OS is designed for users who require extreme privacy guarantees and hardware-level isolation without relying on a monolithic Linux kernel.

Key features:
- **Formally Verified Core**: Uses the seL4 microkernel.
- **Micro-services Architecture**: Every component (networking, storage, UI) is an isolated CAmkES component.
- **Privacy First**: All network traffic is forcefully routed through rotating anonymous circuits (Tor, I2P, Lokinet).
- **Amnesic by Default**: Runs entirely in RAM. No persistent state unless explicitly encrypted.
- **Hardened Browser UI**: There is no desktop environment. A hardened browser acts as the entire UI.

## Getting Started
Please see `docs/TESTING.md` for information on setting up the build environment and testing the OS in QEMU.

## Architecture
See `docs/ARCHITECTURE.md` for a detailed breakdown of the 5-layer stack.

## Threat Model
See `docs/THREAT_MODEL.md` for what this OS can and cannot protect against.
