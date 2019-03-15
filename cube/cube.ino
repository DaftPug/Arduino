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
int counter = 0;
String power_ = "off";
unsigned long interval_one = 5000;     // the time we need to wait
unsigned long interval_two = 333;     // the time we need to wait
unsigned long previousMillis_one = 0;  // millis() returns an unsigned long.
unsigned long previousMillis_two = 0;  // millis() returns an unsigned long.
unsigned long buttonTime = 0;  
void printDetail(uint8_t type, int value);

enum States {
    HELLO = 0,
    GREETINGS = 1,
    GOODBYE = 2,
};

States status = HELLO;
int locked = 0;
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
        
        myDFPlayer.volume(25);  //Set volume value. From 0 to 30
        // Serial.println(F("Playing song 1"));
        // myDFPlayer.playFolder(1, 1);
        // Serial.println(F("Song 1 played"));

        // myDFPlayer.play(1);  //Play the first mp3
    }

void loop()
    {
        // Checking if the button is pressed
        boolean btnPressed = !digitalRead(3);
        static unsigned long timer = millis();        

        if(btnPressed == true)
        {   
            // What happens when the button is pressed:
            // if (buttonTime == 0) {
            //   buttonTime = millis();
            // } else if (buttonTime - previousMillis_two <= interval_two)
            // {
            //   counter += 1;
            // } else
            // {
            //   counter = 0;
            // }
            
            
            
            // static unsigned long timer_two = millis();

            status = GREETINGS;
        }         
        // if (millis() - timer < 1000) {
        //   if (btnPressed == true) {
        //     counter += 1;
        //     Serial.println(counter);
        //   }          
        //   if (counter > 2) {
        //     if (power_ == "on") {
        //       power_ = "off";
        //     } else if (power_ == "off")
        //     {
        //       power_ = "on";
        //     }                        
        //   }
          
        // } else
        // {
        //   counter = 0;
        // }
        
        // if (power_ == "on") {
          // Serial.println(timer - previousMillis_one);
        if (millis() - timer > 5000) {
            timer = millis();
                if (status == GOODBYE) {
                    if (locked < 3) {
                        locked += 1;
                    } else
                    {
                        locked = 0;
                        status = HELLO;
                }                
            }
            if (status == GREETINGS && btnPressed == false) {
                status = GOODBYE;
            }                
            chooseFile(status);  //Play next mp3 every 5 second.
        }      
        // }
        
               
            
            
        
        if (myDFPlayer.available()) {
            printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
        }
    }
    

void chooseFile(States state){
    switch (state)
    {
        case HELLO:
            folder = 1;
            song = int(random(1, 7));
            break;
        case GREETINGS:
            folder = 2;
            song = int(random(1, 4));        
            break;
        case GOODBYE:
            folder = 3;
            song = int(random(1, 4));        
            break;    
        default:
            folder = 1;
            song = int(random(1, 7));
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