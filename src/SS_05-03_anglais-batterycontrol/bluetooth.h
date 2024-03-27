#ifndef _BLUETOOTH_
#define _BLUETOOTH_

#include "global.h"

/*
    This file contains every functions and initializations related to the Bluetooth.
*/

//---------------------------- SETUP -----------------------------

BLEService PasswordService("19B10000-E8F2-537E-4F6C-D104768A1213"); // Bluetooth® Low Energy Service
BLEService ConfigService("19B10000-E8F2-537E-4F6C-D104768A1214");

//----------------------- CHARACTERISTICS ------------------------
BLEShortCharacteristic PasswordCharacteristic("19B10000-E8F2-537E-4F6C-D104768A1213", BLEWrite); // Bluetooth® Low Energy Characteristic
BLEStringCharacteristic NameCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 20);
BLEStringCharacteristic MACCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1217", BLERead, 20);
BLEBooleanCharacteristic ActivationCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite);
BLEBooleanCharacteristic UnlockCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1216", BLEWrite);
BLEBooleanCharacteristic AlarmCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1218", BLEWrite);

//----------------------- DESCRIPTORS ----------------------------
BLEDescriptor PasswordDescriptor("2901", "Password"); // Bluetooth® Low Energy Descriptor
BLEDescriptor NameDescriptor("2901", "Name");
BLEDescriptor ActivationDescriptor("2901", "Activation");
BLEDescriptor UnlockDescriptor("2901", "Unlock");
BLEDescriptor AlarmDescriptor("2901", "Stop alarm");
BLEDescriptor MACDescriptor("2901", "MAC Address");

//---------------------- Initialization --------------------------
bool BLE_activated = true; // true if the bluetooth is activated
uint32_t tim_connec = 0;   // time in ms or we start to activate the bluetooth following a detection of movements
inline void onConnect(BLEDevice central);
inline void onDisconnect(BLEDevice central);
inline void onWritePassword(BLEDevice central, BLECharacteristic characteristic);
inline void onWriteName(BLEDevice central, BLECharacteristic characteristic);
inline void onReadName(BLEDevice central, BLECharacteristic characteristic);
inline void onWriteActivation(BLEDevice central, BLECharacteristic characteristic);
inline void onReadActivation(BLEDevice central, BLECharacteristic characteristic);
inline void onWriteUnlock(BLEDevice central, BLECharacteristic characteristic);

//------------------------ SETUP FUNCTION ------------------------
/**
 * This function starts the Bluetooth module to enable Bluetooth pairing.
 * @param None
 * @result None.
 */
void ble_setup(void)
{
    if (!BLE.begin())
    {
        Serial.println("starting Bluetooth® Low Energy module failed!");
        while (1) // set a reset in this case? risk of card crash?
            ;
    }
    // set advertised local name and service UUID:
    BLE.setLocalName("SportShield 5");
    BLE.setDeviceName("SportShield 5");
    BLE.setAdvertisedService(PasswordService);
    // add descriptors
    PasswordCharacteristic.addDescriptor(PasswordDescriptor);
    NameCharacteristic.addDescriptor(NameDescriptor);
    ActivationCharacteristic.addDescriptor(ActivationDescriptor);
    UnlockCharacteristic.addDescriptor(UnlockDescriptor);
    AlarmCharacteristic.addDescriptor(AlarmDescriptor);
    MACCharacteristic.addDescriptor(MACDescriptor);
    // add the characteristic to the service
    PasswordService.addCharacteristic(PasswordCharacteristic);
    ConfigService.addCharacteristic(NameCharacteristic);
    ConfigService.addCharacteristic(ActivationCharacteristic);
    ConfigService.addCharacteristic(UnlockCharacteristic);
    ConfigService.addCharacteristic(MACCharacteristic);
    ConfigService.addCharacteristic(AlarmCharacteristic);
    // add service
    BLE.addService(PasswordService);
    BLE.addService(ConfigService);
    // set the initial value for the characeristic:
    PasswordCharacteristic.writeValue(0);
    NameCharacteristic.writeValue("\n");
    ActivationCharacteristic.writeValue(false);
    UnlockCharacteristic.writeValue(false);
    MACCharacteristic.writeValue(BLE.address());
    // set event handler
    BLE.setEventHandler(BLEConnected, onConnect);
    BLE.setEventHandler(BLEDisconnected, onDisconnect);
    PasswordCharacteristic.setEventHandler(BLEWritten, onWritePassword);
    NameCharacteristic.setEventHandler(BLEWritten, onWriteName);
    NameCharacteristic.setEventHandler(BLERead, onReadName);
    ActivationCharacteristic.setEventHandler(BLEWritten, onWriteActivation);
    ActivationCharacteristic.setEventHandler(BLERead, onReadActivation);
    UnlockCharacteristic.setEventHandler(BLEWritten, onWriteUnlock);
    // start advertising
    BLE.advertise();
}

//--------------------------  FUNCTIONS --------------------------

/**
 * This function is called when an external device is paired.
 * @param central (BLEDevice): A paired device.
 * @result Print the MAC address of both the external device and this device.
 */
void onConnect(BLEDevice central)
{
    Serial.print("Connected to ");
    Serial.println(central.address());
    Serial.println(BLE.address());
    digitalWrite(LEDB, LOW);
}

/**
 * This function is called when an external device disconnects.
 * @param central (BLEDevice): A paired device.
 * @result Print the MAC address of the disconnecting device.
 */
void onDisconnect(BLEDevice central)
{
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    isAuthenticate = false;
    digitalWrite(LEDB, HIGH);
}

char Conversion(unsigned short int data)
{
    char mdphexadecimal[5];
    sprintf(mdphexadecimal, "%04X", data);

    for (int i = 0; i < 2; ++i)
    {
        char temp = mdphexadecimal[i];
        mdphexadecimal[i] = mdphexadecimal[2 + i];
        mdphexadecimal[2 + i] = temp;
    }
    // Serial.println("Mot de passe : " + String(valeur) + " ");  //used to see the value in decimal
    Serial.print("Written password  = ");
    Serial.println(mdphexadecimal);
}

/**
 * This function is called when a password is sent by a paired device.
 * @param central (BLEDevice): A paired device.
 * @result If the password is correct, a boolean is turned on.
 */
void onWritePassword(BLEDevice central, BLECharacteristic characteristic)
{
    const int motDePasseAttendu = 1;
    short int value = PasswordCharacteristic.value();
    Conversion(value);
    isAuthenticate = (value == motDePasseAttendu);
    Serial.println(isAuthenticate ? "successful authentication" : "wrong password");
}

/**
 * This function is called when the name of the device is changed.
 * @param central (BLEDevice): A paired device.
 * @param characteristic (BLECharacteristic): The Name characteristic.
 * @result Change the name of the device on the mobile app (not yet implemented).
 */
void onWriteName(BLEDevice central, BLECharacteristic characteristic)
{
    if (isAuthenticate)
    {
        Config.Name = NameCharacteristic.value();
        String value = NameCharacteristic.value();
        Serial.print("Written name : ");
        Serial.println(value);
    }
    else
    {
        NameCharacteristic.writeValue("\n");
    }
}

/**
 * This function is called when the name of the device is read.
 * @param central (BLEDevice): A paired device.
 * @param characteristic (BLECharacteristic): The Name characteristic.
 * @result Read the name of the device.
 */
void onReadName(BLEDevice central, BLECharacteristic characteristic)
{
    Serial.println("CALLBACK READ");
    Serial.println(isAuthenticate);
    if (isAuthenticate)
    {
        NameCharacteristic.writeValue(Config.Name);
    }
    else
    {
        NameCharacteristic.writeValue("\n");
    }
}

/**
 * This function is called when the device security mode is modified.
 * @param central (BLEDevice): A paired device.
 * @param characteristic (BLECharacteristic): The Activation characteristic.
 * @result Change the security mode of the device to on if the input value is different than 0.
 */
void onWriteActivation(BLEDevice central, BLECharacteristic characteristic)
{
    if (isAuthenticate)
    {
        Config.isActivate = ActivationCharacteristic.value();
        if (Config.isActivate != 0)
        {
            Serial.println("Alarm enabled");
            digitalWrite(SIM800_DTR_PIN, LOW); // put in normal mode
            delay(100);
            sim800l->setPowerMode(NORMAL); // set normal functionnality mode
        }
        else
        {
            Serial.print("Deactivation");
            sim800l->setPowerMode(MINIMUM);     // set minimum functionnality mode
            digitalWrite(SIM800_DTR_PIN, HIGH); // put in sleep mode
        }
    }
    else
    {
        ActivationCharacteristic.writeValue(Config.isActivate);
    }
}

/**
 * This function is called when the device security mode is modified.
 * @param central (BLEDevice): A paired device.
 * @param characteristic (BLECharacteristic): The Activation characteristic.
 * @result Read the security mode of the device.
 */
void onReadActivation(BLEDevice central, BLECharacteristic characteristic)
{
    // Serial.println("CALLBACK READ");
    // Serial.println(isAuthenticate);
    ActivationCharacteristic.writeValue(Config.isActivate);
}

/**
 * This function is called when the unlock function is called from a paired device.
 * @param central (BLEDevice): A paired device.
 * @param characteristic (BLECharacteristic): The Unlock characteristic.
 * @result If the user is authentified, unlock the magnet for 2 seconds.
 */
void onWriteUnlock(BLEDevice central, BLECharacteristic characteristic)
{
    if (isAuthenticate)
    {
        // activate electromagnet
        Serial.println("Unlock");
        digitalWrite(aimantPin, HIGH);
        delay(2000);
        digitalWrite(aimantPin, LOW);
    }
}

#endif