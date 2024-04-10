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

void launchSmallAlarm(){
  small_alarm_timer_start = millis();
  small_alarm_period_timer_start = millis();
}
int getSmallAlarmTimer(){
  small_alarm_timer = millis() - small_alarm_timer_start;
  return small_alarm_timer;
}
void updateSmallAlarm(){
  small_alarm_timer = millis() - small_alarm_timer_start;
  small_alarm_period_timer = millis() - small_alarm_period_timer_start;
  if (small_alarm_period_timer >= SMALL_ALARM_PERIOD){
    small_alarm_cycles ++;
    small_alarm_period_timer_start = millis();
    for (int i = 0; i+=2; i<SMALL_ALARM_CYCLES*2){
      if (small_alarm_cycles==i){
        analogWrite(BUZZER_PIN, SMALL_ALARM_INTENSITY);
      }else if(small_alarm_cycles==i+1){
        analogWrite(BUZZER_PIN, 0);
      }
    }
  }
}
void resetSmallAlarm(){
  small_alarm_timer_start = 0;
  small_alarm_timer = 0;  
}

void launchBigAlarm(){
  big_alarm_timer_start = millis();
  big_alarm_period_timer_start = millis();
}
int getBigAlarmTimer(){
  big_alarm_timer = millis() - big_alarm_timer_start;
  return big_alarm_timer;
}
void updateBigAlarm(){
  big_alarm_timer = millis() - big_alarm_timer_start;
  big_alarm_period_timer = millis() - big_alarm_period_timer_start;
  if (big_alarm_period_timer >= BIG_ALARM_PERIOD){
    big_alarm_cycles ++;
    big_alarm_period_timer_start = millis();
    for (int i = 0; i+=2; i<BIG_ALARM_CYCLES*2){
      if (big_alarm_cycles==i){
        analogWrite(BUZZER_PIN, BIG_ALARM_INTENSITY);
      }else if(big_alarm_cycles==i+1){
        analogWrite(BUZZER_PIN, 0);
      }
    }
  }
}
void resetBigAlarm(){
  big_alarm_timer_start = 0;
  big_alarm_timer = 0;  
}

#endif