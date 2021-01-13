/*********************************************************
  BSM313 Nesnelerin İnterneti ve Uygulamaları Dersi Proje Ödevi
  Proje Adı: Akıllı Kavanoz
  Öğrenci Adı: Hayriye Maide YILDIZ
  Öğrenci No: B191210310
  Grubu: 1-A
*********************************************************/
  #include <ESP8266WiFi.h> 
  #include <WiFiClient.h>
  #include<WiFiClientSecure.h>
  #include <UniversalTelegramBot.h>
  #include "ThingSpeak.h"
  char ssid[] = "FiberHGW_ZTPX24_2.4GHz";
  char password[] = "4tytUTgRfT";
  
  unsigned long channelID =1256358;
  unsigned int field_no=1;
  const char* writeAPIKey = "VE4V404C03P8LWFQ";
  const char* readAPIKey = "2L9HWNX0LM0IO3JY";
  long uzaklik;
  #define TELEGRAM_BOT_TOKEN "1418071653:AAENcFyaIBbJUzVg46rbeQX-w_l5LGEh53k"
  #define CHAT_ID "1379523364"
  WiFiClientSecure client;
  WiFiClient client2;
  UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);
  
  int botRequestDelay = 1000;
  unsigned long lastTimeBotRan;
  
  void telegramMesaji(int mesajSayisi) 
  {
    Serial.println("Telegram Mesajı");
    Serial.println(String(mesajSayisi));
    for (int i = 0; i < mesajSayisi; i++) {
      String chat_id = String(bot.messages[i].chat_id);
      if (chat_id != CHAT_ID)
      {
        bot.sendMessage(chat_id, "Maalesef bu kavanoz size ait değil...", "");
        continue;
      }
      String text = bot.messages[i].text;
      Serial.println(text);
      String from_name = bot.messages[i].from_name;
      if (text == "/start") {
        String baslangic = "Hoşgeldin, " + from_name + ".\n";
        baslangic += "Akıllı Kavanoza Hoşgeldiniz! \n\n";
        baslangic += "/Durum yazarak kavanozunuzun doluluk oranını görebilirsiniz. \n";
        bot.sendMessage(chat_id, baslangic, "");
      }
      if (text == "/Durum") {
        String durum="Kavanozunuzun doluluk oranı: %" + String(uzaklik);
        bot.sendMessage(chat_id,durum, "");
      }
      else {
        String uyari = "Lütfen belli komutları girin! \n";
        uyari += "/Durum yazarak kavanozunuzun doluluk oranını görebilirsiniz. \n";
        bot.sendMessage(chat_id, uyari, "");
        }
    }
  }
  void setup() 
  {
    Serial.begin(115200);
    #ifdef ESP8266
      //WiFiSecureClient metodu TelegramBot uygulaması için gerekiyor.
      //Ama Thinkspeak bağlantısında sıkıntı çıkardığı için burada client.setInsecure kullanılmıştır.
      client.setInsecure();
    #endif
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(1000);
      Serial.println("WiFi bağlantısı yapılıyor...");
    }
    Serial.println(WiFi.localIP());
      ThingSpeak.begin(client2);
      while (!Serial) 
      {
      ; // Serial portun bağlanması için bekler.
      }
  }
    
  void loop() 
  {
    uzaklik=Serial.read();
    if (Serial.available()) 
    {
      Serial.print("Hesaplanan dolum oranı: %");
      Serial.println(uzaklik);
      ThingSpeak.writeField (channelID, field_no, uzaklik, writeAPIKey);
      float oku = ThingSpeak.readFloatField(channelID, field_no);
      Serial.print("ThingSpeak’ten Okunan Dolum Oranı: %"); 
      Serial.println(oku);
      delay(20000);
    }
    if (millis() > lastTimeBotRan + botRequestDelay)  
    {
      int mesajSayisi = bot.getUpdates(bot.last_message_received + 1);
      while(mesajSayisi) 
      {
        Serial.println("Mesaj var");
        telegramMesaji(mesajSayisi);
        mesajSayisi = bot.getUpdates(bot.last_message_received + 1);
      }
      lastTimeBotRan = millis();
    }
  
  }
