/*********************************************************
SMART-JAR PROJECT
*********************************************************/
  #include <ESP8266WiFi.h> 
  #include <WiFiClient.h>
  #include<WiFiClientSecure.h>
  #include <UniversalTelegramBot.h>
  #include "ThingSpeak.h"
  char ssid[] = "Your wifi name";
  char password[] = "Your wifi password";
  
  unsigned long channelID =XXXXXXX;//Your ThingSpeak channel ID
  unsigned int field_no=1;//Your field no
  const char* writeAPIKey = "XXXXXX"; //Your ThingSpeak Write Api Key
  const char* readAPIKey = "XXXXXXX";//Your ThingSpeak Read Api Key
  long distance;
  #define TELEGRAM_BOT_TOKEN "XXXXXXXX" //Your Telegram Bot Token
  #define CHAT_ID "XXXXXX" //Your Telegram Chat ID
  WiFiClientSecure client;
  WiFiClient client2;
  UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);
  
  int botRequestDelay = 1000;
  unsigned long lastTimeBotRan;
  
  void telegramMessage(int count) 
  {
    Serial.println("Telegram Message");
    Serial.println(String(count));
    for (int i = 0; i < count; i++) {
      String chat_id = String(bot.messages[i].chat_id);
      if (chat_id != CHAT_ID)
      {
        bot.sendMessage(chat_id, "Unfortunately this jar doesn't belong to you...", "");
        continue;
      }
      String text = bot.messages[i].text;
      Serial.println(text);
      String from_name = bot.messages[i].from_name;
      if (text == "/start") {
        String starting = "Welcome, " + from_name + ".\n";
        starting += "Welcome to Smart-Jar! \n\n";
        starting += "You can see your jar's occupancy by texting /Status \n";
        bot.sendMessage(chat_id, starting, "");
      }
      if (text == "/Status") {
        String state="Your occupancy level is : %" + String(distance);
        bot.sendMessage(chat_id,state, "");
      }
      else {
        String warning = "Please text things we provide you! \n";
        uyari += "You can see your jar's occupancy by texting /Status \n";
        bot.sendMessage(chat_id, warning, "");
        }
    }
  }
  void setup() 
  {
    Serial.begin(115200);
    #ifdef ESP8266
      client.setInsecure();
    #endif
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(1000);
      Serial.println("Connecting to wifi...");
    }
    Serial.println(WiFi.localIP());
      ThingSpeak.begin(client2);
      while (!Serial) 
      {
      ; 
      }
  }
    
  void loop() 
  {
    distance=Serial.read();
    if (Serial.available()) 
    {
      Serial.print("Evaluated occupancy : %");
      Serial.println(distance);
      ThingSpeak.writeField (channelID, field_no, distance, writeAPIKey);
      float reading = ThingSpeak.readFloatField(channelID, field_no);
      Serial.print("Occupancy level from ThingSpeak: %"); 
      Serial.println(reading);
      delay(20000);
    }
    if (millis() > lastTimeBotRan + botRequestDelay)  
    {
      int count = bot.getUpdates(bot.last_message_received + 1);
      while(count) 
      {
        Serial.println("Got new message");
        telegramMessage(count);
        count = bot.getUpdates(bot.last_message_received + 1);
      }
      lastTimeBotRan = millis();
    }
  
  }
