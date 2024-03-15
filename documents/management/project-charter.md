<h1 align="center"> SportShield Project Charter </h1>

<details>
<summary style="font-size:1.2em; font-weight:bold;">Table Of Contents</summary>

- [Project Description](#project-description)
- [Team Members](#team-members)
- [Project Objectives](#project-objectives)
  - [Implementation](#implementation)
  - [Documentation](#documentation)
- [Project Scope](#project-scope)
- [Deliverables](#deliverables)
- [Stakeholders](#stakeholders)
- [Communication Plan](#communication-plan)
  - [Communication Channels](#communication-channels)
- [Project Timeline](#project-timeline)
- [Project Risks](#project-risks)
- [Project Constraints](#project-constraints)
- [Project Assumptions](#project-assumptions)
- [Conclusion](#conclusion)

</details>

## Project Description

SportShield, an innovative anti-theft device for sports equipment, represents a breakthrough in safeguarding valuable gear. Equipped with state-of-the-art sensors and actuators, SportShield detects movement, triggers alarms, and promptly notifies owners of potential theft attempts. Our mission, as entrusted by **CORIS INNOVATION**, is to elevate SportShield's performance by focusing on crucial aspects such as battery consumption management, device accessibility via NFC, alarm functionality, and security enhancements.

## Team Members

| **Pictures**                                                                                          | **Name**               | **Role**          | **GitHub address**                                     |
| ----------------------------------------------------------------------------------------------------- | ---------------------- | ----------------- | ------------------------------------------------------ |
| <img src=https://ca.slack-edge.com/T019N8PRR7W-U04JK8487BK-b37025b07600-512 width="150" height="150"> | Tsangue Vivien Bistrel | Project Manager   | [GitHub Link](https://github.com/Bistrel2002)          |
| <img src=https://ca.slack-edge.com/T06C726V31S-U06C4FFK53M-75d8750e33b8-512 width="150" height="150"> | LEMOINE Arthur         | Program Manager   | [GitHub Link](https://github.com/arthur-lemo1ne)       |
| <img src=https://ca.slack-edge.com/T019N8PRR7W-U05SZ8EGZLK-b8a90fc9d463-512 width="150" height="150"> | Benoît de Keyn         | Technical Lead    | [GitHub Link](https://github.com/benoitdekeyn-algosup) |
| <img src=https://ca.slack-edge.com/T019N8PRR7W-U05SZ8DQ0GK-7e592dc1d1fe-512 width="150" height="150"> | PREVOST Antoine        | Quality Assurance | [GitHub Link](https://github.com/TechXplorerFR)        |
| <img src=https://ca.slack-edge.com/T06C726V31S-U06C1LRUYJ1-g4a7908c1162-512 width="150" height="150"> | FERNANDEZ Aurélien     | Software Engineer | [GitHub Link](https://github.com/aurelienfernandez)    |
| <img src=https://ca.slack-edge.com/T019N8PRR7W-U01J9JNHZDM-593483a5505e-512 width="150" height="150"> | Clementine CUREL       | Technical Writer  | [GitHub Link](https://github.com/Clementine951)        |

## Project Objectives

### Implementation

1. **Battery Consumption Management:**

    - Enhance energy efficiency by implementing strategies like component activation only when necessary and efficient management of sleep modes.

    - Develop a protocol for managing low battery situations to ensure continuous protection of secured equipment.

    - Implement battery lifespan optimization techniques, such as limiting charging to 80% of maximum capacity and preventing discharges below 20%.

2. **Device Management with NFC:**

    - Integrate NFC functionality to facilitate convenient activation/deactivation of the anti-theft system and cable unlocking via users' smartphones and the SportShield app.

    - Implement redundancy with Bluetooth functionality to provide users with multiple control options, ensuring reliability and ease of use.

3. **Alarm Management and Simultaneous Actions:**

    - Enhance user experience by enabling the interruption of alarm     cycles, allowing immediate cessation of alarm sounds when required.

    - Enable alarm functionality while simultaneously sending HTTP notifications to the server, ensuring timely alerts to the owner and relevant authorities.

    - Improve interruption management for seamless operation under various conditions.

4. **Security Enhancement:**

    - Strengthen security measures to safeguard access to key features of the system, particularly those related to alarm activation/deactivation and cable unlocking.

    - Implement robust authentication mechanisms to prevent unauthorized access and ensure the integrity of SportShield's security features.

### Documentation

1. **Functional specification Document:**
    This document will contain all the necessary information concerning the project. It is more like a document outlining what we are supposed to do and what the project is all about. For example, it will specify which library we are supposed to use, which programming languages will be employed, Use Case, project objectives.

2. **Technical Specification Document:**
    Just like the functional document, the technical document operates similarly, but from a technical standpoint, it slightly deviates from the functional document. This document contains all the necessary detail information on how we will build the project. For example, it outlines how we will install all the desired libraries, which development environment will be used, and how it will be installed. It also specifies which components will be used for the project, their roles, and how we will interact with them.

3. **Test Plan Document**
    The quality assurance document provide all the information on all the test that have been carried out on each function of the code, what went wrong and what went well, how each function was tested, what was the result, what was the issue, what outcome was expected. The quality assurance document serves as a comprehensive record of the testing activities conducted on the codebase, providing insights into both the strengths and weaknesses of the software and guiding efforts to improve its quality and reliability.

4. **User Manual Document:**
    Provide clear instructions and essential information on how to effectively operate and maintain the enhanced SportShield Anti-Theft Device. It will empower users to utilize the device's features, understand its functionalities, troubleshoot common issues, and ensure safe and efficient usage, thereby enhancing the overall user experience and maximizing the device's utility.

## Project Scope

1. **Battery Consumption Management:**
    - Analyze current power consumption patterns of the SportShield device.

    - Develop and implement algorithms for optimizing energy usage, including intelligent component activation and sleep mode management.

    - The battery must operate for a minimal duration of 7 days under different weather conditions.

    - Conduct extensive testing under various usage scenarios to validate the achieved operating time and identify opportunities for further optimization.

2. **GNSS Position Acquisition and Transmission:**

    - Enhance GNSS (Global Navigation Satellite System) position acquisition and transmission capabilities to achieve a reliability rate of at least 80%.

    - Improve signal reception and processing algorithms to enhance the accuracy and speed of position acquisition.

    - Optimize data transmission protocols to ensure seamless and efficient transfer of GNSS coordinates to the designated server or user devices.

3. **Shock Detection Enhancement:**

    - Achieve a minimum shock detection rate of 99% to ensure optimal performance in identifying potential theft attempts.

    - Enhance accuracy in detecting both small and major movements, ensuring precise differentiation and timely response to varying levels of disturbance.

    - Conduct thorough testing and calibration to validate the effectiveness of shock detection mechanisms under different environmental conditions.

4. **Unlock Functionality Improvement:**

    - Ensure a minimum unlock success rate of 99% to guarantee seamless access to secured sports equipment.

    - Optimize system algorithms and hardware components to enhance reliability and speed of the unlocking process.

    - Conduct rigorous testing to validate the robustness of the unlock mechanism across different scenarios and usage conditions.

5. **Alarm System Optimization:**

    - Maintain a perceived quality rating of at least 98% for the alarm system to instill confidence in users regarding the device's effectiveness.

    - Enhance alarm functionality to ensure prompt activation and loud, attention-grabbing alerts in the event of unauthorized access or tampering.

    - Implement mechanisms for user-friendly alarm management, including the ability to stop the alarm cycle promptly and efficiently.

## Deliverables

- Testing reports demonstrating the efficacy and reliability of the upgraded SportShield system.

- Training materials for end-users and support personnel to ensure seamless adoption and maintenance of the enhanced device.

- Detailed documentation of requirements, design specifications, and testing procedures.

- Clear an concise User Manual for the end-users with detailed information on how to use the product

## Stakeholders

1. **CORIS INNOVATION & ALGOSUP:** As the client and owner of the SportShield project, ***CORIS INNOVATION*** has a vested interest in the successful enhancement of the anti-theft device. They provide the project requirements, and overall direction for the project passing through **ALGOSUP.**

2. **End Users:** These are individuals or organizations who utilize the SportShield anti-theft device to protect their sports equipment. End users rely on the device's functionality and performance to safeguard their valuable assets.

3. **Development Team:** This includes the technical lead, technical writer, program manager, software developers, project manager, and quality assurance responsible for implementing the enhancements outlined in the project scope. Working closely with **CORIS INNOVATION** to ensure that the project meets requirements and objectives.

## Communication Plan

Effective communication is crucial for the success of the SportShield Anti-Theft Device Enhancement project. The following communication plan outlines key communication channels, stakeholders, and frequency of communication:

### Communication Channels

1. ***Project Meetings:*** Regular project meetings will be held to discuss progress, issues, and updates. These meetings will be conducted via video conferencing and in group, this will be done every friday evening.

2. ***Slack:*** Important project updates, meeting agendas, and action items will be communicated on the development team working space via slack.

3. **Project Management Tool:** A project management tool, such as Notion, will be used to track tasks, deadlines, and project progress.

4. **Stakeholder Updates:** Periodic updates will be provided to stakeholders, including **CORIS INNOVATION**, on project milestones, challenges, and achievements.

## Project Timeline

1. **Requirement Analysis and Specification (Week 1-2):**

    - Gather and analyze project requirements from CORIS INNOVATION.

    - Define detailed specifications for each enhancement.

    - Functional and technical specification document.

    - Finalize project scope and deliverables.

2. **System Design and Architecture Proposal (Week 2):**

    - Develop system architecture considering the proposed enhancements.

    - Design algorithms and protocols for shock detection, unlocking, alarm management, and GNSS position acquisition.

    - Propose battery optimization strategies.

3. **Implementation phase (week 3-5)**
    - Implementation of Shock Detection and Unlock Enhancements.

    - Optimization of Alarm System and Shock Notification mechanisms.

    - Integration of GNSS(Global Navigation Satellite System) Position Acquisition and Transmission .Improvements.

    - Battery Operating Time Optimization and Performance Testing.

    - System Integration and Validation Testing.

4. **Final Documentation and Project Handover (Week 5):**

    - Prepare detailed documentation outlining the user guidelines.

    - Conduct training sessions for end-users and support personnel.

    - Hand over the completed project deliverables to **CORIS INNOVATION.**

5. **Oral Presentation(Week 6):**
    - Prepare for the final oral presentation of the project, present in front of the juries the final product.

## Project Risks

Identifying and mitigating potential risks is essential to ensuring the success of the SportShield Anti-Theft Device Enhancement project. The following risks have been identified:

1. **Technical Challenges:** Complexities in implementing the required enhancements may lead to delays or technical issues.

2. **Resource Constraints:** Limited availability of skilled personnel or hardware resources may impact project timelines and deliverables.

3. **Regulatory Compliance:** Changes in regulations or certification requirements may necessitate adjustments to the project scope or timeline.

4. **Hardware constraints:** In case the hardware prototype provided by **CORIS INNOVATION**, we will have some difficulties to complete all the requirements.

## Project Constraints

The SportShield Anti-Theft Device Enhancement project is subject to the following constraints:

1. **Time Constraints:** The project timeline is constrained by deadlines set by **CORIS INNOVATION** and **ALGOSUP.**

2. **Technology Limitations:** Enhancements must be feasible within the limitations of existing technology and hardware components.

3. **Regulatory Compliance:** The device must comply with relevant regulations and certifications to ensure market acceptance.

4. **Stakeholder Expectations:** The project must meet the expectations and requirements of all stakeholders involved, including **CORIS INNOVATION** and end users.

## Project Assumptions

- Availability of necessary resources, including hardware components, software development tools, and testing equipment.

- Collaboration and support from stakeholders, including ***CORIS INNOVATION***, throughout the project lifecycle.

- Compliance with relevant industry standards and regulations governing anti-theft device functionality and security.

## Conclusion

The proposed enhancements to the SportShield anti-theft device represent a significant step forward in ensuring the security and reliability of sports equipment protection. By addressing critical aspects such as battery consumption, device accessibility, alarm functionality, and security, we aim to provide users with a comprehensive and effective solution that exceeds their expectations. We are committed to delivering results that align with **CORIS INNOVATION's** vision for SportShield and contribute to its success in the market.
