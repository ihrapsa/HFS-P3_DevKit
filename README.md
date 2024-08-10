# HFS-P3_DevKit
Developping Kit and resources gathered while reverse engineering the chinese HFS-P3 radiation dosimeter pen.

<details>
<summary> <font size="4"> <strong> 1. Device Pictures </strong> </font></summary>

|                   |                            |                            |
|-------------------|----------------------------|----------------------------|
|**External Photos**|![Image 1](img/external1.png) | ![Image 2](img/external2.png) |
|**Internal Photos**| ![Image 1](img/internal1.png) | ![Image 2](img/internal2.png) |

* Some of the pictures are extracted from radmon.org, so credits to Simomax who thurughly documented this.
</details>

<details>
<summary> <font size="4"> <strong> 2. Device Specs </strong> </font></summary>

| Component         | Specification                |
|-------------------|------------------------------|
| MCU               | FM33LC043N - Arm Cortex M0    |
| GM Tube           | HH614                         |
| Screen            | 128x32 / 14 pin SSD1316 OLED  |
| Battery           | 150 mAh                       |
| Ports             | USB-C power only              |
| Debug interface   | SWD                           |
| Buttons           | #1 Menu/Down <br> #2 Power    |
| LEDs              | LED1 Green <br> LED2 Red      |
| Other             | #1 Buzzer                     |


</details>


<details>
<summary> <font size="4"> <strong> 3. Board Schematic </strong> </font></summary>

[EasyEDA Pro Project](resources/EasyEDA_ProProject_HFS-P3_schematic_2024-08-10.epro) of the Schematic  

[PDF ](resources/HFS-P3_rev_eng_schematic_2024-08-10.pdf) Schematic  

</details>

<details>
<summary> <font size="4"> <strong> 4. MCU Specs & GPIOs </strong> </font></summary>

The **FM33LC043N** is a low power 64MHz Arm Cortex M0 MCU with **256KB Flash** and **24KB of SRAM** in a QFN32 form. 32 pins, 28 GPIOs, (of which 1xSWD, 2xSPIs and 4/2 UART/LPUART interfaces, 9x12bit SAR-ADC channels) and an internal temperature sensor. It lacks USB support and I2C so that latter needs to be bitbanged (as it will be required for oled driver communication).


- <details>
    <summary><strong>Specs Summary: </strong></summary>

    |                     | FM33LC0x3N |
    |---------------------|------------|
    | **CPU**             | Cortex-M0  |
    | **Max Freq.**       |   64MHz    |
    | **Flash**           | 256KB      |
    | **RAM**             | 24KB       |
    | **AES**             |  1         |
    | **RNG**             |  1         |
    | **Timer**           |  1         |
    | ATIM                |  1         |
    | GTIM                |  2         |
    | BSTIM32             |  1         |
    | LPTIM32             |  1         |
    | systick             |  1         |
    | **RTC/WWDT/IWD T**  | 1/1/1      |
    | **SPI**             | 2          |
    | **I2C**             | -          |
    | **UART**            | 4          |
    | **LPUART**          | -          |
    | **USB1.1 FS**       | -          |
    | **GPIO**            | 28         |
    | **OPA**             | 2          |
    | **12bit SAR-ADC**   | 9ch        |
    | **TempSensor**      |  1         |

    </details>

- <details>
    <summary><strong> MCU Pinout </strong></summary>

    ![MCU pinout](img/FM33LC0x3N.png)

  </details>


On the HFS-P3 board the MCU has the following GPIOs connections:



</details>

<details>
<summary> <font size="4"> <strong> 5. Links & Resources </strong> </font> </summary>

|  Item  |Description|  URL   |
|--------|-----------|--------|
|MFANG Tool - Fudan Micro Online Platform | Online GUI Platform to build MDK-ARM Keil uVision Base Projects (Clock setup, GPIOs, Debug interface)| https://mfang2.fmdevelopers.com.cn |
| FM33LC0XXN DevBoard User Manual | Blog Post With step by step instructions on chip schematic, capailites and developpment environment setup including MFANG base project generation, Arm Keil MDK uVison setup and Project Examples. | https://www.yuque.com/xinluyao/fm33lc0xxn |
| Fudan Micro Developpers Official Forum | Example Projects and different coding/developpment issues  | https://www.fmdevelopers.com.cn/forum.php?mod=viewthread&tid=1749 |
| Radmon Forum  | Forum where I first found thurough documentation about this device. The thread eventually stalled due to SWD connection issues, that luckily I figured | https://radmon.org/index.php/forum/commericial-geiger-counters/1287-hfs-p3-pen-geiger-counter-dosimeter |


</details>


---------------------

### Prepairing

#### 1. Wiring:
![alt text](img/SWD.png)
Note: For some reason, SWD will not work if battery is desoldered. Connecting the 3.3v line to the +V input on the board will make it enter debug mode again.
#### 2. Programmer & Software:
I used a chinese ST-Link V2 clone with the firmware modified to work with [J-Link Commander](https://www.segger.com/downloads/jlink/). This was really messy<font color="red">*</font> so my recommandation is to use a proper [Segger JLink debug probe](https://www.segger.com/products/debug-probes/j-link/).

<font color="red">*</font><font size="2">You need [SEGGER STLinkReflash Utility](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/) to flash `J-Link firmware` in place of `STLink` (same app will be able to restore it if ever needed). If the debugger is a chinese clone you might have to use a [patched](resources/STLinkReflash_190812) version of the reflash utility instead to bypass the error of the unsupported device.</font>

With an original J-Link debug probe you might be able to use any version of [J-Link Commander](https://www.segger.com/downloads/jlink/). For my clone, only a couple of versions seemed to have worked (v6.18c, v6.12).


#### 3. Dumping
1. Connect the debug probe to the board
2. Plug the USB inside the PC (currently only Windows 10/11 tested)
3. Run `J-Link Commander` as Administrator
4. Type `connect` -> choose `FM33LC04X` -> type `S` for SWD -> enter for default `4000KHz `speed. If any error at this point run `connect` again and agin until the debug probe succesfully halts the cpu and establishes a connection (see below).

![alt text](img/connect_jlink.png)

To dump the flash use the `savebin` command: 

`savebin <filename>, <addr>, <NumBytes> (hex)`
```
savebin C:\path\where\to\dump.bin, 0x0, 40000
```
![alt text](img/savebin_jlink.png)

`0x0` is the start address, `40000` is the number of bytes (in hex) to dump (according to datasheet that is the size of the flash), in this case `40000 hex = 262144 Bytes`:

#### 4. Downloading to Flash

To Download a binary to flash use the `loadbin` command:

`loadbin <filename>, <addr>`
```
loadbin C:\path\of\the\file_to_flash.bin, 0x0
```

![alt text](img/loadbin_jlink.png)