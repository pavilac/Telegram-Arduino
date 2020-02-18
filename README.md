# Telegram-Smart
## Introduction
This code is based on Telegram BOT Library for ESP8266. This project creates an interface between a Telegram Bot and a Arduino (Any), providing total control over it. It is composed by two Arduino codes and a modified library:

1. ESP8266 code
2. Arduino UNO code
3. [ESP8266TelegramBOT.h ](https://github.com/Gianbacchio/ESP8266-TelegramBot) modified library

## ESP8266 code
It creates an interface between Telegram API and a Arduino. It uses three libraries:
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [WiFiClientSecure.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- ESP8266TelegramBOT.h inside **src** directory

### Installation
The downloaded libraries can be included as a new library into the Arduino IDE selecting the menu:
```
Sketch / include Library / Add .Zip library
```

## Arduino UNO code
