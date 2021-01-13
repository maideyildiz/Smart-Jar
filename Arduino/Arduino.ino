/*********************************************************
  BSM313 Nesnelerin İnterneti ve Uygulamaları Dersi Proje Ödevi
  Proje Adı: Akıllı Kavanoz
  Öğrenci Adı: Hayriye Maide YILDIZ
  Öğrenci No: B191210310
  Grubu: 1-A
*********************************************************/
  #include <SoftwareSerial.h>
  const int trigPin = 9;
  const int echoPin = 8;
  long sure;
  long uzaklik; 
  float seviye;
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
    sure = pulseIn(echoPin, HIGH);
    uzaklik = sure*0.034/2;
    seviye =((14-uzaklik)/14.0)*100;
    delay(2000);
    espSerial.println(seviye);
    delay(1000);
  }
