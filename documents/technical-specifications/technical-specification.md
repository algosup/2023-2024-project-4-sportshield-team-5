# Technical Specifications


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

## Table of Content

</summary>

- [1. Introduction](#1-introduction)
 	- [Document Purpose](#document-purpose)
 	- [Glossary](#glossary)
 	- [Project Overview](#project-overview)
  		- [Project Brief](#project-brief)
  		- [Requirements](#requirements)
			- ➭ [Setting up the Development Environment](#setting-up-the-development-environment)
      				- [Hardware Requirements](#hardware-requirements)
      				- [Software Requirements](#software-requirements)
				- [Coding Methodology](#coding-methodology)
					- [Workflow](#-workflow)
					- [Coding Conventions](#-coding-conventions)
					- [Commenting Conventions](#-commenting-conventions)
					- [Documenting Conventions](#-documenting-conventions)
					- [Test-Driven Development](#-test-driven-development)
			- ➭ [Setting up the utilization](#setting-up-the-game)
				- [Hardware requirements](#hardware-requirements-1) -> user manual
				- [Software requirements](#software-requirements-1)
  		- [Assumptions & Constraints](#assumptions--constraints)
- [2. Technical Specification](#2-technical-specifications)
	- [Folder Structure](#folder-structure)
	
- [3. Conclusion](#3-conclusion)
	- [Thanks](#thanks)
	- [Extras](#extras)
		- [All Value Tables](#all-value-tables)


</details>

# 1. Introduction

# Document Purpose & Definition

The goal of the Technical Specifications is to take the Functional Requirements which defines the features, scope and goals of the project, to dissect each requirement and turn it into instructions, as clear as possible, to guide the development team as well as the quality assurance team in the successful completion of their mission.

We therefore encourage thorough reading of the [Functional Specifications](https://github.com/algosup/) before further reading.

The goal of the Technical Requirements is to clarify as many dark areas as possible to avoid the engineers making decisions
In a sense, while the Functional Requirements represent the "What/Why" aspect of the project, the Technical Requirements are supposed to represent the "How" of the project.

With that being said, we will try to cover as many functional and non-functional aspects of the project while making technological and architectural decisions, evaluating those decisions, measuring their associated risks and impact (providing mitigation) and compare those to other potential solutions.

The document should also benefit other stakeholders and project owners by giving insight into our methodology and may serve as a future reference for maintenance or simple documentation purposes.

# Glossary

# Project Overview

## Project Brief
    
As fully explained in the Functional specifications, our goal in this project is to improve the firmware of an embedded system called "Sport Shield". Basically this "Sport Shield" is an anti-theft device intended only for snowboards and skis at present. It consists of a box equipped with a set of electronic and mechanical equipment, containing a steel cable to be wrapped around the object to be secured.

How it works  ?

When the cable is wrapped and the box in locked state, the device is looking for any physical disturbtions. If any movement or vibration of the box is detected as a possible theft, it enables a strong alarm, more or less loud according to the level of disturbtion (intensity and duration of the movement). At the same time, it sends a notification to the owner by a dedicated smartphone application, using the internet network.
To stop the alarm or unlock the shield, the owner uses the application and it processes via bluetooth or NFC.
The aim is to make the sports shield as rustic and resilient as possible, minimizing direct user interactions with the hardware and keeping them remote, via the bluetooth app.

