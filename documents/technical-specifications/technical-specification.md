# Technical Specifications

Algosup - Team 5 - Project n°4 - Sport Shield


| Role | Name |
|---|---|
| Project Manager | Vivien TSONGUE |
| Program Manager | Arthur LEMOINE |
| Tech Lead | Benoît DE KEYN |
| Software Developer | Aurélien FERNANDEZ |
| Quality Assurance | Antoine PREVOST |
| Technical Writer | Clémentine CUREL |

<details>

<summary>

# Table of Content

</summary>

- [Technical Specifications](#technical-specifications)
- [Table of Content](#table-of-content)
- [1. Introduction](#1-introduction)
- [Document Purpose \& Definition](#document-purpose--definition)
- [Glossary](#glossary)
- [Project Overview](#project-overview)
  - [Project Brief](#project-brief)
  - [Hardware](#hardware)
  - [Software](#software)
  - [Ressources](#ressources)
    - [Documentation about components](#documentation-about-components)
      - [Electronic circuit diagrams](#electronic-circuit-diagrams)
- [Set-up the environnement](#set-up-the-environnement)


</details>


# 1. Introduction

# Document Purpose & Definition

The goal of the Technical Specifications is to take the Functional Requirements that define the features, scope, and goals of the project, dissect each requirement, and turn it into instructions, as clear as possible, to guide the development team as well as the quality assurance team in the successful completion of their mission.

We therefore encourage thorough reading of the [Functional Specifications](https://github.com/algosup/2023-2024-project-4-sportshield-team-5/blob/main/documents/functional-specification/functional-specification.md) before further reading.

The goal of the Technical Requirements is to clarify as many dark areas as possible to prevent the engineers from making decisions
In a sense, while the Functional Requirements represent the "What/Why" aspect of the project, the Technical Requirements are supposed to represent the "How" of the project.

With that being said, we will try to cover as many functional and non-functional aspects of the project while making technological and architectural decisions, evaluating those decisions, measuring their associated risks and impact (providing mitigation), and comparing those to other potential solutions.

The document should also benefit other stakeholders and project owners by giving insight into our methodology and may serve as a future reference for maintenance or simple documentation purposes.

# Glossary

# Project Overview

## Project Brief

As fully explained in the [Functional Specifications](https://github.com/algosup/2023-2024-project-4-sportshield-team-5/blob/main/documents/functional-specification/functional-specification.md), our goal in this project is to improve the firmware of an embedded system called "Sport Shield". This "Sport Shield" is an anti-theft device intended only for snowboards and skis at present. It consists of a box equipped with a set of electronic and mechanical equipment, containing a steel cable to be wrapped around the object to be secured.

How does this Sport Shield work?

When the cable is wrapped and the box is in a locked state, the device is looking for any physical disturbances. If any movement or vibration of the box is detected as a possible theft, it turns on a strong alarm, more or less loud according to the level of disturbance (intensity and duration of the movement). At the same time, it sends a warning notification to the owner by a dedicated smartphone application, using the internet network.
To stop the alarm or unlock the shield, the owner uses the application and it processes via Bluetooth or NFC.
Also, during the locked period, the device will send regularly the GPS position and battery level by the 2G network, to a remote server communicating with the app.
The aim is to make the sports shield as rustic and resilient as possible, minimizing direct user interactions with the hardware and keeping them remote, via the Bluetooth app.

The company who gave us this project, explained all of it during a presentation at the very beginning. Here is the [PDF of the presentation](files/SportShield-project-Brief-AlgoSup-Embedded-software-optimization.pdf).

## Hardware

This project is not about the entire conception of the device from scratch. To be able to develop the firmware of the device we needed only the electronic and informatic parts of the project being developed. Thus, we received :

- the electronic card (which gathers and links by soldered circuits all the micro-electronic) of the embedded system, which includes :
  - **A programmable board**: a "Seeed Xiao BLE nRF52840 Sense" (more details below)
  - **SIM card holder**: a "SIM800L GSM/GPRS 2G" version "S2-1065J-Z143N"
  - **GPS module**: a "CD-PA1010D GNSS patch antenna module"
  - **12V DC converter** : Based on a MT3608 DC-DC converter microship, the circuit provides exactly 12.7V (the MT3608 handles "2V-24V ➔ 3V-28V" with 2A).
  - **4V DC converter** : Based on the same MT3608 as above, this circuit provides exactly 4.13V.
  - 3x **electronic-switch** circuits : basically, it is just a MOSFET transistor. Two are a "DMG1012t" and the last is not referenced.
  - 4x **2 pins plugs**: to connect the external components  
![map of the whole board](files/circuits.png)
- the pluggable components :
  - **battery** : a "LP603449" Lithium-Polymer battery ► 3.7V ► 1100mAh ► 4.3Wh (2 pins plug)
  - **electromagnetic lock** : a 12V/500mA DC electromagnetic lock (2 pins plug)
  - **buzzer** : a 3V-24V DC piezzo-electric buzzer (2 pins plug)
  - **NFC antenna** : a "Molex 1462360031" NFC antenna directly plugged on the main board for NFC communication. (2 pins plug)
  - **2G antenna** : pluggable on the SIM module (2 pins plug)
  - **SIM card** : a 2G nano-SIM in its micro-SIM adaptator, pluggable in the SIM holder  
![all the pluggable components](files/components.png)

## Software

This project uses C/C++ through the Arduino® IDE, to develop the firmware of the Seeed board.  
The company gave us their first version of the software they coded ([here to download](files/arduino-code-05-03.zip)), which includes all the features explained in [their presentation](files/SportShield-project-Brief-AlgoSup-Embedded-software-optimization.pdf), and in the [Functional Specifications](https://github.com/algosup/2023-2024-project-4-sportshield-team-5/blob/main/documents/functional-specification/functional-specification.md).

The usage of public libraries is allowed.

## Ressources

For the Hardware, we received some documentation about the components and also the old schematics of the electronic circuit :

### Documentation about components
- [*Xiao NRF52840 sense* electronic architechture](files/Seeed-Studio-XIAO-nRF52840-Sense-v1.1.pdf) *(provided by the company)*
- [NRF52840 microcontroller datasheet](files/nRF52840-PS-v1.5.pdf)
- [GPS module datasheet](files/CD-PA1010D-datasheet-v.02.pdf) *(provided by the company)*
- [SIM module datasheet](files/SIM800L-SIMCom.pdf) *(provided by the company)*
- [Li-Po Battery datasheet](files/batterie-LP603449.pdf) *(provided by the company)*

![gps, SIM, and seeed pinout](files/main-components-pinout.png)
#### Electronic circuit diagrams
The power management of the board follows this diagram :
![Power management diagram](files/power_diagram.png)
Here, the connectics for the Seeed Board, the SIM module and the GPS module :
![SIM, GPS, and Seeed board connectics](files/easyEDA-connectics.png)([easyEDA sketch here](files/easyEDA-connectics.json))  

If you want to dive into the electronic circuits of the PCB, there is the [PCB circuit schematic](files/SportShield-Electronics-diagram.png) provided by the company. However, this scematic is not up to date. The most important is the absence of the Q5 MOSFET used to cut the battery to other components using the control pin D9.

# Set-up the environnement

In order to improve the software of the device, you need to :

1. Download and install the Arduino® IDE from [the official website](https://www.arduino.cc/en/software)

2. Open the software, and click on 'File'->'Preferences' . Then, copy-paste this URL : "https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json" in the last blank section of the window. Then, click 'OK' :
![where to copy-paste the URL](files/tutorial-arduino-1.png)

3. Open the board manager and install the "Seeed NRF52 mbed-enabled Boards" driver.  
   <img src="files/tutorial-arduino-2.png" height="500px">
   
4.
