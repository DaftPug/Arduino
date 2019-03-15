#include <ADCTouchSensor.h>

#ifdef ADCTOUCH_INTERNAL_GROUNDING

# define GROUNDED_PIN -1

#endif


ADCTouchSensor button0 = ADCTouchSensor(A0, GROUNDED_PIN);

void setup()

{

  Serial.begin(9600);

  button0.begin();

}

float smoothValue = 0;

void loop()

{

  smoothValue = smoothValue * 0.9f + (float)button0.read() * 0.1f;

  Serial.println(smoothValue);

}