# AUTOSAR-Inspired ECU Simulation (C Project)

## Overview

This project is a simplified AUTOSAR-inspired ECU architecture simulation written in C.

It demonstrates:

- Layered architecture (SWC → RTE → COM)
- Periodic scheduler-based execution (1ms / 10ms tasks)
- Sender–Receiver communication model
- Communication supervision using:
  - Updated flag
  - Age counter (timeout monitoring)
- Application-level safe state handling
- Recovery mechanism with anti-flap logic

⚠️ This is NOT a full AUTOSAR implementation.  
It is an educational simulation focused on architectural understanding and communication supervision concepts.


---

## Architecture

The project follows a layered structure inspired by AUTOSAR Classic:

Application Layer (SWC)
        ↓
RTE (Runtime Environment)
        ↓
COM (Signal Buffer + Supervision)
        ↓
Scheduler (OS Simulation)


### Modules

Engine SWC
- Simulates sensor reading
- Computes vehicle speed
- Sends speed via RTE

Brake SWC
- Reads vehicle speed via RTE
- Implements state machine:
  - NORMAL
  - SAFE
  - RECOVERY
- Applies timeout supervision

RTE
- Interface layer between SWC and COM
- Abstracts communication details

COM
- Stores signal buffer
- Maintains updated flag
- Maintains age counter
- Provides atomic access using exclusive areas

Scheduler
- Simulates periodic 1ms and 10ms tasks


---

## Communication Supervision

### Updated Flag
Indicates whether new data has arrived since last read.

### Age Counter
- Incremented every 10ms.
- Reset when new data is transmitted.
- Used for timeout detection.

If:
    age > SPEED_TIMEOUT_TICKS

The Brake SWC transitions to SAFE state.

### Recovery Strategy
- Requires multiple consecutive valid updates.
- Prevents unstable flapping between SAFE and NORMAL.


---

## State Machine (Brake SWC)

NORMAL  
→ Speed is trusted and used normally.

SAFE  
→ Timeout detected. Fallback speed value is used.

RECOVERY  
→ Waiting for stable signal before returning to NORMAL.


---

## Project Structure

autosar-ecu-simulation/

application/
- engine_swc.c
- brake_swc.c

rte/
- rte.c
- rte.h

com/
- com.c
- com.h

scheduler/
- scheduler.c

main.c


---

## Build Instructions

Compile using GCC:

gcc main.c rte/rte.c com/com.c application/engine_swc.c application/brake_swc.c scheduler/scheduler.c -o main

Run:

./main

(Windows PowerShell)

main.exe


---

## Learning Objectives

- Understand AUTOSAR-style layered architecture
- Practice separation of responsibilities
- Implement communication supervision mechanisms
- Apply basic ISO 26262-inspired safety thinking
- Build a portfolio-level embedded systems project


---

## Author

Farhan Mohammad Shaikh  
Embedded Systems Engineer (AUTOSAR-oriented architecture focus)
