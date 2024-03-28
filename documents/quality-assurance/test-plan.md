# SportShield Project Test Plan

<details>
<summary>Table of contents</summary>

- [SportShield Project Test Plan](#sportshield-project-test-plan)
  - [1. Introduction](#1-introduction)
    - [1.1 Document purpose](#11-document-purpose)
  - [2. Quality objectives](#2-quality-objectives)
    - [2.1 Primary objectives](#21-primary-objectives)
    - [2.2 Secondary Objectives](#22-secondary-objectives)
  - [3. Scope of Testing](#3-scope-of-testing)
    - [3.1 In Scope](#31-in-scope)
      - [3.1.1 Scope of SportShield's software](#311-scope-of-sportshields-software)
      - [3.1.2 Scope of documentation](#312-scope-of-documentation)
    - [3.2 Out of Scope](#32-out-of-scope)
  - [4. Roles \& Responsibilities](#4-roles--responsibilities)
  - [5. Testing Strategy](#5-testing-strategy)
  - [6. Entry and Exit Criteria](#6-entry-and-exit-criteria)
    - [6.1 Entry Criteria](#61-entry-criteria)
    - [6.2 Exit Criteria](#62-exit-criteria)
  - [7. Suspension and Resumption Criteria](#7-suspension-and-resumption-criteria)
    - [7.1 Suspension Criteria](#71-suspension-criteria)
    - [7.2 Resumption Criteria](#72-resumption-criteria)
  - [8. Resources and Environment](#8-resources-and-environment)
    - [8.1 Testing tools](#81-testing-tools)
      - [8.1.1 Github Actions](#811-github-actions)
    - [8.2 Test Environment](#82-test-environment)
    - [8.3 Workforce](#83-workforce)
  - [9. Schedules](#9-schedules)
    - [9.1 Estimated Schedule](#91-estimated-schedule)
    - [9.2 Actual Schedule](#92-actual-schedule)
  - [10. Risks/Assumptions](#10-risksassumptions)
  - [11. Deliverables](#11-deliverables)
  - [12. Glossary](#12-glossary)

</details>

## 1. Introduction

The client contacted us to work on SportShield, the prototype of a lock which will be principally used for the protection of winter sports equipment and needs multiple enhancements. This product targets a wide audience, from people well-acquainted with the concept of securing their equipment to people wanting to protect their occasional rental of equipment and with any experience in this security field.

This project aims to enhance the inner workings of SportShield from a software point of view, using C++ and the given hardware. The primary objective is to detect shocks and distinguish theft attempts from unintentional bumps into the sports equipment protected by the lock, as well as triggering an alarm if a theft is detected. The second objective is to enhance battery usage while adding the possibility of doing concurrent actions on the lock and offering NFC unlocking.

With these objectives, the product aims to serve as an educational tool for learning C++ language but also to help the client in their product prototyping. Given the specificity of SportShield, the lock's software must be fully tested ensuring it is bug-free.

### 1.1 Document purpose

This document has been created to facilitate communication between the team members. It describes approaches and methodogies that will apply to the regression, security, boundary, performance and smoke testing of SportShield. It also identifies the test deliverables and the scope of this testing.

## 2. Quality objectives

### 2.1 Primary objectives

The system integration test of SportShield's software should validate from the requirements perspective that:

- List of all objectives

### 2.2 Secondary Objectives

List secondary objectives

## 3. Scope of Testing

The testing of SportShield will mainly consist of the validation of the core features asked by the client, but also of the system resilience in extreme conditions ensuring this lock is a reliable piece of winter sports equipment. Nevertheless, it is worth noting that the hardware will not be tested, as these objectives are beyond the scope of this testing.

### 3.1 In Scope

This test plan mainly targets the testing of SportShield software and its reactivity to given situations. It also englobes documentation control and consistence verfication during the whole project.

#### 3.1.1 Scope of SportShield's software

- Absence of significant bugs
- Final product meets the KPIs and reliability indicators given by the client.
- Conventions respect

The following features of SportShield's software will be tested:

#### 3.1.2 Scope of documentation

- Spellchecking
- Vocabulary accuracy
- Ambiguities
- Consistency between documents

### 3.2 Out of Scope

- Hardware-related issues

<!-- Test approach? -->

## 4. Roles & Responsibilities

| Role            | Team Member | Responsibilities                                                                                                              |
| --------------- | ----------- | ----------------------------------------------------------------------------------------------------------------------------- |
| Project manager | Vivien      | 1. Contact between the QA and the rest of the team <br>2. Responsible for project schedule and overall success of the project |
| QA              | Antoine     | 1. Understand project requirements <br>2. Add complementary things when test strategy ok                                      |

## 5. Testing Strategy

z

## 6. Entry and Exit Criteria

### 6.1 Entry Criteria

Entry criteria description

### 6.2 Exit Criteria

To consider the product as ready for distribution and end the test phase, some critical objectives must be met.

1. Meet the client's Reliability Indicators minimal functionning rate:
   - Shock detection - 99%
   - Unlock - 99%
   - Alarm - 98%
   - Shock notification - 95%
   - GNSS position acquisition and transmission - 80%

2. Meet the client's expectations on battery operating time between two charges:
   - At least 7 days of operating duration
   - A day is considered as a 6 hours of activation mode and then 18 hours in stand-by mode.

3. Test Case Coverage:
   - A minimum test coverage of 95% for all identified features must be achieved before considering the test phase complete.
   - This ensures our lock has its expected behaviour

4. Bug Resolution Rate:
   - All the issues must be addressed and resolved before exiting the testing phase.
   - This allows you to create software that is less prone to bugs.

5. Documentation completeness and correctness
   - Comprehensive documentation including functional specifications, technical specifications, user manual, test plan, test cases and test reports must be verified to identify any possible mistake or missing information.
   - The documentation should be easily understandable to any external person of the project. Additionally, it should be consistent across all documents.

## 7. Suspension and Resumption Criteria

### 7.1 Suspension Criteria

In case of a critical bug affecting the whole testing process, the testing phase can be temporarily suspended. The following cases can trigger this suspension:

- Hardware problems/failure.
- Assigned resources are not available when required by quality assurance team.
- Significant change in requirements asked by the client
- The firmware contains serious defects limiting or preventing testing.

### 7.2 Resumption Criteria

To resume testing, the critical problem(s) that have caused the test suspension must have been addressed and resolved.

## 8. Resources and Environment

### 8.1 Testing tools

To increase efficiency and guarantee the best quality for SportShield's software, we will use powerful monitoring tools running repetitive and measurable actions automatically.

#### 8.1.1 Github Actions

GitHub Actions is a platform we will use to adopt a continuous integration and continuous deployment workflow. Every time a push is triggered on a targetted branch, a test will automatically run.

### 8.2 Test Environment

As this project is based on the supplied board, our tests will be carried out entirely using it. In addition, and in order to harmonize the test environment, we have decided to use a single computer to compile the software and upload it to the ARDUINO board.

We will use the following card equipped with the components listed below:

- Xiao BLE Sense nrf52840
  - GNSS PA1010D
  - GSM/2G SIM800L Module
  - Electromagnet
  - Piezoelectric buzzer
  - Lithium-Polymer battery with a capacity of 1100 mAh
  - NFC Antenna

The following libraries will be added in Arduino IDE:

- NRF52_MBED_TimerInterrupt *V1.4.1*
- ArduinoBLE *V1.3.6*
- Adafruit GPS Library *V1.7.4 (install all)*
- Sim800L http connector *V1.14.0*
- Seeed Arduino[^1] LSM6DS3 *V2.0.3*
- OneWire *V2.3.7*

The computer characteristics follow the configuration listed below:

- Lenovo Ideapad Slim 1-14AST-05
  - **Processor:** AMD® A4-9120e Radeon R3
  - **RAM:** 4,0 GiB
  - **Operating System:** Ubuntu 22.04.4 LTS x64

To test our software, we will not rely on the mobile app itself as we want to add some functionalities for battery saving. Instead, we are going to use LightBlue app showing the device available fields via Bluetooth.

- Iphone 11
  - **iOS version:** 17.4.1
  - **LightBlue version:** 4.2.7

### 8.3 Workforce

## 9. Schedules

### 9.1 Estimated Schedule

| Task                              | Start date     | End date       | Estimated duration |
| --------------------------------- | -------------- | -------------- | ------------------ |
| Issue and pull request templates  | March 11, 2024 | March 11, 2024 | 1 day              |
| First meeting with dev team       | March 11, 2024 | March 11, 2024 | 1 day              |
| Documentation reviewing           | March 11, 2024 | April 10, 2024 | 30 days            |
| Github Actions                    | March 26, 2024 | April 10, 2024 | 16 days            |
| Second meeting with dev team      | March 25, 2024 | March 25, 2024 | 1 day              |
| First meeting with team 7 & 8 QA  | April 2, 2024  | April 2, 2024  | 1 day              |
| Second meeting with team 7 & 8 QA | April 8, 2024  | April 8, 2024  | 1 day              |
| Functional testing                | March 20, 2024 | April 10, 2024 | 21 days            |
| Third meeting with dev team       | April 2, 2024  | April 2, 2024  | 1 day              |
| Regression testing                | March 27, 2024 | April 10, 2024 | 14 days            |
| Security testing                  | April 2, 2024  | April 10, 2024 | 8 days             |
| Boundary testing                  | April 2, 2024  | April 10, 2024 | 8 days             |
| Performance testing               | April 2, 2024  | April 10, 2024 | 8 days             |
| Fourth meeting with dev team      | April 8, 2024  | April 8, 2024  | 1 day              |

### 9.2 Actual Schedule

| Task                              | Start date     | End date       |
| --------------------------------- | -------------- | -------------- |
| Issue and pull request templates  | March 11, 2024 | March 11, 2024 |
| First meeting with dev team       | March 11, 2024 | March 11, 2024 |
| Documentation reviewing           | March 11, 2024 | April 10, 2024 |
| Github Actions                    | March 26, 2024 | April 10, 2024 |
| Second meeting with dev team      | March 25, 2024 | March 25, 2024 |
| First meeting with team 7 & 8 QA  | April 2, 2024  | April 2, 2024  |
| Second meeting with team 7 & 8 QA | April 8, 2024  | April 8, 2024  |
| Functional testing                | March 20, 2024 | April 10, 2024 |
| Third meeting with dev team       | April 2, 2024  | April 2, 2024  |
| Regression testing                | March 27, 2024 | April 10, 2024 |
| Security testing                  | April 2, 2024  | April 10, 2024 |
| Boundary testing                  | April 2, 2024  | April 10, 2024 |
| Performance testing               | April 2, 2024  | April 10, 2024 |
| Fourth meeting with dev team      | April 8, 2024  | April 8, 2024  |

## 10. Risks/Assumptions

| Risk                                   | Mitigation                                             |
| -------------------------------------- | ------------------------------------------------------ |
| The provided code base isn't working   | Troubleshoot errors by isolating code's component      |
| Limited time or ressources for testing | Identify the most critical features to test them first |
| An hardware failure occurs             | Get extra hardware or share hardware among teams       |

## 11. Deliverables

- Test Plan
- Test Cases Description
- Bugs Reports and reports regarding the testing progress
- QA meetings reports

## 12. Glossary
