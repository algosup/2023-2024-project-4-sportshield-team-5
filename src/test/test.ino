void setup() 
{
  Serial.begin(115200);
//  while(!Serial);

  pinMode(P0_31, INPUT);    //Battery Voltage monitoring pin

  pinMode(P0_13, OUTPUT);   //Charge Current setting pin
  pinMode(P0_14, OUTPUT);   //Enable Battery Voltage monitoring pin
  digitalWrite(P0_13, LOW); //Charge Current 100mA   
  digitalWrite(P0_14, LOW); //Enable

  analogReference(AR_INTERNAL2V4);  //Vref=2.4V
  analogReadResolution(12);         //12bits
}

void loop() 
{
  digitalWrite(LED_GREEN, LOW);
  delay(500);
  
  int Vadc = analogRead(P0_31);

  float Vbatt = ((510e3 + 1000e3) / 510e3) * 2.4 * Vadc / 4096;
  Serial.print("0x");Serial.print(Vadc, HEX);
  Serial.print(", "); 
  Serial.println(Vbatt, 3); 
  
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
}