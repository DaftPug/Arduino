/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int folder;
int song;
int locked = 0;
int pressed = 0;
void printDetail(uint8_t type, int value);

enum States {
    HELLO = 0,
    GREETINGS = 1,
    GOODBYE = 2,
};

States status = HELLO;

void setup()
    {
        // Setup so the button can be detected
        pinMode(3, INPUT_PULLUP);
        mySoftwareSerial.begin(9600);

        Serial.begin(115200);        
        Serial.println();
        Serial.println(F("DFRobot DFPlayer Mini Demo"));
        Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
        
        if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
            Serial.println(F("Unable to begin:"));
            Serial.println(F("1.Please recheck the connection!"));
            Serial.println(F("2.Please insert the SD card!"));
            while(true);
        }
        Serial.println(F("DFPlayer Mini online."));
        
        myDFPlayer.volume(15);  //Set volume value. From 0 to 30
        chooseFile(HELLO);
        randomSeed(analogRead(0));
    }

void loop()
    {
        // Checking if the button is pressed
        boolean btnPressed = !digitalRead(3);
        // static unsigned long timer = millis();        

        if(btnPressed == true)
        {
            status = GREETINGS;
            if (locked == 0) {
              chooseFile(status);
            }    
            locked = 1;
        } else if (status == GREETINGS && btnPressed == false)
        {
          status = GOODBYE;
        }
        

        if (myDFPlayer.available()) {
          printDetail(myDFPlayer.readType(), myDFPlayer.read());
        }
        if (myDFPlayer.readType() == 5) {
          
          // delay(300);
          // if (played == 2) {
          //   status = HELLO;
          //   played = 0;
          // } else
          // {
          //   played++;
          // }
          
          
          if (status == HELLO) {
            chooseFile(status);
          }          
          if (status == GOODBYE) {
            chooseFile(status);
            status = HELLO;
            // played = 1;
          }           
          locked = 0;
        }     
    }
    

void chooseFile(States state){
    switch (state)
    {
        case HELLO:
            folder = 1;
            // song = 1;
            // Serial.println("HELLO");
            song = random(1, 4);
            break;
        case GREETINGS:
            folder = 2;
            // song = 1;
            // Serial.println("GREETINGS");
            song = random(1, 3);        
            break;
        case GOODBYE:
            folder = 3;
            // song = 1;
            // Serial.println("GOODBYE");
            song = random(1, 5);        
            break;    
        default:
            folder = 1;
            song = 1;
            // Serial.println("DEFAULT");
            // song = int(random(1, 7));
            break;
    }
    myDFPlayer.playFolder(folder, song);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      // Serial.println(myDFPlayer.readType());
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}