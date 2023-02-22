#include <IRremote.h>

IRsend irsend(5); //D1

void setup() 
{
  pinMode(4, INPUT_PULLUP); //D2
  pinMode(0, INPUT_PULLUP); //D3
  pinMode(2, OUTPUT); //D4
}

void loop() {

  if(digitalRead(4) == LOW)
  {
    irsend.sendSony(0xF807FF00, 32);
    digitalWrite(2, HIGH);
    delay(100);
  }
  else if(digitalRead(0) == LOW)
  {
    irsend.sendSony(0xEA15FF00, 32);
    digitalWrite(2, HIGH);
    delay(100);
  }

   digitalWrite(2, LOW);
}


