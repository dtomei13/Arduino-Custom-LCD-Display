#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 6
#define DELAYVAL 50
#define NUMPIXELS 40

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
  
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

      byte breakHandsDown[8] =
      {
        0b01110,
        0b01110,
        0b00100,
        0b11111,
        0b10101,
        0b00100,
        0b11111,
        0b10001
        
        
        };
      byte breakHandsUp[8] =
      {
        0b01110,
        0b01110,
        0b10101,
        0b11111,
        0b00100,
        0b00100,
        0b11111,
        0b10001
        
        
        };

void setup() {

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
  pixels.clear();
  lcd.createChar(1, smile);
  lcd.createChar(2, determined);
  lcd.createChar(3, degreeMark);
  lcd.createChar(4, computerTime);
  lcd.createChar(5, breakHandsDown);
  lcd.createChar(6, breakHandsUp);
  pixels.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[0]);
}
int x    = matrix.height();
int pass = 0;
void loop() {
             matrix.fillScreen(0);
  matrix.setCursor(0, x);
  matrix.print(F("***"));
  if(--x < -5) {
    x = matrix.height();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
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

      if(minutes == 30 && minutes < 32)
      {
          pixels.clear();
          for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(20, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //delay(DELAYVAL); // Pause before next pass through loop
  }
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Take a Break! ");
        lcd.print(count);
          if(count % 2 == 0)
          {
                    lcd.setCursor(0,1);
                    lcd.write(5);
            
            }
            else
            {
                 lcd.setCursor(0,1);
                 lcd.write(6);
              }

        count++;
        delay(1000);
        if(count == 60)
        {
          minutes++;
          }


        
        } 




      else if(minutes >= 1 && hours == 0 || minutes == 32)
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

        else if(hours >= 1 && minutes >= 0 || minutes == 32)
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
   
    
