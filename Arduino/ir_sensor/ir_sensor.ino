int pin_irsensor = A1;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  // read value from the sensor
  sensorValue = analogRead(pin_irsensor);
  Serial.println(sensorValue);
  delay(500);
}
