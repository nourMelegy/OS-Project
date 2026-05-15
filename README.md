# OS-Project

A comprehensive Operating Systems project implementing core OS concepts and functionality.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Core Components](#core-components)

## Overview

OS-Project is an educational operating systems implementation that demonstrates fundamental OS concepts including process management, memory management, file systems, and scheduling algorithms. This project explores the scientific principles and algorithms that form the foundation of modern operating systems.

## Features

- **Process Management**: Process creation, scheduling, and context switching with support for multi-level queue scheduling
- **Memory Management**: Virtual memory implementation with paging algorithms, page replacement strategies (LRU, FIFO, Optimal), and memory allocation techniques
- **File System**: Inode-based file organization, directory structures, and I/O operations with caching mechanisms
- **Scheduling Algorithms**: CPU scheduling implementations including Round Robin, Priority Scheduling, Shortest Job First (SJF), and Multilevel Feedback Queue
- **Synchronization Primitives**: Mutex locks, semaphores, and condition variables for thread synchronization and deadlock prevention

## Project Structure

```
OS-Project/
├── src/                           # Source implementation
│   ├── kernel/                    # Core kernel operations
│   │   ├── scheduler.c           # CPU scheduling algorithms
│   │   ├── context_switch.c      # Context switching mechanism
│   │   └── interrupt_handler.c   # Interrupt handling
│   ├── processes/                # Process management
│   │   ├── process_table.c       # Process control blocks
│   │   ├── process_creation.c    # Fork and process spawning
│   │   └── process_termination.c # Process cleanup
│   ├── memory/                   # Memory management
│   │   ├── page_table.c          # Virtual memory mapping
│   │   ├── page_replacement.c    # Page eviction algorithms
│   │   ├── malloc.c              # Memory allocation
│   │   └── tlb.c                 # Translation lookaside buffer
│   └── filesystem/               # File system implementation
│       ├── inode.c               # Inode structure and operations
│       ├── directory.c           # Directory management
│       ├── file_operations.c     # Read/write operations
│       └── disk_scheduler.c      # I/O scheduling
├── include/                      # Header files and data structures
├── tests/                        # Unit and integration tests
└── README.md                     # This file
```

## Core Components

### Process Management
Implements the complete lifecycle of processes including creation, execution, and termination. The process table maintains process control blocks (PCBs) that store process state, registers, memory allocations, and I/O information. Supports context switching to enable the illusion of concurrent execution on single or multi-core systems.

### CPU Scheduling
Multiple scheduling algorithms are implemented to demonstrate different approaches to CPU resource allocation:
- **Round Robin**: Time-slice based scheduling for fairness
- **Priority Scheduling**: Processes execute based on assigned priority levels
- **Shortest Job First (SJF)**: Minimizes average waiting time
- **Multilevel Feedback Queue**: Adaptive scheduling based on process behavior

### Memory Management
Implements virtual memory to decouple logical address space from physical memory:
- **Paging**: Fixed-size memory blocks for efficient allocation and fragmentation reduction
- **Page Replacement Algorithms**: LRU, FIFO, and Optimal page replacement strategies
- **Translation Lookaside Buffer (TLB)**: Cache for virtual-to-physical address translation
- **Memory Allocation**: Dynamic memory management with buddy system or segmentation support

### File System
Hierarchical file organization with inode-based structure:
- **Inode Structure**: Metadata storage including file size, permissions, timestamps, and block pointers
- **Directory Management**: Hierarchical file organization and namespace management
- **I/O Scheduling**: Disk head scheduling algorithms (SCAN, C-SCAN) to optimize I/O performance
- **Caching**: Buffer cache to reduce disk access latency

### Synchronization
Thread-safe resource access through synchronization primitives:
- **Mutex Locks**: Mutual exclusion for critical sections
- **Semaphores**: Counting semaphores for resource management
- **Condition Variables**: Thread coordination and signaling
- **Deadlock Prevention**: Detection and recovery mechanisms

---

**Created by**: nourMelegy  
**Last Updated**: 2026-05-15
