/*********************************************************
  SMART-JAR PROJECT
*********************************************************/
  #include <SoftwareSerial.h>
  const int trigPin = 9;
  const int echoPin = 8;
  long duration;
  long distance; 
  float level;
  SoftwareSerial espSerial(5, 6);
  void setup() {
    pinMode(trigPin,OUTPUT); 
    pinMode(echoPin,INPUT); 
    Serial.begin(115200);
    espSerial.begin(115200);
    delay(2000);
  }
  void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.034/2;
    level =((14-distance)/14.0)*100;
    delay(2000);
    espSerial.println(level);
    delay(1000);
  }
