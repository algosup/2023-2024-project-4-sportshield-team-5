#ifndef _LOCK_
#define _LOCK_

#include "definitions.h"

void lockSetup(){
  pinMode(EML_PIN, OUTPUT); 
  digitalWrite(EML_PIN, HIGH);
  delay(TEST_DURATION);
  digitalWrite(EML_PIN, LOW);
}

void unlock(){
  turnPowerSwitches(ON);
  digitalWrite(EML_PIN, HIGH);
  delay(UNLOCKING_DURATION);
  digitalWrite(EML_PIN, LOW);
  turnPowerSwitches(OFF);
}

#endif