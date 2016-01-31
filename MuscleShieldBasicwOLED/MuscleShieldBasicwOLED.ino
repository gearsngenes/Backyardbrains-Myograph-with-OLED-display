#include <SPI.h>
#include <Wire.h>

// ************** Adafruit Oled Initializations
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// ************** Adafruit Oled Initializations Complete 

#define EMG A0

int reading[10];
int finalReading;
byte multiplier = 1;


void oledSetup()
{
    Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(500);
  display.clearDisplay();
  /* end of Adafruit Default Specification */
  /* Basic "hello world!" */


  display.setCursor(0, 0);

   delay(100);
  display.clearDisplay();
}
void setup(){
  Serial.begin(9600);
  oledSetup();
}

void oledPrint()
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
   display.setCursor (5, 20);  
  display.println(finalReading);
  display.display();
  delay(100);
  display.clearDisplay();
}
void loop(){
  for(int i = 0; i < 10; i++){
    reading[i] = analogRead(EMG) * multiplier;
    delay(2);
  }
  for(int i = 0; i < 10; i++){
    finalReading += reading[i];
  }
  finalReading /= 10;
  Serial.print("Value = ");
  Serial.println(finalReading);
  oledPrint();
  delay(100);
}
