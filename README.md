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
    2. [Microcontroller](#microcontroller)
    3. [PCB](#pcb)
2. [Software](#software)
    1. [Master](#master)
    2. [Slave](#slave)
    3. [Web Interface](#web-interface)
3. [Final result](#final-result)

---

## Hardware
The entire clock is composed by 24 sub-clocks, arranged on a 8x3 matrix, that are fully independent. I design a module that contains 3 clocks and it can show vertically an half digit. A total of 8 boards are used to make up the entire clock,  nothing prohibits adding more, thus increasing the number of digits.

### Motor
After careful research, *VID28-05* (or *BKA30D-R5*) stepper motor were chosen. It is made by two separate motors that drives the two shaft individually, that is perfect for attaching the lancets. Moreover, this type is sold by some vendor (search on Aliexpress) with no endstops and can turn freely.

<img align="right" width="400"  src="/images/vid-28.gif">
These mototors are low power and can be runned directly by the microcontroller, but i didn't want to put stress on the GPIO so I used a dedicated controller. Specifically the *AX1201728SG* (equivalent of *X12.017* and *VID6606*), this chip offer advantages over running the motor directly such as: uses of microstepping, it requires only two GPIO pins per motor, it protects the microprocessor from the inductive effects of the motor coils and it requires lower current to be runned by the microcontroller.

### Microcontroller
Two types of microcontrollers are used: **Raspberry-pi-pico** (RP2040) and **ESP8266**. The main reason of this choice is that ESP8266 has wifi capabilities, the design was made before the release of Raspberry-pi-pico-w, now the PCB could be simplified even more. ESP8266 acts as a master and sends commands to the pico boards that runs directly the motors. I chose raspberry-pi-pico because it has a lot of pins, it is reliable and it is available on the market at a relative low price.

### PCB
The schematic and all the gerber files are placed in the *./pcb* directory. 
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
Software side, two different projects were made for master and slave, [PlatformIO](https://platformio.org/)  was used for both of them. The project setup is easy with PlatformIO because it automatically downloads the necessary files. The only parameters you may need to change is *upload_port* and *monitor_port* in *platformio.ini* .

### Slave
The slave code is runned by Raspberry pico, it recives the taraget hands position throw I2C protocol and moves motors accordingly. The I2C address is taken from the position of the 4 switches on the board.

To have a fluid aniamtion, motion must be done using an acceleration curve, so it is used [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) library. 
The code is multicore, one core gets bytes from the I2C bus and saves them in the internal buffer, the other core manage to run directly the stepper motors, doing so the animation is not stopped by the I2C interrupts.


### Master
The master code is runned by ESP8266, it is in charge of send actual hands position to all the boards and to serve the web application.

At powered on, tries to connect to the configured WiFi network, if it fails then makes an open network. Time synchronization is made, if internet connection is available, using NTP service or it is taken from the client browser that visits the web app. When time changes it send to the corresponding board the new hands position, the way in which these are to be moved (clockwise, counter clockwise, min distance, max distance, etc.), the speed and the acceleration. In the meantime it responds to the requested made by the web application made available at http://clockclock24.local .

* Animation modes available (for now):
    1. **Lazy**, moves only clock hands that needs to be changed by traveling the minimum distance.
    2. **Fun**, moves all clock's hands in clockwise direction.
    3. **Waves**, reproduce a domino animation.

### Web Interface
On the web application is shown an exact copy of the clock, also animations are cloned and occurs at the same time. The interface allows you to change clock mode, set the hours when it should not work  and change the wireless connection.

Credits for the clock's web design animation go to [Manuel Wieser](https://manu.ninja/).

<div align="center">
<img width="800"  src="/images/web.jpg">
</div>

---

## Final result