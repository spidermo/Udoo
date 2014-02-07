#include <Adafruit_GPS.h>

// how long are max NMEA lines to parse?
#define GPS_MAXLINELENGTH 120

Adafruit_GPS GPS(&Serial1);

int pin_irsensor_1 = A1;
int pin_ultrasonic_trigger_1 = 39;
int pin_ultrasonic_echo_1 = 41;

float sensorValue = 0;

unsigned long startDT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  setupGPS();
  
  // ultrasonic sensors
  setupUltrasonic(pin_ultrasonic_trigger_1, pin_ultrasonic_echo_1);
  
  // ir sensors
  setupSharpIR(pin_irsensor_1);
}

void loop() {
  // put your main code here, to run repeatedly:
  startDT = millis();
  
  // read value from the ir sensor
  sensorValue = getIRMeasCM(pin_irsensor_1);
  Serial.print("IR1:");
  Serial.println(sensorValue);
  
  // read value from the ultrasonic sensor
  sensorValue = getUltrasonicMeasCM(pin_ultrasonic_trigger_1, pin_ultrasonic_echo_1);
  Serial.print("Ultrasonic1:");
  Serial.println(sensorValue);

  // read gps
  getGPS();
  
  Serial.print("Duration: ");
  Serial.println((float)(millis() - startDT) / 1000.0);
  
  delay(500);
}

/*
  Setup GPS
*/
void setupGPS() {
 // 9600 NMEA is the default baud rate for MTK - some use 4800
  GPS.begin(9600);
  
  // You can adjust which sentences to have the module emit, below
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // uncomment this line to turn on only the "minimum recommended" data for high update rates!
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // uncomment this line to turn on all the available data - for 9600 baud you'll want 1 Hz rate
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  
  // Set the update rate
  // 1 Hz update rate
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  // 5 Hz update rate- for 9600 baud you'll have to set the output to RMC or RMCGGA only (see above)
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
  // 10 Hz update rate - for 9600 baud you'll have to set the output to RMC only (see above)
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA); 
}

void getGPS() {
  char line[GPS_MAXLINELENGTH];
  int pos = 0;
  bool eol = false;
  while (pos < GPS_MAXLINELENGTH && !eol) {
    char c = GPS.read();
    if (c == 10) {
      eol = true;
    } else if (c) {
      line[pos] = c;
      pos++;
    }
  }

  Serial.print("GPS: ");
  Serial.println(line); 
}

/*
  Setup ultrasonic sensor.
*/
void setupUltrasonic(int pin_trigger, int pin_echo) {
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);
}

/*
  Get analog reading from sharp IR GP2Y0A21YK sensor and convert to cm.
*/
float getUltrasonicMeasCM(int pin_trigger, int pin_echo) {
   // trigger ultrasound sensor
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(40);
  
   // wait for pulse
  long duration = pulseIn(pin_echo, HIGH);
  float distance = (duration > 0)? (float)duration/58.0 : 0; // duration / speed of sound
  
  return distance;
}

/*
  Setup sharp IR sensor.
*/
void setupSharpIR(int pin) {
  pinMode(pin, INPUT);
}

/*
  Get analog reading from sharp IR GP2Y0A21YK sensor and convert to cm.
*/
float getIRMeasCM(int pin) {
  int sensorValue = analogRead(pin);
  float distance = 65*pow(sensorValue*(3.3/1024), -1.10);  // input voltage -> cm
  
  return distance;
}

