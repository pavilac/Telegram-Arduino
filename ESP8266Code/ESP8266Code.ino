/*******************************************************************
 *  IoT Project~ESP8266                                            *                                                                 
 *  written by Pablo Avila-Campos                                  *
 *******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>


// Initialize Wifi connection to the router
char ssid[] = "YOURSSID";                                     //your network SSID (name)
char password[] = "YOURPWD";                                   //your network key

// Initialize Telegram BOT
#define BOTtoken "YOURBOTTOKEN"      //Bot Token
#define BOTname "BOTNAME"
#define BOTusername "BOTUSERNAME"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 50;                                                //Mean time between scan messages
long Bot_lasttime;                                                //last time messages scan has been done
bool Start = false;
void Bot_InputMessages() {

  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++){
      if (bot.message[i][5] != "/code" && bot.message[i][5] != "/start") {
        Serial.println(bot.message[i][4] + bot.message[i][5]);    //Concatenate and send usercode + message to authenticate and run in Arduino Uno
    }
      if (bot.message[i][5] == "/start") {                        //Command Menu
        bot.sendMessage(bot.message[i][4],"**Welcome**", "");
        Start = true;
    }
       if (bot.message[i][5] == "/code") {                        //Code command is served by ESP directly
        bot.sendMessage(bot.message[i][4],"Usercode: "+bot.message[i][4], ""); 
    }
  }
  bot.message[0][0] = "";                                         //All messages have been replied - reset new messages
}

void Bot_OutputMessages() {
  if (Serial.available()) {
    String ms;
    ms = Serial.readString();
    ms.trim();
    bot.sendMessage(ms.substring(0,9),ms.substring(9), "");
  }
}

void setup() { 
  Serial.begin(115200);
  delay(3000);
  //Attempt to connect to Wifi network:
  WiFi.mode(WIFI_STA);
  Serial.println("");
  Serial.println("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid,password) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  bot.begin();                                                  //Launch Bot functionalities  
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);
    Bot_InputMessages();                                        //Check messages from Telegram and sent them to UNO
    Bot_OutputMessages();                                       //Check and send messages
    Bot_lasttime = millis();
  }
}
