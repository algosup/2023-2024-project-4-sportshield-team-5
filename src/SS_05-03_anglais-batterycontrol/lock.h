#ifndef _LOCK_
#define _LOCK_

#include "definitions.h"
#include "power.h"

void lockSetup(){
  pinMode(EML_PIN, OUTPUT); 
  //pinMode(CONTACT_LOCK_PIN, INPUT);
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