# Threat Model

This document outlines what Azula OS is designed to protect against, and importantly, what it is *not* designed to protect against.

## What Azula OS Protects Against

1. **Network Surveillance and Metadata Analysis**
   - **Protection:** All network traffic is forcefully routed through Tor, I2P, or Lokinet. IP and routing circuits are rotated frequently.
   - **Mechanism:** The Privacy Daemon acts as an un-bypassable proxy at the capability level.
2. **DNS Hijacking and Censorship**
   - **Protection:** Centralized DNS is replaced with decentralized blockchain-based resolution (Handshake/ENS).
3. **Remote Code Execution (RCE) Escaping the Browser Sandbox**
   - **Protection:** Even if the browser is compromised, it runs in a heavily restricted CAmkES component. It cannot access the disk (read-only base image), it has no access to the network stack except through the Privacy Daemon, and it has no concept of a "root" user to escalate privileges to.
4. **Driver Vulnerabilities**
   - **Protection:** Unlike Linux, where a compromised Wi-Fi or USB driver yields ring-0 kernel access, Azula OS drivers run in isolated userspace containers. A compromised driver can only affect its specific domain.
5. **Physical Forensics (Post-Seizure)**
   - **Protection:** The system runs entirely in RAM. Upon shutdown, memory is overwritten. There is no persistent swap or temporary storage written to the boot medium unless the user creates a LUKS-encrypted persistence volume.

## What Azula OS Does NOT Protect Against

1. **Compromised Hardware (Firmware/Bootkits)**
   - **Limitation:** If your BIOS/UEFI, CPU microcode, or NIC firmware is compromised before Azula OS boots, all guarantees are void. Azula OS relies on the hardware executing instructions correctly.
2. **User Error / Operational Security (OpSec) Failures**
   - **Limitation:** If a user logs into a personal account (e.g., a mainstream social media site) over the anonymized network, their identity is tied to that session. Azula OS cannot prevent users from voluntarily deanonymizing themselves.
3. **Targeted Zero-Day Exploits on the seL4 Core**
   - **Limitation:** While seL4 is mathematically verified against certain classes of bugs (e.g., buffer overflows) in its specification, hardware side-channels (like Spectre/Meltdown) or bugs in the verification proofs themselves could theoretically exist.
4. **End-to-End Timing Attacks**
   - **Limitation:** Global adversaries observing traffic at both ends of the Tor network can still perform traffic correlation attacks. Azula OS's circuit rotation mitigates some temporal tracking, but cannot defeat a sufficiently capable global passive adversary.
5. **Physical Compromise While Running**
   - **Limitation:** If the machine is physically seized while powered on and unlocked (e.g., a cold boot attack or DMA attack via an insecure port before the system can wipe memory), data in RAM could be recovered.
