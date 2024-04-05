
# Test Cases

## Overview

This document outlines the different critical points of the software which will be tested. Those tests will ensure the device can be used in production by anyone without significant bug.

## Criticity

The test cases are defined by a criticity level, indicating the importance of the feature in the system and the inner workings of the device.

### 1. Code compilatation

| ID | 1 |
| --- | --- |
| Name | Code compilatation |
| Test Description | The code compiles successfully without errors or warnings |
| Test Type | Automated |
| Test Criticity | 🟣 |

**External Tools:**

- GitHub Actions - [Arduino Compile Sketches](https://github.com/arduino/compile-sketches)

**Steps:**

1. Push to the dev or the main branch of the repository. This test will be run automatically by GitHub Actions.

### 2. Coding conventions

| ID | 2 |
| --- | --- |
| Name | Coding conventions |
| Test Description | The source code follows the given conventions and guidelines |
| Test Type | Automated |
| Test Criticity | 🟣 |

**Tests:**

- 1
**External Tools:**

- linter.py

**Steps:**

1. Push to the dev or the main branch of the repository. This test will be run automatically by GitHub Actions.

### 3. Small move detection

| ID | 3 |
| --- | --- |
| Name | Small move detection |
| Test Description | When slightly moved for less than one second, SportShield emits a 3-tone sound |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board of 5 centimeters in less than one second.

### 4. Thief attempt/Major movement detection

| ID | 4 |
| --- | --- |
| Name | Thief attempt/Major movement detection |
| Test Description | If the lock is moved one second or more in anti-thief mode, it triggers a 5-tone sound. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1- 3
**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board of 50 centimeters in two seconds.

### 5. Bluetooth connection

| ID | 5 |
| --- | --- |
| Name | Bluetooth connection |
| Test Description | Ensure that SportShield can connect to the LightBlue app via Bluetooth and send/receive data. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Go on LightBlue app, and look for a device named 'SportShield 5'.

### 6. Bluetooth disconnection while charging

| ID | 6 |
| --- | --- |
| Name | Bluetooth disconnection while charging |
| Test Description | Ensure that we cannot connect to SportShield via Bluetooth while it is charging. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1- 5
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Connect the SportShield development board to a power source.
2. Go on LightBlue app, and look for a device named 'SportShield 5'.

### 7. Silent lock while charging

| ID | 7 |
| --- | --- |
| Name | Silent lock while charging |
| Test Description | The lock cannot emit any sound while charging. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1- 3- 4
**Hardware:**

- SportShield development board

**Steps:**

1. Connect the SportShield development board to a power source.
2. Move in diffferent directions the anti-thief device for 30 seconds to ensure it does not emit any sound.

### 8. Bluetooth linking

| ID | 8 |
| --- | --- |
| Name | Bluetooth linking |
| Test Description | You can only pair one device to the SportShield app, and it should be the only one that can connect to it. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1- 3- 4
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Connect to the SportShield development board via Bluetooth.
2. Try to connect to the SportShield development board via Bluetooth with another device.

### 9. 2G connectivity

| ID | 9 |
| --- | --- |
| Name | 2G connectivity |
| Test Description | Ensure that the device can connect to the 2G network and send data using the GPRS. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Wait for any packet to be sent to the server.

### 10. Wrong NFC card

| ID | 10 |
| --- | --- |
| Name | Wrong NFC card |
| Test Description | Ensure a notification is sent over GPRS to inform the user an attempt of unlock with another NFC device has been done on his behalf. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- NFC card

**Steps:**

1. Bring an unknown NFC card near the SportShield development board NFC reader.

### 11. NFC badging

| ID | 11 |
| --- | --- |
| Name | NFC badging |
| Test Description | The lock can be unlocked by badging the linked NFC card/phone. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- NFC card / Phone equipped with NFC technology

**Steps:**

1. Put the anti-thief device in lock state if not already done.
2. Bring the known and predefined card near the SportShield development board NFC reader.

### 12. Theft tentative notification

| ID | 12 |
| --- | --- |
| Name | Theft tentative notification |
| Test Description | Ensure that the device sends a notification to the server when a theft attempt is detected. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Put the anti-thief device in lock state if not already done.
2. Move the anti-theft device for more than one second.

### 13. Battery autonomy: Extreme conditions

| ID | 13 |
| --- | --- |
| Name | Battery autonomy: Extreme conditions |
| Test Description | The autonomy of the device is tested in extremely cold conditions to ensure it can least at least 7 days. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Freezer

**Steps:**

1. Put the development board in a plastic bag.
2. Empty the air from the bag and close it.
3. Put the bag in the freezer for 2 hours.
4. Take the development board out of the freezer and plug it to the GitHub Actions host computer
5. Check the console to see the percentage of battery left and enter it in the Python script to know if SportShield would last one week.

### 14. Battery autonomy: Normal conditions

| ID | 14 |
| --- | --- |
| Name | Battery autonomy: Normal conditions |
| Test Description | The autonomy of the device is tested in normal temperature conditions to ensure it can least at least 7 days. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Leave the development board in a room at room temperature for 2 hours.
2. Plug back the development board to the GitHub Actions host computer.
3. Check the console to see the percentage of battery left and enter it in the Python script to know if SportShield would last one week.

### 15. Charging threshold

| ID | 15 |
| --- | --- |
| Name | Charging threshold |
| Test Description | If the battery level is greater than or equal to 80% the charging speed si limited to 50mA |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Plug the development board and charge it until 80% of battery level.
2. Take an ammeter and measure if the charging speed is roughly 50mA.

### 16. Sleep mode disabled while charging

| ID | 16 |
| --- | --- |
| Name | Sleep mode disabled while charging |
| Test Description | If the anti-theft device is charging, sleep mode should be disabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug the development board to a power source.
2. When moving the board a sound should be emitted.
3. Verify on your phone a notification has been sent.

### 17. Deep sleep mode disabled while charging

| ID | 17 |
| --- | --- |
| Name | Deep sleep mode disabled while charging |
| Test Description | If the anti-theft device is charging, deep sleep mode should be disabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug the development board to a power source.
2. When moving the board a sound should be emitted.
3. Verify on your phone a notification has been sent.

### 18. Deep sleep mode automatically enabled

| ID | 18 |
| --- | --- |
| Name | Deep sleep mode automatically enabled |
| Test Description | If the anti-theft device hits 5% of the battery level, deep sleep mode should be enabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug the development board to the GitHub Actions host computer and check the battery level.
2. If the battery level is greater than 5%, wait until the battery level is less than 5% by unplugging it from the computer.
3. If the battery level is lower than 5%, unplug the board from the computer and start moving it.
4. Verify on your phone a notification has been sent and that no alarm has been triggered by the device.

### 19. Deep sleep mode manually enabled

| ID | 19 |
| --- | --- |
| Name | Deep sleep mode manually enabled |
| Test Description | The Bluetooth has a field to enable directly the deep sleep mode from the app. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue

**Steps:**

1. On SportShield, find the device named 'SportShield 5'.
2. Log in to the board and find the deep sleep mode field.
3. Send the hexadecimal value 0x1
4. Move the board in multiple directions for 30 seconds.
5. Verify on your phone a notification has not been sent and that no alarm has been triggered by the device.

### 20. Deep sleep mode alarm disabled

| ID | 20 |
| --- | --- |
| Name | Deep sleep mode alarm disabled |
| Test Description | The alarm is disabled when the deep sleep mode is enabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Ensure that deep sleep mode is enabled.
2. Move the board in multiple directions for 30 seconds.
3. Ensure that no alarm has been triggered by the device during this duration.

### 0. Deep sleep mode GPRS disabled

| ID | 0 |
| --- | --- |
| Name | Deep sleep mode GPRS disabled |
| Test Description | Communication with the server is disabled when the deep sleep mode is enabled |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Ensure that deep sleep mode is enabled.
2. Move the board in multiple directions for 30 seconds.
3. Verify on your phone you didn't receive any notification.

### 0. Deep sleep mode NFC disabled

| ID | 0 |
| --- | --- |
| Name | Deep sleep mode NFC disabled |
| Test Description | The NFC function is disabled when the deep sleep mode is enabled |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- NFC card / Phone equipped with NFC technology

**Steps:**

1. Ensure that deep sleep mode is enabled.
2. Put the anti-thief device in lock state if not already done.
3. Bring the known and predefined card near the SportShield development board NFC reader.
4. Verify the lock has not been unlocked and that you received no notification on your phone.
5. Bring an unknown NFC card near the SportShield development board NFC reader.
6. Verify the lock has not been unlocked and that you received no notification on your phone.

### 0. Deep sleep mode Bluetooth disabled

| ID | 0 |
| --- | --- |
| Name | Deep sleep mode Bluetooth disabled |
| Test Description | Communication with the server is disabled when the deep sleep mode is enabled |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Ensure that deep sleep mode is enabled.
2. Go on LightBlue app, and look for a device named 'SportShield 5'.

### 0. Sleep mode manually enabled

| ID | 0 |
| --- | --- |
| Name | Sleep mode manually enabled |
| Test Description | The Bluetooth has a field to enable directly the sleep mode from the app. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. On SportShield, find the device named 'SportShield 5'.
2. Log in to the board and find the sleep mode field.
3. Send the hexadecimal value 0x1
4. Move the board in multiple directions for 30 seconds, waiting for an alarm to trigger.
5. Verify on your phone a notification has not been sent.

### 0. Sleep mode disabled with specific movement

| ID | 0 |
| --- | --- |
| Name | Sleep mode disabled with specific movement |
| Test Description | When doing a specific movement, the sleep mode is disabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Ensure that sleep mode is enabled.
2. Do the movement in the provided documentation to disable the sleep mode.
3. Move in diffferent directions the anti-thief device for 30 seconds.
4. Verify on your phone a notification has been sent and that no alarm has been triggered by the device.

### 0. Sleep mode automatically enabled

| ID | 0 |
| --- | --- |
| Name | Sleep mode automatically enabled |
| Test Description | When the lock is unlocked, and after 40 seconds of inactivity, the sleep mode is enabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Unlock the device if that's not already done.
2. Do not move the device for 40 seconds.
3. Move in diffferent directions the anti-thief device for 30 seconds.
4. Verify on your phone no notification has been sent and that an alarm has been triggered by the device.

### 0. Sleep mode alarm

| ID | 0 |
| --- | --- |
| Name | Sleep mode alarm |
| Test Description | When the lock is in sleep mode and a movement is detected, an alarm is triggered. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Ensure that sleep mode is enabled.
2. Move in diffferent directions the anti-thief device for 30 seconds.
3. Verify that an alarm has been triggered by the device.

### 0. Sleep mode move packet

| ID | 0 |
| --- | --- |
| Name | Sleep mode move packet |
| Test Description | When the lock is in sleep mode and a movement is detected, a packet is sent to the server indicating a movement detection. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Ensure that sleep mode is enabled.
2. Move in diffferent directions the anti-thief device for 30 seconds.
3. Verify that you received a notification

### 0. Ecomode automatically enabled

| ID | 0 |
| --- | --- |
| Name | Ecomode automatically enabled |
| Test Description | When the lock battery reaches 15% of its maximum capacity, the ecomode is automatically enabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Server

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%, go on LightBlue app.
4. Verify on LightBlue that none of the available device is named 'SportShield 5'.
5. Move in diffferent directions the anti-thief device for 30 seconds.
6. Verify on your phone a notification has been sent and that an alarm has been triggered by the device.

### 0. Ecomode Bluetooth disabled

| ID | 0 |
| --- | --- |
| Name | Ecomode Bluetooth disabled |
| Test Description | When the lock battery reaches 15% of its maximum capacity, Bluetooth is automatically disabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%, go on LightBlue app.
4. Verify on LightBlue that none of the available device is named 'SportShield 5'.

### 0. Ecomode position and battery level sending

| ID | 0 |
| --- | --- |
| Name | Ecomode position and battery level sending |
| Test Description | When in ecomode, the battery level and the position of the device are sent to the server every 30 minutes. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%
4. Wait for the first position packet to be sent to the server for 15 minutes.
5. Wait for the second position packet to be sent to the server another 15 minutes.

### 0. Ecomode alarm triggering

| ID | 0 |
| --- | --- |
| Name | Ecomode alarm triggering |
| Test Description | When in ecomode, the battery level triggers if ecomode is enabled and the device is moved. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%
4. Wait for the first position packet to be sent to the server for 15 minutes.
5. Wait for the second position packet to be sent to the server another 15 minutes.

### 0. Battery ecomode enabled packet sent

| ID | 0 |
| --- | --- |
| Name | Battery ecomode enabled packet sent |
| Test Description | When ecomode enables, a battery and position packet is sent to the server |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%, charge the device until the battery level is greater than 15%.
4. Wait until a battery and position packet is sent to the server indicating 15% of battery.
5. Verify if ecomode has been enabled on the device.

### 0. Ecomode NFC enabled

| ID | 0 |
| --- | --- |
| Name | Ecomode NFC enabled |
| Test Description | When the lock battery reaches 15% of its maximum capacity, NFC stays enabled. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- NFC card / Phone equipped with NFC technology

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%, take the NFC card.
4. Bring the known and predefined card near the SportShield development board NFC reader.
5. Verify the lock has been unlocked and that you received no notification on your phone.
6. Bring an unknown NFC card near the SportShield development board NFC reader.
7. Verify the lock has not been unlocked and that you received a notification on your phone.

### 0. Ecomode packet sending

| ID | 0 |
| --- | --- |
| Name | Ecomode packet sending |
| Test Description | When the lock battery reaches 15% of its maximum capacity, and a movement is detected, a packet is sent to the server indicating a movement detection. |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Tests:**

- 1
**Hardware:**

- SportShield development board
**External Tools:**

- Server

**Steps:**

1. Plug back the development board to the GitHub Actions host computer.
2. If the battery level is greater than 15%, wait until the battery level is less than 15% by unplugging it from the computer.
3. If the battery level is lower than 15%, move the board in multiple directions for 30 seconds.
4. Verify on your phone that a notification has been sent.

### 0. Anti-Theft mode sends position and battery every 15 minutes

| ID | 0 |
| --- | --- |
| Name | Anti-Theft mode sends position and battery every 15 minutes |
| Test Description | Ensure that the position of the device and the battery level are sent via 2G network |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Activate the Anti-Theft function
2. Leave it alone for 15 minutes
3. Verify that you received a notification
4. Leave it alone for 15 more minutes
5. Verify that you received a second notification

### 0. Sound intensity is twice as high for the big shock than for the light shock

| ID | 0 |
| --- | --- |
| Name | Sound intensity is twice as high for the big shock than for the light shock |
| Test Description | Ensure that the alarm of the device has a higher sound intensity ( ouble)for the 5 long tone ,than for the 3 short tone |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Activate the Anti-Theft function
2. Move the device to create a small shock so that it turns on the 3 short tones alarm
3. Move the device to create a big shock so that it turns on the 5 long tones alarms
4. Compare the sound intensity of both the alarms

### 0. When the battery hits 15%, a notification is send to the server

| ID | 0 |
| --- | --- |
| Name | When the battery hits 15%, a notification is send to the server |
| Test Description | Ensure that the device send a notification to the server when its battery hit a low level (15%) |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Wait for the device's battery to deplete
2. When the battery hits 15%, verifiy that the server received a notification

### 0. When the battery level is less than or equal to 15%, the lock cannot be activated

| ID | 0 |
| --- | --- |
| Name | When the battery level is less than or equal to 15%, the lock cannot be activated |
| Test Description | Ensure that the device doesn't try to activate the lock if its battery is lower than or equal to 15% |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Wait for the device's battery to deplete
2. When the battery hits 15% or lower, try to activate the lock function of the device (activate the Anti-theft function
3. Verify that the device doesn't activate the lock

### 0. When charging, the NFC function is disabled

| ID | 0 |
| --- | --- |
| Name | When charging, the NFC function is disabled |
| Test Description | Ensure that the device deactivate the NFC function while it is charging |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Put the device on charge
2. Try to connect to the device via NFC
3. Verify that you cannot connect to the device

### 0. Only the NFC tag associated with the app unlocks the device

| ID | 0 |
| --- | --- |
| Name | Only the NFC tag associated with the app unlocks the device |
| Test Description | Ensure that only one NFC tag can unlock the device for obvious security reasons |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. zzz

### 0. Charging automatically disable sleep mode

| ID | 0 |
| --- | --- |
| Name | Charging automatically disable sleep mode |
| Test Description | Ensure that when the device is put in charge, it deactivate the sleep mode |
| Test Type | Manual |
| Test Criticity | 🟣 |

**Hardware:**

- SportShield development board

**Steps:**

1. Put the device in sleep mode
2. Put the device in charge
3. Verify that the divice isn't in sleep mode anymore
