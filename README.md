# Linux IPC Examples (System V)

This repository demonstrates **Inter-Process Communication (IPC)** in Linux using
**System V mechanisms** such as **Message Queues** and **Semaphores**.  
These examples show how independent processes communicate and synchronize
through kernel-managed IPC resources.

---

# Linux IPC – Message Queue Example

This example demonstrates **System V Message Queues**, where two independent
processes communicate without direct knowledge of each other.

## Overview

- One process acts as a **sender**, writing a message to the message queue.
- Another process acts as a **receiver**, reading the message from the queue.
- The Linux kernel manages message routing and synchronization.

This example helps understand:
- How System V message queues work
- How processes communicate via kernel-managed IPC
- Blocking behavior of `msgrcv()`
- Proper cleanup of IPC resources

## Files

- `sender.c`  
  Creates a message queue (if not present) and sends a message.

- `receiver.c`  
  Receives a message from the message queue and removes the queue.

## Build Instructions

Compile both programs using GCC:

```bash
gcc sender.c -o sender
gcc receiver.c -o receiver
Run Instructions

Open two terminals.

Terminal 1 (Receiver):

./receiver


Terminal 2 (Sender):

./sender

Linux IPC – Semaphore Example

This example demonstrates the use of System V Semaphores for
process synchronization in Linux.

What is a Semaphore?

A semaphore is an Inter-Process Communication (IPC) mechanism used to
control access to shared resources such as files, logs, or shared memory.
It ensures that multiple processes do not access a critical resource
simultaneously.

Why Semaphores?

Prevent race conditions

Provide mutual exclusion

Synchronize access to shared resources

Critical Section

A critical section is the part of a program where a process accesses a
shared resource. Using semaphores ensures that only one process enters the
critical section at a time, while other processes wait.

How It Works

A semaphore is initialized with a value

A process performs a wait (P) operation before entering the critical section

After completing its work, the process performs a signal (V) operation

Waiting processes are allowed to proceed one by one

System Calls Used

semget()

semctl()

semop()

Use Case

This example simulates multiple processes trying to access a shared resource,
ensuring safe and synchronized execution.

Cleanup

To remove any leftover IPC objects:

ipcs
ipcrm -q <queue_id>
ipcrm -s <semaphore_id>



---
Is this conversation helpful so far?
