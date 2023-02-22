#include <LedControl.h>

int DIN = 11; //MOSI
int CS = 7;
int CLK = 13; //SCK

LedControl ledControl = LedControl(DIN, CLK, CS, 0);

void setup()
{
  ledControl.shutdown(0, false);   //Pierwszy argument to numer matrixa (mamy jeden więc 0)
  ledControl.setIntensity(0,3);  //Jasność ledów 
  ledControl.clearDisplay(0);     //Czyści matrix
}

void loop()
{
  //ledControl.setLed(addr,row,col,state);
  //ledControl.setLed(0,0,2,true);    //Zapalenie trzeciego led w pierwszym rzędzie

  //ledControl.setRow(addr,row,val);
  //ledControl.setRow(0,0,B00100000); //Zapalenie trzeciego led w pierwszym rzędzie

  ledControl.clearDisplay(0);

  byte diagonal [8] = 
  {
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000100,
    B00000010,
    B00000001
  };


{
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }
  
  for(int i = 0; i<8; i++)
  {
    ledControl.setRow(0,i,diagonal[i]); //Wyświetlenie przekątnej
  }

  // ledControl.clearDisplay(0);

  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      ledControl.setLed(0,j,i,true);
      delay(10);
    }
  }
  
}