#include <IRremote.h>
#include <LedControl.h> 

const int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);

decode_results results;

const int DIN = 11; //MOSI
const int CS = 7;
const int CLK = 13; //SCK

LedControl ledControl = LedControl(DIN, CLK, CS, 0);

short channel = 0;

 byte face [8] = 
  {
    B00000000,
    B01100110,
    B01100110,
    B00000000,
    B01000010,
    B01000010,
    B01111110,
    B00000000
  };

byte dots1 [8]
{
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101
};

byte dots2 [8]
{
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010
};

short numbers[40][8] = 
{
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

short nm = 0;

short rabdomCol;
short randomRow;


void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
  irrecv.blink13(true);

  ledControl.shutdown(0, false);   
  ledControl.setIntensity(0,3);  
  ledControl.clearDisplay(0);  

  randomSeed(analogRead(0));  
}

void loop() 
{
  
  if (irrecv.decode(&results))
  irrecv.resume(); 

  delay(100);
  
    if (results.decode_type == SONY) 
    {
      Serial.println(results.value, HEX);
    } 

    if(results.value == 0xF807FF00)
    {
      channel--;
      if(channel == -1)
      {
        channel = 4;
      }

      ledControl.clearDisplay(0);  
    }
    else if (results.value == 0xEA15FF00)
    {
      channel++;
      if(channel == 5)
      {
        channel = 0;
      }
  
      ledControl.clearDisplay(0);  
    }

    results.value = 0;

  switch(channel)
    {
      case 0:
      {
        for(int i = 0; i<8; i++)
        {
          ledControl.setRow(0,i,face[i]);
        }
      }
      break;

      case 1:
      { 
        for(int i = 0; i<8; i++)
        {
          ledControl.setRow(0,i,dots1[i]);
        }
        delay(50);
        for(int i = 0; i<8; i++)
        {
          ledControl.setRow(0,i,dots2[i]);
        }
        delay(50);
      }
      break;

      case 2:
      {
        for(int n = 0; n < 5; n++)
        {
          for (int j = 0, n = 0; j<8; j++, n++)
          {
            for (int i = 0; i < 8; i++)
            {
              ledControl.setLed(0,i,j,numbers[i+nm][j]);
            }
          }

          delay(1000);
          ledControl.clearDisplay(0);

          nm += 8;
          if(nm == 40)
          {
            nm = 0;
          }
        }
      }
      break;

      case 3:
      {
        
        randomRow = random(8);
        rabdomCol = random(8);

        ledControl.setLed(0,randomRow,rabdomCol,true);       
      }
      break;

      case 4:
      {
        for(int i = 0; i < 8; i++)
        {
          for(int j = 0; j < 8; j++)
          {
            ledControl.setLed(0,i,j,true); 
            delay(100);
            ledControl.setLed(0,i,j,false); 
          }          
        }
      }
      break;
    }

  delay(100);
}