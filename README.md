# Telegram-Smart
## Introduction
This code is based on Telegram BOT Library for ESP8266. This project creates an interface between a Telegram Bot and a Arduino (Any), providing total control over it. It is composed by two Arduino codes and a modified library:

1. ESP8266 code
2. Arduino UNO code
3. [ESP8266TelegramBOT.h ](https://github.com/Gianbacchio/ESP8266-TelegramBot) Original library

## Telegram BOT
First, it is neccesary to create a Telegram Bot, once you do it you are given an Access Token, Name and Username that must be added to ESP code in next section. To create your Telegram Bot, talk to BotFather and follow a few simple steps described [here](https://core.telegram.org/bots#botfather).

Check last Telegram API documentation at: https://core.telegram.org/bots/api.

## ESP8266 code
It creates an interface between Telegram API and a Arduino. It connects to Wifi, checks telegram bot messages and send them through ESP serial port to any Arduino. It uses three libraries:
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [WiFiClientSecure.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- ESP8266TelegramBOT.h modified version inside **ESP8266-TelegramBot** directory. It was modified to allow https and avoid serial printings although it can be helpful at beginning to check connection status.

### Installation
The downloaded libraries can be included as a new library into the Arduino IDE selecting the menu:
```
Sketch / include Library / Add .Zip library
```

## Arduino UNO code
