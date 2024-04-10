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
70 -void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff);
70 +void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity); // The value intensity has been added to control the intensity of the buzzer

71 -unsigned long previousMillis = 0;
71 +unsigned long startCycle = 0; //The name of the value has been changed to increase readability

72 -int currentRep = 0;     // This value was no longer necessary

79 -float SmallMT = 20.0;  
79 +float SmallMT = 5000.0; // The minimum value has been increased because of the sensibility of the sensor

80 -float BigMT = 150.0;  
80 +float BigMT = 7000.0;   // The value has been increased to match the minimum value

82 -float SmallRT = 20.0;  
82 +float SmallRT = 45.0;   // The minimum value has been increased because of the sensibility of the sensor

83 -float BigRT = 125.0;   
83 +float BigRT = 100.0;    // The value has been increased to match the minimum value

169 +Config.isActivate = 1;    // The boolean of the structure is set to one to allow our team to effectuate tests on the code

184 -} else if ((MotionBig == false) && (MotionData > SmallMT || RotationData > SmallRT)) {  
184 +} else if (MotionData > SmallMT || RotationData > SmallRT) {  // The first condition has been deleted because of redundancy

197 -PulseBuzzer(5, 500, 1000);  
197 +PulseBuzzer(5, 350, 350, 25);  // The use of the intensity has been added to the call and modifications on the alarm durations has been done

202 -PulseBuzzer(3, 100, 100);  
202 +PulseBuzzer(3, 200, 100, 12);  // The use of the intensity has been added to the call and modifications on the alarm durations has been done

206 -if ((MotionData > SmallMT) || (RotationData > SmallRT)) { // This block of code has been deleted since it only served testing purposes
        -if (MotionData > SmallMT) {
            -Serial.print("WAKE UP : ");
            -Serial.println(MotionData);
        -} else {
            -Serial.print("WAKE UP Rota: ");
            -Serial.println(RotationData);
        -}
214 -}

372  -while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
     -  delay(1000);
     -  network = sim800l->getRegistrationStatus();
     -  Serial.print(network + " ");
     -  Serial.println(F("Problem to register, retry in 1 sec"));
     -  digitalWrite(LEDG, !digitalRead(LEDG));
378  -}  
372 +// while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) { // This block of code has been commented to pass be able to test the code
    +//   delay(1000);
    +//   network = sim800l->getRegistrationStatus();
    +//   Serial.print(network + " ");
    +//   Serial.println(F("Problem to register, retry in 1 sec"));
    +//   digitalWrite(LEDG, !digitalRead(LEDG));
378 +// }  

438 -void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
438 +void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity) { // The value intensity has been added to the function to control the buzzer's intensity

440  -unsigned long currentMillis = millis();
440  +unsigned long timePassed; // The value currentMillis has been renamed and it's value is declared in the next loop

441  +startCycle = millis(); // The variable is given the value equal to the time representing the start of the buzzer's cycle

443  -if (currentRep < repetitions) {
443  +while (repetitions > 0) { // The condition has been modified into a loop

444  +timePassed = millis(); // This variable is set to the current time in milliseconds

	
456 -if (currentMillis - previousMillis >= (buzzerState == LOW ? durationOn : durationOff)) {
456 +if (timePassed- startCycle <= (buzzerState == LOW ? durationOff : durationOn)) { // Calculate the difference of the distance between the start of the cycle and the current time, then compare it to the duration of a cycle

457 -digitalWrite(buzzerPin, buzzerState = !buzzerState);
457 +analogWrite(buzzerPin, (buzzerState == LOW ? 0 : intensity)); // The writting on the pin has been modified to manage different intensities

458 -previousMillis = currentMillis;
459 -if (!buzzerState) currentRep++; // These two lines weren't necessary anymore, thus they were deleted

459 +} else if (timePassed - startCycle > (buzzerState == LOW ? durationOff : durationOn)) { // If the time between the start of the cycle and the present is higher than the duration

460 +buzzerState = !buzzerState;        // Switch the state of the buzzer
461 +startCycle = timePassed;           // Set the new cycle to the present 
462 +if (!buzzerState) repetitions--;   // If the buzzer is off, decrease repetitions



465 -} else {                          // Since we are now using a while loop, the else is no longer needed
465 +analogWrite(buzzerPin, 0);        // Change the buzzer's state to OFF

466 -currentRep = 0;                   // We no longer need this variable so it has been deleted
467 -previousMillis = 0;               // We no longer need this variable so it has been deleted


```