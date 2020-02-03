/*******************************************************************
 *  IoT ~ Alarma Arduino UNO                                       *                                                                 
 *  Written by Pablo Avila                                         *
 *******************************************************************/

//PORT ASIGNATION
int AlarmStateLed = 13;                         
char* usercodes[5] = {"962529677"};                     //Authorized user codes
int AlarmState = LOW;                                   //Defect configuration
int pirState = LOW;                                     //Auxiliar variable for PIR Sensor
int AuC =0;                                             //Autentication variable
char charBuf[10];                                       //Buffer to convert from String to Char ~ Add user part
int nusers =0;                                          //Real number of Users

//Sensor Pins
int PIRsensor = 2;
//Alarm Sound Pin
int Alarm = 3;

void setup() {
                                                        //Open serial communications and wait for port to open:
  pinMode(Alarm, OUTPUT);                               //Alarm sound
  pinMode(AlarmStateLed, OUTPUT);                       //Alarm state
  pinMode(PIRsensor, INPUT);                            //PIR Sensor
  Serial.begin(115200);

  for (int i=0; i <= 4; i++){                           //To know real number of users in unsercodes array
  if (usercodes[i] != 0){
    nusers = nusers +1;
    }
  }
}

void loop() { 
//===============================================================================================
// CONTROL COMMANDS
//===============================================================================================
  //Commands from Telegram APP                                                  
  if (Serial.available()) {                               //Request to turn on or off alarm or Sound
    String rm, cod, msg, cmd, un ;
    rm = Serial.readString();
    rm.trim();
    cod = rm.substring(0,9);
    msg = rm.substring(9);
    cmd = rm.substring(9,13);
    for (int i=0; i <= nusers-1; i++){                    //Check if the User is Authorized
      if(cod == usercodes[i]){
        AuC = AuC+1;                                      //If user is in the list, AuC variable will have a 1 value
        }
    }
      if (AuC >= 1){                                      //Verify user identity
        if(msg=="/on"){                                   //Turn on Alarm System
           digitalWrite(AlarmStateLed, HIGH);             //Turn on Alarm On LED indicator
           AlarmState = HIGH;                             //State variable
           SendMessage("Alarm is ON");      //Send Message to all authorized users
           AuC = 0;
         }
         else if(msg=="/off"){                            //Turn off Alarm System
           digitalWrite(AlarmStateLed, LOW);
           AlarmState = LOW;
           digitalWrite(Alarm, LOW);                      //Turn off Alarm Sound if it's necessary
           SendMessage("Alarm is OFF");
           AuC = 0;
         } 
         else if(cmd=="/add" && cod =="962529677"){       //Add User
           un=rm.substring(13,22);
           un.toCharArray(charBuf, 10);
           usercodes[nusers] = charBuf;
           nusers = nusers+1;
           SendMessage("New User Added");
           AuC = 0;
         }
         else{
           Serial.println(cod+"Wrong Command");
           AuC = 0;
          }      
        }
        else if(AuC == 0){
          Serial.println(cod+"Not Autorized User. Contact System Admin");
          delay(5000);
          SendMessage("An unautorized user is trying to access the system");
          }
  }
//===============================================================================================
//ALARM ADVICES
//===============================================================================================
//**********************************************************************************
//ALARM ON
//**********************************************************************************
  if (AlarmState == HIGH){                              //Alarm is ON?
    // PIR SENSOR CODE
    if (digitalRead(PIRsensor) == HIGH){
      if (pirState == LOW) {
        digitalWrite(Alarm, HIGH);
        SendMessage("Movement Registered. Alarm is On");
        pirState = HIGH;
        delay(500);
        }
      } else if (digitalRead(PIRsensor) == LOW) {
          if (pirState == HIGH){
            pirState = LOW;
            }
        }
     // END OF PIR SENSOR CODE
    }
}
//**********************************************************************************
//Send Messages to Security System Administrators
//**********************************************************************************
int SendMessage(char* sms ){
   for (int i=0; i <= nusers-1; i++){                   //Send Message to all authorized users
      Serial.println(usercodes[i]+String(sms));
      delay(5000);   
   } 
}
//**********************************************************************************
