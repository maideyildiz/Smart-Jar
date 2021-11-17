# Smart-Jar
This is an easy IoT project that can track your jar's occupancy ratio and show it to you on Telegram.

For this project, I used Hc-SR04 Ultrasonic Sensor (which is not really the best choice but it's cheaper), Arduino Uno, Nodemcu ESP8266, and jumper cables. (Instead of Nodemcu you can also use the Esp8266 wifi module that one is cheaper but I already had Nodemcu so I used what I have.)

First, if you don't have a Telegram or ThingSpeak account sign up for those.

Then you need to create TelegramBot, just text to BotFather, and it's all done!

All connection is on the Connection.pdf file that I upload here.

Once you connect everything, first load code to Arduino, then load the code to Nodemcu without connecting the RX TX pins.

When code loaded connect RX, TX pins and you good to go!

You can text to the bot you created and see your occupancy level easily!

