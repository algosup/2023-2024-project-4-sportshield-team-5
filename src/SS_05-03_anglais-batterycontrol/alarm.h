#ifndef _ALARM_
#define _ALARM_
#include "definitions.h"

/*
    This file contains every functions related to the buzzer.
*/

//-------------------------- FUNCTIONS ---------------------------

void alarmSetup(){
  pinMode(BUZZER_PIN, OUTPUT); 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(TEST_DURATION);
  digitalWrite(BUZZER_PIN, LOW);
}

/**
 * This function starts the buzzer to generate a sound with a given intensity.
 * @param repetations (int): The number of repetitions emitted by the buzzer.
 * @param duration_On (long): The time the sound lasts in each repetition.
 * @param duration_Off (long): The time the buzzer is silent between each sound.
 * @param intensity (int): The intensity of the sound, from 0 to 255.
 * @result None.
 */
void pulseBuzzer(int repetitions, unsigned long duration_On, unsigned long duration_Off, int intensity)
{
    static int buzzer_state = LOW;
    unsigned long time_passed;

    start_cycle = millis();
    while (repetitions > 0)
    {
        time_passed = millis();
        BLE.poll();
        if (AlarmCharacteristic.value() != 0 && is_authenticate)
        {
            AlarmCharacteristic.setValue(0);
            break;
        }

        if (time_passed - start_cycle <= (buzzer_state == LOW ? duration_Off : duration_On))
        {

            analogWrite(BUZZER_PIN, (buzzer_state == LOW ? 0 : intensity));
        }
        else if (time_passed - start_cycle > (buzzer_state == LOW ? duration_Off : duration_On))
        {

            buzzer_state = !buzzer_state;
            start_cycle = time_passed;
            if (!buzzer_state)
                repetitions--;
        }
    }
    // Reset variables after performing all repetitions
    analogWrite(BUZZER_PIN, 0);
    delay(500);
    //reset the motion detected
}

#endif