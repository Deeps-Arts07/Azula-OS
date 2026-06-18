# Azula OS Architecture

Azula OS is a lightweight, privacy-first operating system designed with a hardened browser interface over a formally verified seL4 microkernel. 

## The Layered Stack

Azula OS avoids the monolithic Linux kernel entirely. It is built as a set of isolated capability-based components (CAmkES) running on seL4.

### Layer 1: seL4 Microkernel
- Unmodified, formally verified microkernel (Phase 1 complete).
- Enforces strict capability-based access control.
- CAmkES is used as the component architecture to define statically-configured IPC communication between user-level daemons.

### Layer 2: Minimal Userspace Drivers
- **Drivers:** USB, Framebuffer display, NIC, Wi-Fi.
- These run in entirely isolated userspace components. If a driver crashes or is compromised, it cannot compromise the kernel or other services.

### Layer 3: System Utilities & Networking
- **C Library:** musl libc for a minimal footprint.
- **Utilities:** BusyBox for standard Unix tools (invisible to the end user).
- **Network Stack:** lwIP embedded TCP/IP stack running isolated from the application layer.

### Layer 4: Privacy Daemon
- Sits between the network stack and the browser.
- Manages Tor, I2P, and Lokinet circuits.
- Handles automatic IP/circuit rotation every 30–90 seconds.
- Handles blockchain-based DNS resolution (Handshake/ENS).
- **Kill Switch:** Enforces capability-level blocking of all outbound traffic if circuits drop. There is no physical route for the browser to bypass this daemon.

### Layer 5: User Interface (Hardened Browser)
- There is no desktop environment or window manager.
- A hardened Firefox fork operates directly on the framebuffer.
- All OS utilities (File Manager, Terminal, Settings, Media Player) are implemented as local web applications/extensions running securely within the browser sandbox.

## Key Design Principles
1. **Amnesic by Default:** The OS boots from a read-only SquashFS image and runs entirely in RAM. Nothing is written to disk unless explicitly authorized via an encrypted persistence layer.
2. **Capability-Based Security:** There is no "root" or superuser. Each daemon gets only the memory and IPC capabilities it strictly requires.
3. **Fail Closed:** If anonymization fails, networking drops entirely. No direct connections to the clearweb are permitted.
