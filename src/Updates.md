# Updates

## Overview

This document aims to identify every modification between the base code given at the beginning of the project and the current code.

## What has been updated

### Format

The format is fairly simple:
- The first element of a line is the line number in the code,
- The second element is either -, + symbolizing if the line has been removed or added, if a line with - is followed by a line with  +, it means the line has been modified
- The third element is the line itself,
- The last element is a short comment explaining why the change has been made.

### Code

```cpp
72 -int currentRep = 0; // This value is not needed in the code anymore

78 -float SmallMT = 20.0;
78 +float SmallMT = 5000.0;  // The minimum value has been increased to remove parasitic movements

79 -float BigMT = 150.0;
79 +float BigMT = 7000.0;    // The maximum value has been increased to match the minimum value

81 -float SmallRT = 20.0; 
81 +float SmallRT = 45.0;  // The minimum value has been increased to remove parasitic movements

82 -float BigRT = 125.0;
82 +float BigRT = 100.0;   // The maximum value has been increased to match the minimum value

169 +  Config.isActivate = 1;   // To be able to test the program, the boolean is set to true, it has to be removed to make the project work as intended

184 -    } else if ((MotionBig == false) && (MotionData > SmallMT || RotationData > SmallRT)) { 
184 +    } else if (MotionData > SmallMT || RotationData > SmallRT) {  // The first condition was redundant with the previous if statement

186  -        Serial.print(" Small motion: ");
186  +        Serial.print("Small motion: "); // A space was present at the beginning of the string
   

197 -    PulseBuzzer(5, 500, 1000);  // This line has been moved under the the print
197 +    Serial.println("Big motion detected"); // A print has been added for testing purposes

198 +    PulseBuzzer(3, 100, 100);  // This is the same line but as before, except for the number of repetitions that has been reduced


203 +    Serial.println("Small motion detected"); // A print has been added for testing purposes


208 -  if ((MotionData > SmallMT) || (RotationData > SmallRT)) {
    -    if (MotionData > SmallMT) {
    -      Serial.print("WAKE UP : "); 
    -      Serial.println(MotionData);
    -    } else {
    -      Serial.print("WAKE UP Rota: ");
    -      Serial.println(RotationData);
    -    }
216 -  } // This block of code has been removed as it was redundant with the previous statements

   
382 -  while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    -    delay(1000);
    -    network = sim800l->getRegistrationStatus();
    -    Serial.print(network + " ");
    -    Serial.println(F("Problem to register, retry in 1 sec"));
    -    digitalWrite(LEDG, !digitalRead(LEDG));
388 -  }
382 +  // while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    +  //   delay(1000);
    +  //   network = sim800l->getRegistrationStatus();
    +  //   Serial.print(network + " ");
    +  //   Serial.println(F("Problem to register, retry in 1 sec"));
    +  //   digitalWrite(LEDG, !digitalRead(LEDG));
288 +  // } // This block of code has been commented to be able to test the functionalities of the code


442 -  unsigned long currentMillis = millis();
442 +  unsigned long currentMillis; // Since it is now updated in a loop, it is not necessary to give the variable a value in this line

443 +  while (repetitions > 0) { // A loop was necessary in this function as it wouldn't turn the flag to detect a motion to false

444 +     currentMillis=millis(); // This line update the current time

452 -  if (currentRep < repetitions) { // Since the code is noew looping and removing 1 to repetition at each repetition, it is now unecessarry to have this condition

449 -      if (!buzzerState) currentRep++; 
449 +      if (!buzzerState) repetitions--; // After the end of each buzz, remove 1 to repetitions to perform
     
451 -  } else {
451 +  } // The else is not needed since it is now a loop

460 -    currentRep = 0; // This variable does not exist anymore

464 -  } // This bracket is not necessary anymore since the condition has been removed
```