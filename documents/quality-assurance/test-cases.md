# Test Cases

## Overview

This document outlines the different critical points of the software which will be tested. Those tests will ensure the device can be used in production by anyone without significant bug.

## Criticity

The test cases are defined by a criticity level, indicating the importance of the feature in the system and the inner workings of the device.

### 1. Code compilation

| ID               | 1                                                         |
| ---------------- | --------------------------------------------------------- |
| Name             | Code compilatation                                        |
| Test Description | The code compiles successfully without errors or warnings |
| Test Type        | Automated                                                 |
| Test Criticity   | 🟣                                                         |

**External Tools:**

- GitHub Actions - [Arduino Compile Sketches](https://github.com/arduino/compile-sketches)

**Steps:**

1. Push to the dev or the main branch of the repository. This test will be run automatically by GitHub Actions.

### 2. Coding conventions

| ID               | 2                                                            |
| ---------------- | ------------------------------------------------------------ |
| Name             | Coding conventions                                           |
| Test Description | The source code follows the given conventions and guidelines |
| Test Type        | Automated                                                    |
| Test Criticity   | 🟠                                                            |

**External Tools:**

- linter.py

**Steps:**

1. Push to the dev or the main branch of the repository. This test will be run automatically by GitHub Actions.

### 3. Moving the device triggers a sound

| ID               | 3                                                       |
| ---------------- | ------------------------------------------------------- |
| Name             | Moving the device triggers a sound                      |
| Test Description | Whenever the device is moved, a sound is emitted by it. |
| Test Type        | Manual                                                  |
| Test Criticity   | 🟣                                                       |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board.
2. Listen for any sound emitted by the device's buzzer.

### 4. Small move detection

| ID               | 4                                                                              |
| ---------------- | ------------------------------------------------------------------------------ |
| Name             | Small move detection                                                           |
| Test Description | When slightly moved for less than one second, SportShield emits a 3-tone sound |
| Test Type        | Manual                                                                         |
| Test Criticity   | 🟣                                                                              |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board of 5 centimeters in less than one second.
2. Listen for any sound emitted by the device's buzzer.

### 5. Thief attempt/Major movement detection

| ID               | 5                                                                                    |
| ---------------- | ------------------------------------------------------------------------------------ |
| Name             | Thief attempt/Major movement detection                                               |
| Test Description | If the lock detects a major move for less than 1 second, it triggers a 5-tone sound. |
| Test Type        | Manual                                                                               |
| Test Criticity   | 🟣                                                                                    |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board of 50 centimeters in less than one second.
2. Listen for any sound emitted by the device's buzzer.

### 6. Thief attempt/Long movement detection

| ID               | 6                                                                                       |
| ---------------- | --------------------------------------------------------------------------------------- |
| Name             | Thief attempt/Long movement detection                                                   |
| Test Description | If the lock is moved one second or more in anti-thief mode, it triggers a 5-tone sound. |
| Test Type        | Manual                                                                                  |
| Test Criticity   | 🟣                                                                                       |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board

**Steps:**

1. Move the SportShield development board for 5 seconds.
2. Listen for a 5-tone sound emitted by the buzzer of the board.

### 7. Sound level differences

| ID               | 7                                                                  |
| ---------------- | ------------------------------------------------------------------ |
| Name             | Sound level differences                                            |
| Test Description | The sound of a 5-tone sound is twice more loud than the 3-tone one |
| Test Type        | Manual                                                             |
| Test Criticity   | 🔴                                                                  |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection
- 4 - Thief attempt/Major movement detection
- 5 - Thief attempt/Long movement detection

**Hardware:**

- SportShield development board
**External Tools:**

- Phyphox

**Steps:**

1. Ensure the anti-theft device is not in deep sleep mode and enable Phyphox on the "Audio Amplitude" tab.
2. Move the SportShield development board of 5 centimeters in less than one second.
3. Note down the maximum value displayed on the chart.
4. Reset the activity chart in Phyphox application using the "Clear History" button.
5. Move the SportShield development board for 5 seconds.
6. Note down the maximum value displayed on the chart.
7. Comapre if the second sound level is equal or greater than the first sound level + 10dB.

### 8. Bluetooth connection

| ID               | 8                                                                                             |
| ---------------- | --------------------------------------------------------------------------------------------- |
| Name             | Bluetooth connection                                                                          |
| Test Description | Ensure that SportShield can connect to the LightBlue app via Bluetooth and send/receive data. |
| Test Type        | Manual                                                                                        |
| Test Criticity   | 🟣                                                                                             |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Go on LightBlue app, and look for a device named "SportShield 5".

### 9. 2G connectivity

| ID               | 9                                                                                  |
| ---------------- | ---------------------------------------------------------------------------------- |
| Name             | 2G connectivity                                                                    |
| Test Description | Ensure that the device can connect to the 2G network and send data using the GPRS. |
| Test Type        | Manual                                                                             |
| Test Criticity   | 🟣                                                                                  |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Wait for any payload to be sent to the server.

### 10. NFC badging

| ID               | 10                                                                          |
| ---------------- | --------------------------------------------------------------------------- |
| Name             | NFC badging                                                                 |
| Test Description | The anti-thief device can be unlocked by badging the linked NFC card/phone. |
| Test Type        | Manual                                                                      |
| Test Criticity   | 🟡                                                                           |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Iphone 11 NFC module

**Steps:**

1. Put the anti-thief device in lock state if not already done.
2. Bring the Iphone near the SportShield development board NFC reader.

### 11. Device charging

| ID               | 11                                              |
| ---------------- | ----------------------------------------------- |
| Name             | Device charging                                 |
| Test Description | SportShield can be charged using a powersource. |
| Test Type        | Manual                                          |
| Test Criticity   | 🟣                                               |

**Hardware:**

- SportShield development board
**External Tools:**

- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.
3. Wait for 30 minutes to receive two battery level payload and verify the linked level increased over time.

### 12. Device locking

| ID               | 12                                   |
| ---------------- | ------------------------------------ |
| Name             | Device locking                       |
| Test Description | The anti-thief device can be locked. |
| Test Type        | Manual                               |
| Test Criticity   | 🟣                                    |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Ammeter

**Steps:**

1. Verify the inactivity of the electromagnet using the ammeter.

### 13. Device unlocking

| ID               | 13                                     |
| ---------------- | -------------------------------------- |
| Name             | Device unlocking                       |
| Test Description | The anti-thief device can be unlocked. |
| Test Type        | Manual                                 |
| Test Criticity   | 🟣                                      |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Ammeter- LightBlue app

**Steps:**

1. Verify the inactivity of the electromagnet using the ammeter.
2. Leave the ammeter on the pins on which you were doing the previous step's measurements.
3. Go on LightBlue app, and put the unlock field value to 0.
4. In the second following the submission of the value, check the value displayed on the ammeter screen.

### 14. Eco-mode - The lock cannot be locked back

| ID               | 14                                                                           |
| ---------------- | ---------------------------------------------------------------------------- |
| Name             | Eco-mode - The lock cannot be locked back                                    |
| Test Description | When the anti-thief device is in eco-mode, it cannot be locked if it wasn't. |
| Test Type        | Manual                                                                       |
| Test Criticity   | 🟠                                                                            |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Check if the eco-mode is enabled by checking if a "SportShield 5" Bluetooth device is available.
2. If you see one, wait until the battery level is lower than or equal to 15%
3. If you don't see one, unlock the device by submitting the value 0x1 the "Unlock" Bluetooth field.

### 15. Eco-mode - The lock can be unlocked via NFC

| ID               | 15                                                                                             |
| ---------------- | ---------------------------------------------------------------------------------------------- |
| Name             | Eco-mode - The lock can be unlocked via NFC                                                    |
| Test Description | When the anti-thief device is in eco-mode, it can be unlocked using the linked NFC card/phone. |
| Test Type        | Manual                                                                                         |
| Test Criticity   | 🔴                                                                                              |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Iphone 11 NFC module

**Steps:**

1. Check if the eco-mode is enabled by checking if a "SportShield 5" Bluetooth device is available.
2. If you see one, wait until the battery level is lower than or equal to 15%
3. If you don't see one, bring the Iphone close to the NFC reader of the SportShield development board.

### 16. Sleep mode - The lock cannot be locked back

| ID               | 16                                                                             |
| ---------------- | ------------------------------------------------------------------------------ |
| Name             | Sleep mode - The lock cannot be locked back                                    |
| Test Description | When the anti-thief device is in sleep mode, it cannot be locked if it wasn't. |
| Test Type        | Manual                                                                         |
| Test Criticity   | 🟠                                                                              |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if the sleep mode is enabled by checking if a "SportShield 5" Bluetooth device is available and by bringing the phone close to the NFC reader.
2. If you see a device named "SportShield 5", or the lock is unlocked via NFC, go on LightBlue and submit the value 0x1 in the "Sleep Mode 5" field.
3. To ensure deep sleep mode is not switched on, move the device in different directions and ensure a sound is emitted.
4. If the two previous steps were validated, unlock the device by submitting the value 0x1 the "Unlock" Bluetooth field.

### 17. Sleep mode - The lock cannot be unlocked

| ID               | 17                                                                  |
| ---------------- | ------------------------------------------------------------------- |
| Name             | Sleep mode - The lock cannot be unlocked                            |
| Test Description | When the anti-thief device is in sleep mode, it cannot be unlocked. |
| Test Type        | Manual                                                              |
| Test Criticity   | 🟠                                                                   |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Iphone 11 NFC module- LightBlue app

**Steps:**

1. Check if the sleep mode is enabled by checking if a "SportShield 5" Bluetooth device is available and by bringing the phone close to the NFC reader.
2. If you see a device named "SportShield 5", or the lock is unlocked via NFC, go on LightBlue and submit the value 0x1 in the "Sleep Mode 5" field.
3. To ensure deep sleep mode is not switched on, move the device in different directions and ensure a sound is emitted.
4. Try to access via Bluetooth to the device. You shouldn't be able to access it and find it on LightBlue app.
5. Bring the phone close to the board NFC reader.

### 18. Deep sleep mode - The lock must be locked

| ID               | 18                                                                               |
| ---------------- | -------------------------------------------------------------------------------- |
| Name             | Deep sleep mode - The lock must be locked                                        |
| Test Description | Deep sleep mode can only be enabled if the anti-thief device is in a lock state. |
| Test Type        | Manual                                                                           |
| Test Criticity   | 🔴                                                                                |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Check if a "SportShield 5" Bluetooth device is available
2. Submit the value 0x1 in the "Unlock field"
3. Try to submit the value 0x1 in the "Deep Sleep Mode" field. The value should instantly reswitch to 0x0
4. Submit the value 0x0 in the "Unlock field"
5. Try to submit the value 0x1 in the "Deep Sleep Mode" field.

### 19. Deep sleep mode - The lock cannot be unlocked

| ID               | 19                                                                       |
| ---------------- | ------------------------------------------------------------------------ |
| Name             | Deep sleep mode - The lock cannot be unlocked                            |
| Test Description | When the anti-thief device is in deep sleep mode, it cannot be unlocked. |
| Test Type        | Manual                                                                   |
| Test Criticity   | 🟠                                                                        |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Iphone 11 NFC module- LightBlue app

**Steps:**

1. Check if the deep sleep mode is enabled by moving the device and ensuring no sound is emitted from it.
2. Check on LightBlue app that no Bluetooth device named "SportShield 5" is available.
3. Bring the phone close to the board NFC reader.

### 20. Single device pairing over BLE

| ID               | 20                                                                           |
| ---------------- | ---------------------------------------------------------------------------- |
| Name             | Single device pairing over BLE                                               |
| Test Description | The anti-thief device should be able to pair only with one Bluetooth device. |
| Test Type        | Manual                                                                       |
| Test Criticity   | 🟣                                                                            |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- External phone

**Steps:**

1. Check if a Bluetooth device named "SportShield 5" is available and connect to it with the first phone using LightBlue app.
2. Take the second phone and try connect to the device named "SportShield 5".

### 21. Charging - Bluetooth connectivity disabled

| ID               | 21                                                                                                    |
| ---------------- | ----------------------------------------------------------------------------------------------------- |
| Name             | Charging - Bluetooth connectivity disabled                                                            |
| Test Description | When the anti-thief device is charging, the possibility to connect to it over BLE should be disabled. |
| Test Type        | Manual                                                                                                |
| Test Criticity   | 🟢                                                                                                     |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Github Actions server USB port

**Steps:**

1. Check if a Bluetooth device named "SportShield 5" is available.
2. Plug the development board to a power source.
3. Verify on LightBlue that none of the available device is named "SportShield 5".

### 22. Deep sleep mode - Automatic switch-on

| ID               | 22                                                                                                               |
| ---------------- | ---------------------------------------------------------------------------------------------------------------- |
| Name             | Deep sleep mode - Automatic switch-on                                                                            |
| Test Description | When the battery level reaches 5% or less, the anti-thief device should automatically switch to deep sleep mode. |
| Test Type        | Manual                                                                                                           |
| Test Criticity   | 🟣                                                                                                                |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board

**Steps:**

1. Wait until the battery level is lower than or equal to 5%.
2. Check if deep sleep mode is enabled by ensuring no alarm is triggered when the device is moved.
3. If it triggers, wait until the battery level is lower than or equal to 5%.

### 23. Deep sleep mode manual activation (BLE)

| ID               | 23                                                   |
| ---------------- | ---------------------------------------------------- |
| Name             | Deep sleep mode manual activation (BLE)              |
| Test Description | The deep sleep mode can be enabled manually via BLE. |
| Test Type        | Manual                                               |
| Test Criticity   | 🟠                                                    |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board

**Steps:**

1. Check if a Bluetooth device named "SportShield 5" is available.
2. Connect to the device and ensure a "Deep Sleep Mode" field is available.
3. Submit the value 0x1 in the "Deep Sleep Mode" field.

### 24. Deep sleep mode â€“ Inactive BLE

| ID               | 24                                                                   |
| ---------------- | -------------------------------------------------------------------- |
| Name             | Deep sleep mode â€“ Inactive BLE                                     |
| Test Description | When the anti-thief device is in deep sleep mode, BLE is not active. |
| Test Type        | Manual                                                               |
| Test Criticity   | 🟡                                                                    |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Check if deep sleep mode is enabled by ensuring no alarm is triggered when the device is moved.
2. Go on LightBlue app, and look for a device named "SportShield 5".

### 25. Sleep mode manual activation (BLE)

| ID               | 25                                              |
| ---------------- | ----------------------------------------------- |
| Name             | Sleep mode manual activation (BLE)              |
| Test Description | The sleep mode can be enabled manually via BLE. |
| Test Type        | Manual                                          |
| Test Criticity   | 🟠                                               |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if a Bluetooth device named "SportShield 5" is available.
2. Connect to the device and ensure a "Sleep Mode" field is available.
3. Submit the value 0x1 in the "Sleep Mode" field.

### 26. Sleep mode â€“ Inactive BLE

| ID               | 26                                                              |
| ---------------- | --------------------------------------------------------------- |
| Name             | Sleep mode â€“ Inactive BLE                                     |
| Test Description | When the anti-thief device is in sleep mode, BLE is not active. |
| Test Type        | Manual                                                          |
| Test Criticity   | 🟡                                                               |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if sleep mode is enabled by ensuring the device can be unlocked using NFC.
2. Go on LightBlue app, and look for a device named "SportShield 5".

### 27. Sleep mode â€“ Disabling with specific movement

| ID               | 27                                                                                                 |
| ---------------- | -------------------------------------------------------------------------------------------------- |
| Name             | Sleep mode â€“ Disabling with specific movement                                                    |
| Test Description | When the anti-thief device is in sleep mode, sleep mode can be disabled using a specific movement. |
| Test Type        | Manual                                                                                             |
| Test Criticity   | 🟢                                                                                                  |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if sleep mode is enabled by ensuring the device can be unlocked using NFC.
2. Go on LightBlue app, and ensure no device is named "SportShield 5".
3. Move the lock in the way shown in the attachments
4. Go on LightBlue app to look for a device named "SportShield 5".

### 28. Eco-mode - Automatic switch-on

| ID               | 28                                                                                                         |
| ---------------- | ---------------------------------------------------------------------------------------------------------- |
| Name             | Eco-mode - Automatic switch-on                                                                             |
| Test Description | When the battery level reaches 15% or less, the anti-thief device should automatically switch on eco-mode. |
| Test Type        | Manual                                                                                                     |
| Test Criticity   | 🔴                                                                                                          |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Wait until the battery level is lower than or equal to 15%.
2. Check if eco-mode is enabled by ensuring no device in LightBlue is named "SportShield 5".
3. If a device is called "SportShield 5", wait until the battery level is lower than or equal to 15%.

### 29. Eco-mode â€“ Inactive BLE

| ID               | 29                                                            |
| ---------------- | ------------------------------------------------------------- |
| Name             | Eco-mode â€“ Inactive BLE                                     |
| Test Description | When the anti-thief device is in eco-mode, BLE is not active. |
| Test Type        | Manual                                                        |
| Test Criticity   | 🟠                                                             |

**Tests:**

- 1 - Coding conventions
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if eco-mode is enabled by ensuring the device can be unlocked using NFC.
2. Go on LightBlue app, and look for a device named "SportShield 5".

### 30. Anti-thief mode - Position and battery updates

| ID               | 30                                                                                                      |
| ---------------- | ------------------------------------------------------------------------------------------------------- |
| Name             | Anti-thief mode - Position and battery updates                                                          |
| Test Description | In the regular mode, the anti-thief device should send its position and battery level every 15 minutes. |
| Test Type        | Manual                                                                                                  |
| Test Criticity   | 🟣                                                                                                       |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Ensure the anti-theft device is not in a particular battery-saving mode.
2. Wait 15 minutes to receive the first position and battery level payload.
3. Verify in the logs and in the console of the web-server that you received the payload.
4. Wait 15 additional minutes to receive the first position and battery level payload.
5. Verify in the logs and in the console of the web-server that you received the second payload.

### 31. Theft tentative notification

| ID               | 31                                                                                |
| ---------------- | --------------------------------------------------------------------------------- |
| Name             | Theft tentative notification                                                      |
| Test Description | In anti-theft mode, when a theft is detected, a notification should be triggered. |
| Test Type        | Manual                                                                            |
| Test Criticity   | 🟣                                                                                 |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Ensure the anti-theft device is not in a particular battery-saving mode.
2. Move the device during 30 seconds.
3. Verify in the logs and in the console of the web-server that you received a notification payload.

### 32. Eco-mode - Position and battery updates

| ID               | 32                                                                                              |
| ---------------- | ----------------------------------------------------------------------------------------------- |
| Name             | Eco-mode - Position and battery updates                                                         |
| Test Description | In eco-mode, the anti-thief device should send its position and battery level every 30 minutes. |
| Test Type        | Manual                                                                                          |
| Test Criticity   | 🔴                                                                                               |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Ensure the anti-theft device is in eco-mode.
2. Wait 30 minutes to receive the first position and battery level payload.
3. Verify in the logs and in the console of the web-server that you received the payload.
4. Wait 30 additional minutes to receive the first position and battery level payload.
5. Verify in the logs and in the console of the web-server that you received the second payload.

### 33. Eco-mode - Theft tentative notification

| ID               | 33                                                                         |
| ---------------- | -------------------------------------------------------------------------- |
| Name             | Eco-mode - Theft tentative notification                                    |
| Test Description | In eco-mode, when a theft is detected, a notification should be triggered. |
| Test Type        | Manual                                                                     |
| Test Criticity   | 🟣                                                                          |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Ensure the anti-theft device is in eco-mode.
2. Move the device during 30 seconds.
3. Verify in the logs and in the console of the web-server that you received a notification payload.

### 34. Sleep mode - Position and battery updates

| ID               | 34                                                                                   |
| ---------------- | ------------------------------------------------------------------------------------ |
| Name             | Sleep mode - Position and battery updates                                            |
| Test Description | In sleep mode, the anti-thief device should not send its position and battery level. |
| Test Type        | Manual                                                                               |
| Test Criticity   | 🟡                                                                                    |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Check if sleep mode is enabled by ensuring the device can be unlocked using NFC.
2. Go on LightBlue app, and ensure no device is named "SportShield 5".
3. Wait 35 minutes to receive the first position and battery level payload.
4. Verify in the logs and in the console of the web-server that you didn't received the payload.

### 35. Deep sleep mode - Position and battery updates

| ID               | 35                                                                                        |
| ---------------- | ----------------------------------------------------------------------------------------- |
| Name             | Deep sleep mode - Position and battery updates                                            |
| Test Description | In deep sleep mode, the anti-thief device should not send its position and battery level. |
| Test Type        | Manual                                                                                    |
| Test Criticity   | 🟡                                                                                         |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server

**Steps:**

1. Check if deep sleep mode is enabled by moving the anti-thief device for 30 seconds.
2. If no alarm was triggered, wait 35 minutes to receive a position and battery level payload.
3. Verify in the logs and in the console of the web-server that you didn't received the payload.

### 36. Charging - Position and battery updates

| ID               | 36                                                                                    |
| ---------------- | ------------------------------------------------------------------------------------- |
| Name             | Charging - Position and battery updates                                               |
| Test Description | While charging, the anti-thief device should not send its position and battery level. |
| Test Type        | Manual                                                                                |
| Test Criticity   | 🟡                                                                                     |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging

**Hardware:**

- SportShield development board
**External Tools:**

- Testing web-server- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.
3. Wait 35 minutes to receive a position and battery level payload.
4. Verify in the logs and in the console of the web-server that you didn't received the payload.

### 37. Wrong NFC card â€“ Notification sent over GPRS

| ID               | 37                                                                                                                                   |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| Name             | Wrong NFC card â€“ Notification sent over GPRS                                                                                       |
| Test Description | Ensure a notification is sent over GPRS to inform the user an attempt of unlock with another NFC device has been done on his behalf. |
| Test Type        | Manual                                                                                                                               |
| Test Criticity   | 🟣                                                                                                                                    |

**Tests:**

- 1 - Coding conventions
- 9 - NFC badging
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card- Testing web-server

**Steps:**

1. Bring an unknown NFC card near the SportShield development board NFC reader.

### 38. Wrong NFC card - No unlock

| ID               | 38                                                                          |
| ---------------- | --------------------------------------------------------------------------- |
| Name             | Wrong NFC card - No unlock                                                  |
| Test Description | When a wrong NFC card is detected, the anti-thief device should not unlock. |
| Test Type        | Manual                                                                      |
| Test Criticity   | 🟣                                                                           |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card

**Steps:**

1. Bring an unknown NFC card near the SportShield development board NFC reader.

### 39. Charging - NFC disabled

| ID               | 39                                                              |
| ---------------- | --------------------------------------------------------------- |
| Name             | Charging - NFC disabled                                         |
| Test Description | When the device is charging, the NFC reader should be disabled. |
| Test Type        | Manual                                                          |
| Test Criticity   | 🟡                                                               |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card- Iphone 11 NFC module- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.
3. Bring an unknown NFC card near the SportShield development board NFC reader.
4. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.
5. Bring the phone close to the board NFC reader.
6. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.

### 40. Deep sleep mode â€“ NFC disabled

| ID               | 40                                                                        |
| ---------------- | ------------------------------------------------------------------------- |
| Name             | Deep sleep mode â€“ NFC disabled                                          |
| Test Description | When the device is in deep sleep mode, the NFC reader should be disabled. |
| Test Type        | Manual                                                                    |
| Test Criticity   | 🟠                                                                         |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card- Iphone 11 NFC module

**Steps:**

1. Ensure that deep sleep mode is enabled by moving the device in different directions and ensuring no sound is emitted.
2. Bring an unknown NFC card near the SportShield development board NFC reader.
3. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.
4. Bring the phone close to the board NFC reader.
5. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.

### 41. Sleep mode â€“ NFC disabled

| ID               | 41                                                                   |
| ---------------- | -------------------------------------------------------------------- |
| Name             | Sleep mode â€“ NFC disabled                                          |
| Test Description | When the device is in sleep mode, the NFC reader should be disabled. |
| Test Type        | Manual                                                               |
| Test Criticity   | 🟠                                                                    |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card- Iphone 11 NFC module

**Steps:**

1. Ensure that sleep mode is enabled by moving the device in different directions and ensuring a sound is emitted.
2. Bring an unknown NFC card near the SportShield development board NFC reader.
3. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.
4. Bring the phone close to the board NFC reader.
5. Verify in the logs and in the console of the web-server that you didn't received the payload and that the electromagnet was not turned on.

### 42. Eco-mode â€“ NFC enabled

| ID               | 42                                                                |
| ---------------- | ----------------------------------------------------------------- |
| Name             | Eco-mode â€“ NFC enabled                                          |
| Test Description | When the device is in eco-mode, the NFC reader should be enabled. |
| Test Type        | Manual                                                            |
| Test Criticity   | 🔴                                                                 |

**Tests:**

- 1 - Coding conventions
- 10 - Device charging

**Hardware:**

- SportShield development board
**External Tools:**

- Unknown NFC card- Iphone 11 NFC module- LightBlue app

**Steps:**

1. Ensure that eco-mode is enabled by going on LightBlue app and looking for a device named "SportShield 5".
2. Bring an unknown NFC card near the SportShield development board NFC reader.
3. Verify in the logs and in the console of the web-server that you received the payload and that the electromagnet was not turned on.
4. Bring the phone close to the board NFC reader.
5. Verify in the logs and in the console of the web-server that you received the payload and that the electromagnet was turned on.

### 43. Optimized battery charging

| ID               | 43                                                                                                                               |
| ---------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| Name             | Optimized battery charging                                                                                                       |
| Test Description | When the device is charging and its battery level is greater than or equal to 80%, the charging speed should be limited to 50mA. |
| Test Type        | Manual                                                                                                                           |
| Test Criticity   | 🔴                                                                                                                                |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Ammeter

**Steps:**

1. Ensure the anti-thief device is charging and its battery level is greater than or equal to 80%.
2. Put the test tips on the pins of the board shown as an attachement, to measure the current.

### 44. Charging â€“ Sleep mode disabling

| ID               | 44                                                                     |
| ---------------- | ---------------------------------------------------------------------- |
| Name             | Charging â€“ Sleep mode disabling                                      |
| Test Description | When the device is charging, the sleep mode is automatically disabled. |
| Test Type        | Manual                                                                 |
| Test Criticity   | 🔴                                                                      |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.

### 45. Charging â€“ Deep sleep mode disabling

| ID               | 45                                                                          |
| ---------------- | --------------------------------------------------------------------------- |
| Name             | Charging â€“ Deep sleep mode disabling                                      |
| Test Description | When the device is charging, the deep sleep mode is automatically disabled. |
| Test Type        | Manual                                                                      |
| Test Criticity   | 🔴                                                                           |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.

### 46. Charging â€“ Eco-mode disabling

| ID               | 46                                                                   |
| ---------------- | -------------------------------------------------------------------- |
| Name             | Charging â€“ Eco-mode disabling                                      |
| Test Description | When the device is charging, the eco-mode is automatically disabled. |
| Test Type        | Manual                                                               |
| Test Criticity   | 🔴                                                                    |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.

### 47. Deep sleep mode automatically enabled

| ID               | 47                                                                                        |
| ---------------- | ----------------------------------------------------------------------------------------- |
| Name             | Deep sleep mode automatically enabled                                                     |
| Test Description | If the anti-theft device hits 5% of the battery level, deep sleep mode should be enabled. |
| Test Type        | Manual                                                                                    |
| Test Criticity   | 🟣                                                                                         |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board
**External Tools:**

- Github Actions server USB port

**Steps:**

1. Plug the development board to the GitHub Actions host computer and check the battery level.
2. If the battery level is greater than 5%, wait until the battery level is less than 5% by unplugging it from the computer.
3. If the battery level is lower than 5%, unplug the board from the computer and start moving it.
4. Wait for 35 minutes to receive a position and battery level payload.

### 48. Eco-mode - Alarm triggers if detecting a movement

| ID               | 48                                                                                   |
| ---------------- | ------------------------------------------------------------------------------------ |
| Name             | Eco-mode - Alarm triggers if detecting a movement                                    |
| Test Description | When in eco-mode, the alarm triggers if eco-mode is enabled and the device is moved. |
| Test Type        | Manual                                                                               |
| Test Criticity   | 🟣                                                                                    |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Ensure that eco-mode is enabled by going on LightBlue app and looking for a device named "SportShield 5".
2. Check if the device can be unlocked using NFC using the phone.
3. Move the device for 30 seconds.

### 49. Sleep mode - Alarm triggers if detecting a movement

| ID               | 49                                                                                       |
| ---------------- | ---------------------------------------------------------------------------------------- |
| Name             | Sleep mode - Alarm triggers if detecting a movement                                      |
| Test Description | When in sleep mode, the alarm triggers if sleep mode is enabled and the device is moved. |
| Test Type        | Manual                                                                                   |
| Test Criticity   | 🟣                                                                                        |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Ensure that sleep mode is enabled by going on LightBlue app and looking for a device named "SportShield 5".
2. Check if the device can be unlocked using NFC using the phone.
3. Move the device for 30 seconds.

### 50. Deep sleep mode - Alarm triggers if detecting a movement

| ID               | 50                                                                                                 |
| ---------------- | -------------------------------------------------------------------------------------------------- |
| Name             | Deep sleep mode - Alarm triggers if detecting a movement                                           |
| Test Description | When in deep sleep mode, the alarm triggers if deep sleep mode is enabled and the device is moved. |
| Test Type        | Manual                                                                                             |
| Test Criticity   | 🟠                                                                                                  |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module

**Steps:**

1. Ensure that deep sleep mode is enabled by going on LightBlue app and looking for a device named "SportShield 5".
2. Check if the device can be unlocked using NFC using the phone.
3. Move the device for 30 seconds.

### 51. Charging - Alarm is disabled

| ID               | 51                                                              |
| ---------------- | --------------------------------------------------------------- |
| Name             | Charging - Alarm is disabled                                    |
| Test Description | When charging, the alarm never triggers if the device is moved. |
| Test Type        | Manual                                                          |
| Test Criticity   | 🟠                                                               |

**Tests:**

- 1 - Coding conventions
- 3 - Small move detection

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app- Iphone 11 NFC module- Github Actions server USB port- USB-A to USB-C cable

**Steps:**

1. Plug the USB-C part of the cable in the charging port of the board.
2. Plug the USB-A part of the cable in the USB port of the computer.
3. Ensure that the device can be unlocked using NFC.
4. Move the device for 30 seconds.

### 52. Battery lasts 7 days in normal conditions

| ID               | 52                                                                                                              |
| ---------------- | --------------------------------------------------------------------------------------------------------------- |
| Name             | Battery lasts 7 days in normal conditions                                                                       |
| Test Description | The autonomy of the device is tested at a normal temperature conditions to ensure it can least at least 7 days. |
| Test Type        | Manual                                                                                                          |
| Test Criticity   | 🟣                                                                                                               |

**Tests:**

- 1 - Coding conventions

**Hardware:**

- SportShield development board

**Steps:**

1. Leave the development board in a room at room temperature for 2 hours.
2. Plug back the development board to the GitHub Actions host computer.
3. Check the console to see the percentage of battery left and enter it in the Python script to know if SportShield would last one week.

### 53. Battery lasts 7 days in extreme conditions

| ID               | 53                                                                                                        |
| ---------------- | --------------------------------------------------------------------------------------------------------- |
| Name             | Battery lasts 7 days in extreme conditions                                                                |
| Test Description | The autonomy of the device is tested in extremely cold conditions to ensure it can least at least 7 days. |
| Test Type        | Manual                                                                                                    |
| Test Criticity   | 🟣                                                                                                         |

**Tests:**

- 1 - Coding conventions

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

### 54. Thief attempt disabling over BLE

| ID               | 54                                                                         |
| ---------------- | -------------------------------------------------------------------------- |
| Name             | Thief attempt disabling over BLE                                           |
| Test Description | The alarm can be disabled by sending a BLE packet with a specific payload. |
| Test Type        | Manual                                                                     |
| Test Criticity   | 🟣                                                                          |

**Tests:**

- 1 - Coding conventions
- 5 - Thief attempt/Long movement detection
- 6 - Sound level differences
- 8 - 2G connectivity

**Hardware:**

- SportShield development board
**External Tools:**

- LightBlue app

**Steps:**

1. Ensure the anti-theft device is not in a particular battery-saving mode.
2. Move the device during 30 seconds.
3. Go on LightBlue app to look for a device named "SportShield 5".
4. Go in the "Alarm" tab and submit the value 0x0.
