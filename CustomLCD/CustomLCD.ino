/*
  SparkFun Inventor’s Kit
  Circuit 4A-HelloWorld

  The LCD will display the words "Hello World" and show how many seconds have passed since
  the RedBoard was last reset.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
int count = 0;
float voltage = 0;                          //the voltage measured from the TMP36
float degreesC = 0;                         //the temperature in Celsius, calculated from the voltage
float degreesF = 0;                         //the temperature in Fahrenheit, calculated from the voltage
int minutes = 0;
int hours = 0;
byte smile[8] =                             // tells which bit in the array to light up for a smile face
{
                0b00000,

                0b00000,

                0b01010,

                0b00000,

                0b10001,

                0b01110,

                0b00000,

                0b00000
  };
  byte determined[8] =                    // this is the work brief case
  {
      0b00000,
      0b01110,
      0b01010,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b00000
    
    };

    byte degreeMark[8] =
    {
      0b00011,
      0b00011,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000
      
      
     };

     byte computerTime[8] =
     {
      
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b00000,
      0b11111,
      0b00100,
      0b01110
      
      };

void setup() {

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
  
  lcd.createChar(1, smile);
  lcd.createChar(2, determined);
  lcd.createChar(3, degreeMark);
  lcd.createChar(4, computerTime);

}

void loop() {

   voltage = analogRead(A0) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
  degreesF = degreesC * (9.0 / 5.0) + 32.0; //convert the voltage to a temperature in degrees Fahrenheit
  if(count < 15 && minutes == 0 && hours == 0)
  {
      lcd.setCursor(0, 0);  
      lcd.print("Hello, Dylan");
      lcd.setCursor(13,0);
      lcd.write(1);
      lcd.setCursor(0,1);
      lcd.print(count);
      count++;
      delay(1000);
   }
   else if(count < 60 && minutes == 0 && hours == 0 )
   {
        lcd.setCursor(0, 0);              
        lcd.print("Computer Time! ");       
        lcd.write(4);

        lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
        lcd.print(count);       //print the number of seconds that have passed since the last reset
        lcd.setCursor(9,1);
        lcd.print(degreesF);
        lcd.write(3);
        lcd.print("F");
        count++;
        delay(1000);
        
             if(count == 60)
            {
              minutes++;
        
            }
   }
   if(count >= 60)
   {
    count = 0;
    }

    if(minutes == 60)
    {
      minutes = 0;
      hours++;
      }




      else if(minutes >= 1 && hours == 0)
      {
        
        

        lcd.clear();
        lcd.setCursor(0, 0);              
        lcd.print("Computer Time!");     
        lcd.write(4);

        lcd.setCursor(0, 1);             
        lcd.print(minutes);       //print the number of minutes that have passed since the last reset
        lcd.print(":");
        lcd.print(count);
        lcd.setCursor(9,1);
        lcd.print(degreesF);
        lcd.write(3);
        lcd.print("F");
        count++;
        delay(1000);
        

         if(count == 60)
          {
             minutes++;
        
          }

         
                
        }

        else if(hours >= 1 && minutes >= 0)
        {
                  lcd.clear();
          lcd.setCursor(0, 0);              
          lcd.print("Computer Time! ");       
          lcd.write(4);

          lcd.setCursor(0, 1);             
          lcd.print(hours);       //print the number of hours that have passed since the last reset
          lcd.print(":");
          lcd.print(minutes);
          lcd.print(":");
          lcd.print(count);
          lcd.setCursor(9,1);
          lcd.print(degreesF);
          lcd.write(3);
          lcd.print("F");
          count++;
          delay(1000);
                   if(count == 60)
          {
             minutes++;
        
          }
          
         }
      
   }
   
    
