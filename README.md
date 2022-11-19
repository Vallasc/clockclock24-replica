# ClockClock 24 Replica
This is my personal implementation of the "ClockClock 24" by Humans Since 1982.

<div align="center">
<img width="900"  src="/images/photo1.jpg">
</div>

| DISCLAIMER: All files in this repository are intended for personal use only. All design rights go to Humans Since 1982.|
| - |

Clockclock is a kinetic sculpture design by Humans Since 1982, consisting of 24 clocks which by animating show the time in digital format. My attempt to create a replica started by designing the PCB and the case that houses them, and then writing the software to drive the clocks.

---
### Table of Contents:
1. [Hardware](#hardware)
    1. [Motor](#motor)
    1. [Microcontroller](#microcontroller)
    2. [PCB](#pcb)
2. [Software](#software)
    1. [Communicaation](#)
    1. [Master](#)
    2. [Slave]()
    2. [Web Interface]()
2. [Final result](#)

---
## Hardware
The entire clock is composed by 24 sub-clocks, arranged on a 8x3 matrix, that are fully independent. I design a module that contains 3 clocks and it can show vertically an half digit. A total of 8 boards are used to make up the entire clock,  nothing prohibits adding more, thus increasing the number of digits.

### Motor
After careful research, VID28-05 (or BKA30D-R5) stepper motor were chosen. It is made by two separate motors that drives the two shaft individually, that is perfect for attaching the lancets. Moreover, this type is sold by some vendor (search on Aliexpress) with no endstops and can turn freely.

<img align="right" width="400"  src="/images/vid-28.gif">
These mototors are low power and can be runned directly by the microcontroller, but i didn't want to put stress on the GPIO so I used a dedicated controller. Specifically the AX1201728SG (equivalent of X12.017 and VID6606), this chip offer advantages over running the motor directly such as: uses of microstepping, it requires only two GPIO pins per motor, it protects the microprocessor from the inductive effects of the motor coils and it requires lower current to be runned by the microcontroller.

### Microcontroller
Two types of microcontrollers are used: raspberry-pi-pico (RP2040) and ESP8266. The main reason of this choice is that ESP8266 has wifi capabilities, the design was made before the release of raspberry-pi-pico-w, now the PCB could be simplified even more. ESP8266 acts as a master and sends commands to the pico boards that runs directly the motors. I chose raspberry-pi-pico because it has a lot of pins, it is reliable and it is available on the market at a relative low price.

### PCB
The schematic and all the gerber files are placed in the /pcb directory. 
<div align="center">
<img align="center" width="800"  src="/images/pcb.jpg">
</div>
#### Schematic
<div align="center">
<img width="800"  src="/images/schematic.jpg">
</div>
Each board has 2 stepper controllers that in total can run 8 motors. As a design choice, the board has only 3 clocks (6 motors), so 2 outputs are unused. The schematic also contains 6 hall sendors which were to be used to automatically adjust the position of the hands, but in the end they were not added to the final prototype because the magnets were not powerful enough to trigger the sensors. Each board also has housing for ESP8266MINI but it should only be installed on one board (master). This makes it possible to produce only one type of printed circuit board to which components will be soldered according to purpose. Master talks to slaves using I2C protocol, each board i connected to the next in daisy chain. The board is powered with 5v and should approximately consume 150 mAh.

#### Bill Of Materials (full clock)
<div align="center">

| Quantity | Name | 
|-|-|
| 8 | PCB board |
| 24 | VID28-05 (or BKA30D-R5) 360 degree mod |
| 16 | AX1201728SG (or VID6606) |
| 8 | Raspberry pi pico |
| 1 | ESP8266 MINI |
| 8 | DIP switch 4 switches |
| 16 | JST XH 2.54 MALE 4 pins |
| 14 | JST XH 2.54 FEMALE 4 pins (for connection cables) |
| 8 | (Optional) power connector |

</div>
---

## Software
