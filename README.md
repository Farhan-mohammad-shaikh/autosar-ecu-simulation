\# AUTOSAR-Inspired ECU Simulation in C



\## Overview

Educational simulation of an AUTOSAR-inspired layered architecture:

SWC → RTE → COM, executed via a scheduler loop with communication supervision concepts.



> Disclaimer: This is NOT a full AUTOSAR implementation. It is an AUTOSAR-inspired architecture simulation.



\## Project Structure

\- `application/` : Software Components (SWCs)

\- `rte/`         : RTE layer (interfaces, routing)

\- `com/`         : Communication layer (signals, supervision logic)

\- `scheduler/`   : Periodic task execution

\- `docs/`        : Diagrams and notes



\## Build (example)

```bash

gcc -Wall -Wextra -std=c11 -I./rte -I./com -I./application ^

main.c rte/rte.c com/com.c scheduler/Scheduler.c ^

application/engine\_swc.c application/brake\_swc.c -o ecu\_sim.exe



