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

void NFCUnlock(void)
{
    // activate electromagnet
    Serial.println("Unlock");
    digitalWrite(aimant_pin, HIGH);
    delay(2000);
    digitalWrite(aimant_pin, LOW);
}

#endif // DEBUG