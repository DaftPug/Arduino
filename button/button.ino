#include <SoftwareSerial.h>
#include "Arduino.h"
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX - mp3
DFRobotDFPlayerMini myDFPlayer;
boolean lastState = false;

void printDetail(uint8_t type, int value);
    void setup()
    {
        pinMode(3, INPUT_PULLUP);
        mySoftwareSerial.begin(9600); //for mp3 player

        Serial.begin(9600);
        Serial.println("Initializing mp3player");
        while(!myDFPlayer.begin(mySoftwareSerial)) { //Use softwareSerial to communicate with mp3.
            Serial.println(".");
            delay(300);
        }
        Serial.println("Initialized mp3player");
        myDFPlayer.volume(20); //Set volume value. From 0 to 30

        pinMode(3, INPUT_PULLUP);
        myDFPlayer.play(1); //Play the first mp3

    }

    void loop()
    {
        boolean btnPressed = !digitalRead(3);
        if(btnPressed == true)
        {
            Serial.println("button has been pressed.");
        }

        // if(millis()-timer > 2000) // do something every two seconds)
        //     {
        //     timer = millis();
        //     //do something here
        //     }

    }