# Linux IPC – Message Queue Example

This repository demonstrates **Inter-Process Communication (IPC)** in Linux using
**System V Message Queues**. Two independent processes communicate via a
kernel-managed message queue without direct knowledge of each other.

---

## Overview

- One process acts as a **sender**, writing a message to the message queue.
- Another process acts as a **receiver**, reading the message from the queue.
- The Linux kernel manages message routing and synchronization.

This example helps understand:
- How System V message queues work
- How processes communicate via kernel-managed IPC
- Blocking behavior of `msgrcv`
- Proper cleanup of IPC resources

---

## Files

- `sender.c`  
  Creates a message queue (if not present) and sends a message.

- `receiver.c`  
  Receives a message from the message queue and removes the queue.

---

## Build Instructions

Compile both programs using GCC:

```bash
gcc sender.c -o sender
gcc receiver.c -o receiver
