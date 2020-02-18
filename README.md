# Telegram-Smart Home Alarm
Telegram Home alarm is capable of:
- On/Off alarm through Telegram
- Send you alerts when intrusion is detected (PIR sensor)
- Add new allowed users
- Add new commands and sensors on code depending on your needs
## Introduction
This code is based on Telegram BOT Library for ESP8266. This project creates an interface between a Telegram Bot and a Arduino (Any), providing total control over it. It is composed by two Arduino codes and a ESP8266TelegramBOT modified library:

1. ESP8266 code
2. Arduino UNO code
3. [ESP8266TelegramBOT.h ](https://github.com/Gianbacchio/ESP8266-TelegramBot) Original library

## Telegram BOT
First, it is necessary to create a Telegram Bot, once you do it you are given an Access Token, Name and Username that must be added to ESP code in next section. To create your Telegram Bot, talk to BotFather and follow a few simple steps described [here](https://core.telegram.org/bots#botfather).

Check last Telegram API documentation at: https://core.telegram.org/bots/api.

## ESP8266 code
It creates an interface between Telegram API and a Arduino. It connects to WiFi, checks telegram bot messages and send them through ESP serial port to any Arduino. It uses three libraries:
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [WiFiClientSecure.h](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- ESP8266TelegramBOT.h modified version inside **ESP8266-TelegramBot** directory. It was modified to allow https and avoid serial printings although it can be helpful at beginning to check connection status.

### Installation
The downloaded libraries can be included as a new library into the Arduino IDE selecting the menu:
```
Sketch / include Library / Add .Zip library
```
### Programming ESP8266 01
Programming ESP8266 01 can be a bit tricky. Next connection diagram could be useful. If you do not own a FDTI, it is always possible to replace it by an Arduino UNO taking off the microcontroller. 

<img src="http://lasergrbl.com/wp-content/uploads/2017/07/ESP8266_FTDI_RST_bb.jpg" width="250">


## Arduino UNO code
This code reads serial port for messages from ESP8266. If message is available, checks authorization and do the required command. Code can be found on **ArduinoCode** library.
