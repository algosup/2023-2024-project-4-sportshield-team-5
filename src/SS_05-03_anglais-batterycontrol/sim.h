#ifndef _SIM_
#define _SIM_
#include "global.h"

/*
    This file contains every functions related to the SIM card.
*/

//---------------------------- SETUP -----------------------------

/**
 * This function starts the SIM800L module to enable the use of mobile network.
 * @param None
 * @result None.
 */
void sim_setup(void)
{
    // while (!sim800l->isReady()) {
    //   Serial.println(F("Problem to initialize AT command, retry in 1 sec"));
    //   digitalWrite(LEDR, !digitalRead(LEDR));
    //   delay(1000);
    // }
    // sim800l->enableEchoMode();
    // sim800l->setupGPRS("iot.1nce.net");

    // uint8_t signal = sim800l->getSignal();
    // while (signal <= 0) {
    //   delay(1000);
    //   signal = sim800l->getSignal();
    // }
    // Serial.println(String(signal));
    // NetworkRegistration network = sim800l->getRegistrationStatus();
    // // while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    // //   delay(1000);
    // //   network = sim800l->getRegistrationStatus();
    // //   Serial.print(network + " ");
    // //   Serial.println(F("Problem to register, retry in 1 sec"));
    // //   digitalWrite(LEDG, !digitalRead(LEDG));
    // // }
    // delay(50);
    // sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
    // digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
}

//-------------------------- FUNCTIONS ---------------------------

void SIM_ISR()
{
    send_position = true;
}

#endif