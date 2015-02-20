/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 */
#include <SoftwareSerial.h>

SoftwareSerial esp(10, 11); // RX, TX

int ledPin = 12;
int dbg = 13;
boolean ledState;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(dbg, OUTPUT);

  // set the data rate for the SoftwareSerial port
  esp.begin(9600);
  while (!esp.find("OK")){
  esp.println("AT+RST");
  }
  digitalWrite(dbg,HIGH);
  delay(10);
  digitalWrite(dbg,LOW);
  
  while (!esp.find("OK")){
  esp.println("AT+CWMODE=1");
  }
  digitalWrite(dbg,HIGH);
  delay(10);
  digitalWrite(dbg,LOW);
  
  while (!esp.find("OK")){
  esp.println("AT+CWJAP=\"AlexAlferyFTW\",\"NgSenor410\"");
  }
  digitalWrite(dbg,HIGH);
  delay(10);
  digitalWrite(dbg,LOW);
  
  while (!esp.find("OK")){
  esp.println("AT+CIPMUX=1");
  }
  digitalWrite(dbg,HIGH);
  delay(10);
  digitalWrite(dbg,LOW);
  
  while (!esp.find("OK")){
  esp.println("AT+CIPSERVER=1,4444");
  }
  digitalWrite(dbg,HIGH);
  delay(100);
  digitalWrite(dbg,LOW);
  
}

void loop() // run over and over
{
  while (esp.available()) {
    char command[256];
    memset(command, 0, sizeof(command));  //reset command
    if (esp.find("+IPD,")) {
      char id;
      id = (char)esp.read();
      esp.find(":");  //skip length
      esp.readBytesUntil('=', command, 256);

      if (strcmp(command, "led") == 0)
      {
        char ledcmd[4];
        memset(ledcmd, 0, sizeof(ledcmd));
        esp.readBytes(ledcmd, 3);
        if (strcmp(ledcmd, "?") == 0)
        {
          esp.println(ledState);
        }
        else if (strcmp(ledcmd, "13H") == 0)
        {
          ledState = 1;
          digitalWrite(ledPin, ledState);
        }
        else if (strcmp(ledcmd, "13L") == 0)
        {
          ledState = 0;
          digitalWrite(ledPin, ledState);
        }
        esp.print("AT+CIPSEND=");
        esp.print(id);
        Serial.print(id);
        esp.print(',');
        esp.println('1');
        if (esp.find(">")) {
          esp.print(ledState);
          Serial.println("sent ledState");
          esp.print("AT+CIPCLOSE=");
          esp.println(id);
        } else {
          Serial.println("failed");
          esp.print("AT+CIPCLOSE=");
          esp.println(id);

        }

      } else {

      }

    }
  }
}

