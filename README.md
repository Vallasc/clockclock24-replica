# ClockClock 24 Replica
This is my personal implementation of the "ClockClock 24" by [Humans Since 1982](https://www.humanssince1982.com/).

<div align="center">
<img width="900"  src="/images/photo1.jpg">
</div>

| DISCLAIMER: All files in this repository are intended for personal use only. All design rights go to [Humans Since 1982](https://www.humanssince1982.com/).|
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
    4. [Hands calibration](#hands-calibration)
3. [Case and clock's hands](#case-and-clocks-hands)
4. [Final result](#final-result)

---

## Hardware
The entire clock is composed of 24 sub-clocks, arranged on a 8x3 matrix, that are fully independent. A module that contains 3 clocks and can show vertically an half digit has been designed. A total of 8 boards are used to make up the entire clock, nothing prohibits adding more, thus increasing the number of digits.

### Motor
After careful research, *VID28-05* (or *BKA30D-R5*) stepper motor was chosen. It is made by two separate motors that drive the two shafts individually, that is perfect for attaching the hands. Moreover, this type is sold by some vendors (search on Aliexpress) with no endstops and can turn freely.

<img align="right" width="400"  src="/images/vid-28.gif">

These motors are low power and can be runned directly by the microcontroller, but in order not to stress the GPIO a dedicated controller was used. Specifically the *AX1201728SG* (equivalent of *X12.017* and *VID6606* chips) offers advantages over running the motor directly such as uses of microstepping. It requires only two GPIO pins per motor, protects the microprocessor from the inductive effects of the motor coils and requires lower current to be runned by the microcontroller.

### Microcontroller
Two types of microcontrollers are used: **Raspberry-pi-pico** (RP2040) and **ESP8266**. The main reason for this choice is that ESP8266 has wifi capabilities, the design was made before the release of Raspberry-pi-pico-w, now the PCB could be simplified even more. ESP8266 acts as a master and sends commands to the pico boards that run directly the motors. Raspberry-pi-picoIt was chosen because it has a lot of pins, it is reliable and it is available on the market at a relatively low price.

### PCB
The schematic and all the gerber files are placed in the *./pcb* directory. 
<div align="center">
<img align="center" width="800"  src="/images/pcb.jpg">
</div>

#### Schematic
<div align="center">
<img width="800"  src="/images/schematic.jpg">
</div>
Each board has 2 stepper controllers that in total can run 8 motors. As a design choice, the board has only 3 clocks (6 motors), so 2 outputs are unused. The schematic also contains 6 hall sensors which were to be used to automatically adjust the position of the hands, but in the end they were not added to the final prototype because the magnets were not powerful enough to trigger the sensors. Each board has also housing for ESP8266MINI but it should only be installed on one board (master). This makes it possible to produce only one type of printed circuit board to which components will be soldered according to purpose. Master talks to slaves using I2C protocol, each board is connected to the next in daisy chain. All the boards are powered with 5v and should approximately consume at peak times 1.7 Ah .

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
On the software side, two different projects were made for master and slave, [PlatformIO](https://platformio.org/)  was used for both of them. The project setup is easy with PlatformIO because it automatically downloads the necessary files. The only parameters you may need to change is *upload_port* and *monitor_port* in *platformio.ini* .

### Slave
The slave code is runned by Raspberry pico, it receives the target hands position through I2C protocol and moves motors accordingly. The I2C address is taken from the position of the 4 switches on the board.

To have a fluid animation, motion must be done using an acceleration curve, so it is used [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) library. 
The code is multicore, one core gets bytes from the I2C bus and saves them in the internal buffer, the other core manages to run directly the stepper motors, doing so the animation is not stopped by the I2C interrupts.


### Master
The master code is runned by ESP8266, it is in charge of sending actual hands position to all the boards and to serve the web application.

When powered on, it tries to connect to the configured WiFi network, if it fails then makes an open network. Time synchronization is made, if internet connection is available, using NTP service or it is taken from the client browser that visits the web app. When time changes it sends to the corresponding board the new hands position, the way in which these are to be moved (clockwise, counter clockwise, min distance, max distance, etc.), the speed and the acceleration. In the meantime, it responds to the requests made by the web application made available at http://clockclock24.local.

* Animation modes available (for now):
    1. **Lazy**, moves only clock hands that need to be changed by traveling the minimum distance.
    2. **Fun**, moves all the clock's hands in a clockwise direction.
    3. **Waves**, reproduces a domino animation.

### Web interface
On the web application an exact copy of the clock is shown, animations are also cloned and occur at the same time. The interface allows you to change clock mode, set the hours when it should not work and change the wireless connection.

Credits for the clock's web design animation go to [Manuel Wieser](https://manu.ninja/).

<div align="center">
<img width="500"  src="/images/web.jpg">
</div>

### Hands calibration
Before powering on the clock, you need to manually set all the clock's hands at 6 o'clock. This process needs to be done every time it is disconnected from power.

---

## Case and clock's hands
The case is one piece, it was made by taking a sheet of black MDF and hollowing out the material with a CNC machine. This gives a lot of stiffness to the structure. The clock's hands are laser cutted from a white plexiglass panel.

Since I don't want to receive a letter from Human Since 1982’s lawyers, all design files and the actual clock assembly are omitted, more [here](https://hackaday.com/2020/07/31/patent-law-and-the-legality-of-making-something-similar/).
> “Humans since 1982 have the copyright to works displaying digital time using a grid arrangement of analog clocks…”

---

## Final result
<div align="center">

| Animation type | Result |
| - | - |
| Lazy | ![sasdasd](/images/clock1.gif) |
| Fun | ![sasdasd](/images/clock2.gif) |
| Waves | ![sasdasd](/images/clock3.gif) |

</div>
