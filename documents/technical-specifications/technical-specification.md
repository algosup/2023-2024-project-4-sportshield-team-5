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
  - [Hardware provided](#hardware-provided)
  - [Documentation Provided](#documentation-provided)
  - [Software Provided](#software-provided)


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

## Hardware provided

This project is not about the entire conception of the device from scratch. To be able to develop the firmware of the device we needed only the electronic and informatic parts of the project being developed. Thus, we received :

- the electronic card (which gathers and links by soldered circuits all the micro-electronic) of the embedded system, which includes :
  - **A programmable board**: a "Seeed Xiao BLE nRF52840 Sense" Arduino-based.
  - **SIM card holder**: a "GSM/2G SIM800L Module"
  - **GPS module**: a "Galileo GNSS PA1010D with-antenna module"
  - 12V DC converter : based on a MT3608 DC-DC converter microship, the circuit provides exactly 12.7V (the MT3608 handles "2V-24V ➔ 3V-28V" with 2A)
  - 4V DC converter** : based on the same MT3608 as above, this circuit provides exactly 4.13V.
  - 2x **electronic-switch** circuits : based on a MOSFET "DMG1012t" (basically, it is just a transistor).
  - 4x **2 pins plugs**: to connect the external components.
- the pluggable components :
  - the Li-Po **battery** : a "LP603449" Lithium-Polymer battery ► 3.7V ► 1100mAh ► 4.3Wh
  - the **electromagnetic lock** : a 12V/500mA DC electromagnetic lock
  - the **buzzer** :  

## Documentation Provided

## Software Provided

