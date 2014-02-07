#define pin_trigger 39
#define pin_echo 41

unsigned long start = 0;
unsugned long duration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);
  attachInterrupt(pin_echo, riseInterrupt, RISING);
  attachInterrupt(pin_echo, fallInterrupt, FALLING);

  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  // trigger ultrasound sensor
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);

  delay(400);

  // wait for pulse
  //duration = pulseIn(pin_echo, HIGH);
  //Serial.print("Duration: ");
  //Serial.println(duration);
  distance = (duration > 0)? duration/58.0 : 0; // duration / speed of sound

  //report
  Serial.print("Distance: ");
  Serial.println(distance);
}

void riseInterrupt() {
  duration = 0;
  start = millis();
}

void fallInterrupt() {
  duration = millis() - start;
}
