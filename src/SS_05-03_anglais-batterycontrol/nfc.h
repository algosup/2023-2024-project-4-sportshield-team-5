#ifndef _NFC_
#define _NFC_
#include "definitions.h"

/*
    This file contains every functions related to the NFC feature.
*/

/* The NFC libraries aren't finished yet or it would require deeper assembly programming,
   so these functions are not to be used yet.
*/

//-------------------------- FUNCTIONS ---------------------------

void nfcSetup(){
    //future implementation of the NFC setup
}

void checkNfc(){
  if ("a device is detected ?" == 1){
    if ("the phone" == "the good one"){
      Device.alarm_triggered = false;
      unlock();
    }else{
      // send a notification to say someone tried to unlock
    }
  }
}

#endif // DEBUG