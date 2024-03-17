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
- Use a C/C++ environment
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

| Project Owner | Represented by... |
| --- | --- |
| **Coris Innovation** | Florant Anon |
| **ALGOSUP** | Franck Jeannin |
| Bistrel Tsangue | Arthur Lemoine (Program Manager) |

The project sponsors (represented in **bold**) are expected to be in charge of:
- Defining the vision and high-level objectives for the project.
- Approving the requirements, timetable, resources and budget (if necessary).
- Authorising the provision of funds/resources (internal or external) (if necessary).
- Approving the functional and technical specifications written by the team.
- Approving any major changes in scope.
- Receive Project Weekly Reports and take action accordingly to resolve issues escalated by the Project Manager.
- Providing final acceptance of the solution upon project completion.

### 1.3.2 Stakeholders

| Stakeholder | May Have/Find an Interest In |
| --- | --- |
| Coris Innovation | Having their prototype tested and upgraded <br> & Help train the next generation of software engineers |
| ALGOSUP | Have the students learn C/C++ programmation |
| ALGOSUP's Students | Learn C/C++ & get experience |

### 1.3.3 Project Roles

As defined by the project owner (ALGOSUP), the team is arranged as follows:

| Role | Description | Assigned Person |
| --- | --- | :-: |
| Project Manager | Is in charge of organization, planing and budgeting.<br>Keep the team motivated. | Bistrel TSANQUE |
| Program Manager | Makes sure the project meets expectations. <br> Is in charge of design. <br> Is responsible for writing the Functional Specifications | Arthur LEMOINE |
| Technical Lead | Makes the technical decision in the project.<br>Translates the Functional Specification into Technical Specifications.<br>Does code review. | Benoît DE KEYN |
| Software Engineer | Writes the code.<br>Writes documentation<br>Participate in the technical design. | Aurélien FERNANDEZ |
| Quality Assurance | Tests all the functionalities of a product to find bugs and issues.<br>Document bugs and issues.<br>Write the test plan.<br>Check that issues have been fixed. | Antoine PREVOST |
| Technical Writer | Makes the User Manual | Clémentine CUREL |

### 1.3.4 Project Reviewers

External project reviewers have been appointed by the project owner to review our specifications and provide us with feedback.

