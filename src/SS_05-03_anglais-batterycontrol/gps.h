#ifndef _GPS_
#define _GPS_
#include "definitions.h"

/*
    This file contains every functions related to the geolocalisation of the device.
*/

//---------------------------- SETUP -----------------------------

/**
 * This function starts the GNS PA1010D module to enable geolocalisation.
 * @param None
 * @result None.
 */
void gpsSetup(void)
{
    // pinMode(GPS_WKUP_PIN, OUTPUT);
    // digitalWrite(GPS_WKUP_PIN, LOW);
    // GPS.begin(9600);
    // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // GPS.sendCommand(PMTK_SET_im800l->isReady()) {
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
    // digiNMEA_UPDATE_1HZ);
    // GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
    // GPS.sendCommand("$PMTK225,8*23");   // send to Always Locate backup mode
    // GPS.sendCommand("$PMTK225,9*22");   // send to Always Locate standby mode
    // GPS.sendCommand("$PMTK225,2,4000,15000,24000,90000*16");  // send to periodic standby mode
    // GPS.sendCommand("$PMTK161,0*28");   // send to standby mode
    // }
}

//-------------------------- FUNCTIONS ---------------------------
/**
 * This function converts degrees minutes and decimal minutes coordinates into decimal degrees coordinates.
 * @param dmm_coordinates(String): Degrees minutes and decimal minutes coordinates.
 * @result A string containing decimal degrees coordinates.
 */
String convertDMMToDD(String dmm_coordinates)
{
    int degrees;
    float minutes;
    // Separate coordinates in degrees and decimal minutes
    if (dmm_coordinates.length() == 9)
    {
        degrees = dmm_coordinates.substring(0, 2).toInt();
        minutes = dmm_coordinates.substring(2).toFloat();
    }
    else
    {
        degrees = dmm_coordinates.substring(0, 1).toInt();
        minutes = dmm_coordinates.substring(1).toFloat();
    }
    // Convert decimal minutes to decimal degrees
    float decimal_degrees = degrees + (minutes / 60.0);

    // Convert to string and format coordinates to decimal degrees
    String dd_coordinates = String(decimal_degrees, 10); // You can adjust the number of decimals here

    return dd_coordinates;
}

/**
 * This function checks if the position of the device has been acquired or not.
 * @param None
 * @result None.
 */
void GPSIsr()
{
    if (Config.isActivate != 0)
    {
        if (!position_acquired)
        {
            start_gps = true;
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }
        else
        {
            // digitalWrite(GPS_WKUP_PIN, LOW);
            // GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
            send_position = true;
            position_acquired = false;
        }
    }
}
/**
 * This function starts the GPS if the boolean "start_gps" is true.
 * @param None
 * @result None.
 */
void activateGPS()
{
    if (start_gps == true)
    {
        digitalWrite(GPS_WKUP_PIN, HIGH);
        start_gps = false;
    }
}
#endif