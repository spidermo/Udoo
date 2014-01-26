#define pin_trigger 39
#define pin_echo 41

long duration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);

  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  // trigger ultrasound sensor
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(40);

  // wait for pulse
  duration = pulseIn(pin_echo, HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);
  //distance = (duration > 0)? (float)duration/58.0 : 0; // duration / speed of sound

  //report
  //Serial.print("Distance: ");
  //Serial.println(distance);

  delay(1000);
}

