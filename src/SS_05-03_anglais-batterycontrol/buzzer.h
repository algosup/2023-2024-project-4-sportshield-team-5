#ifndef _BUZZER_
#define _BUZZER_
#include "global.h"

/*
    This file contains every functions related to the buzzer.
*/

//-------------------------- FUNCTIONS ---------------------------

/**
 * This function starts the buzzer to generate a sound with a given intensity.
 * @param repetations (int): The number of repetitions emitted by the buzzer.
 * @param durationOn (long): The time the sound lasts in each repetition.
 * @param durationOff (long): The time the buzzer is silent between each sound.
 * @param intensity (int): The intensity of the sound, from 0 to 255.
 * @result None.
 */
void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity)
{
    static int buzzerState = LOW;
    unsigned long timePassed;

    startCycle = millis();
    while (repetitions > 0)
    {
        timePassed = millis();
        BLE.poll();
        if (AlarmCharacteristic.value() != 0 && isAuthenticate)
        {
            AlarmCharacteristic.setValue(0);
            break;
        }

        if (timePassed - startCycle <= (buzzerState == LOW ? durationOff : durationOn))
        {

            analogWrite(buzzerPin, (buzzerState == LOW ? 0 : intensity));
        }
        else if (timePassed - startCycle > (buzzerState == LOW ? durationOff : durationOn))
        {

            buzzerState = !buzzerState;
            startCycle = timePassed;
            if (!buzzerState)
                repetitions--;
        }
    }
    // Reset variables after performing all repetitions
    analogWrite(buzzerPin, 0);
    delay(0500);
    MotionSmall = false;
    MotionBig = false;
}

#endif