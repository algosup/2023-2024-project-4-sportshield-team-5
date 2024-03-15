# <h1 align="center">Functional Specifications</h1>

<p align="right">created : 15/03/2024<br>last modified : 15/03/2024</p>

<details>
<summary>Table Of Content</summary>



</details>

# 1 Introduction

## 1.1 Project Overview

We were asked to improve the embedded software of a prototype product made by the company "Coris Innovation". This product is a security device called "SportShield", designed to secure sports equipment, this device is equipped with sensors to detect movement and is programmed to activate an alarm and notify the user on a smartphone application.

The software is currently developed in a C/C++ environment with added libraries meaning that we have to continue using this language to ensure that already implemented features will stay operational.

**The prototype's current features are:**

- Connexion to the device via BLE
- Activate / Deactivate the anti-theft function via BLE
- Unlock the security cable via BLE
- Alarm
    - 3 light sounds when a small shock is detected
    - 5 long loud sounds when a big shock is detected
- Send movement notification via a SIM card (GPS coordinates recorded via GPRS)
- Send GPS position and Battery level every 15 minutes via a SIM card
- Sleep mode 
    - GPS and GPRS functionalities are only powered when information should be sent
    - When the antitheft system is deactivated, and no movements are detected for 5 minutes, then the BLE function is disabled. As soon as a movement is detected, the BLE turns on again

**The features we were tasked with improving:**

- Battery Consomption Optimisation
    - Improve the energy efficiency of the system
    - Manage low battery situation
    - Increase the battery lifespan (keeping charge between 20% and 80%)
- Alarm Management & Simultaneous actions
    - Add the possibility to stop the alarm when it rings, even if the ringing cycle is not finished
    - Allow the alarm to be active while sending notification
    - Improve the management of interruptions
- Security
    - Increase the security level of the device to connect and access key features (activate/deactivate alarm & unlock cable)
- Device Management With NFC
    - Used to activate/deactivate the anti-theft system and unlock the cable via smartphone and SportShield app.

## 1.2 Project Definition

### 1.2.1 Vision

We are making improvements on the current prototype. We will upgrade the energy efficiency along with the security of the device and its connection capabilities.

### 1.2.2 Objectives

- Make improvements on the embedded software (add asked new features and upgrade current ones)
- Make improvements on the energy efficiency
- Use C/C++ environment
- Keep the current features running

### 1.2.3 Scope

| In Scope |
| --- |
| Modify & Improve the embedded software |
| Create a User Manual |
| Use C/C++ |

| Out Of Scope |
| --- |
| Modify & Improve the smartphone application |
| Modify & Improve the hardware of the prototype |

### 1.2.4 Deliverables

| Name | Type | Deadline | Link |
| --- | --- | :-: | -: |
| Functional Specification | Document(Markdown) | 18/03/2024 | [functional-specification.md](./functional-specification.md) |
| Technical Specification | Document(Markdown) | 26/03/2024 | [technical-specification.md](./functional-specification.md) |
| Weekly Reports | Document(Markdown) | Every Friday | [weekly-reports/](./management/weekly-reports/) |
| Test Plan | Document(Markdown) | 10/04/2024 | [test-plan.md](./qa/test-plan.md) |
| User Manual | Document(PDF) | 10/04/2024 | [user-manual.pdf](./functional-specification.md) |

## 1.3 Project Organisation

### 1.3.1 Project Representative

### 1.3.2 Stakeholders

### 1.3.3 Project Roles

### 1.3.4 Project Reviewers