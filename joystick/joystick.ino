//This code is to use with dual axis fpv camera cradle that uses two servos, adding a joystick module
//we control the position of the cradle by moving the analog stick, the cradle follows the joystick movements
//Refer to surtrtech.com for more information


int YAxis = 0; //Declaring where the X axis and Y axis of the joystick pins are wired
int XAxis = 1; //Of course analog inputs

void setup() {
 Serial.begin(9600); //Setting the Serial monitor baude rate and launching
 pinMode(XAxis, INPUT); //Declaring the pin modes and servo pins
 pinMode(YAxis, INPUT); 

}
void loop() {
 int X=analogRead(XAxis); //Reading from the X axis potentiometer
 X=X*0.1756; //Converting the range of the potentiometer from 0-1023 to 0-180 limits of the servo you can change them if you have a 360° servos
 X=180-X;// This is used so the servo turn to exact position otherwise it will be inverted
 Serial.print("X: ");
 Serial.println(X);
 int Y=analogRead(YAxis);//Reading from the Y axis potentiometer
 Y=Y*0.1466; //Here we did conversion that suits the servo limits so we went from 0-1023 to 0-150
 Serial.print("Y: ");
 Serial.println(Y);
}