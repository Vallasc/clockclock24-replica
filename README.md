# ClockClock 24 Replica
This is my personal implementation of the "ClockClock 24" by Humans Since 1982.

| DISCLAIMER: All files in this repository are intended for personal use only. All design rights go to Humans Since 1982.|
| - |

Clockclock is a kinetic sculpture design by Humans Since 1982, consisting of 24 clocks which by animating show the time in digital format. My attempt to create a replica started by designing the pcb and the case that houses them, and then writing the software to drive the clocks.

##### Table of Contents:
1. [Hardware](#hardware)
    1. [Motors](#software)
    1. [Microcontrollers](#)
    1. [BOM (Bill Of Materials)](#)
    2. [PCB]()
2. [Software](#software)
    1. [Communicaation](#)
    1. [Master](#)
    2. [Slave]()
## Hardware
The entire clock is composed by 24 sub-clocks, arranged on a 8x3 matrix, that are fully independent. Each clock module has two motors that move the two lancets.

### Motors
After careful research, VID28-05 (or BKA30D-R5) stepper motor were chosen. It is made by two separate motors that drives the two shaft individually, that is perfect for attaching the lancets.

<img align="right" width="400"  src="/images/vid-28.gif">
These mototors are low power and can be runned directly by the microcontroller, but i didn't want to put stress on the GPIO so I used a dedicated controller. Specifically the AX1201728SG (equivalent of X12.017 and VID6606), this chip offer advantages over running the motor directly such as: uses of microstepping, it requires only two GPIO pins per motor, it protects the microprocessor from the inductive effects of the motor coils and it requires lower current to be runned by the microcontroller.
