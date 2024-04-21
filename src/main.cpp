#include <Arduino.h>
   /*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers
I change the adafruit SSD1306 to SH1106
SH1106 driver don't provide several functions such as scroll commands.
  Place a needle on the compass face and spin it. 
  Magnet strength will show on the display
 A4=SDA A5=SCK A6=VCC A7=GND
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
long AV = 50;
int lpcnt = 0;
long i;


#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

void testprintaverage(int avr){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("  Magnetic Strength");
  display.println("");
  display.println("");
  display.setTextSize(4);
  display.println(avr, DEC);
  display.display();
}

void testdrawline(unsigned long bar) {
    int Dbar = bar / 10;  
    display.drawLine(0, 60, Dbar, 60, WHITE);
    display.drawLine(Dbar, 60, 128, 60, BLACK);
    display.display();
}


void setup()   {      
  digitalWrite(A7,LOW);
  digitalWrite(A6,HIGH);
  pinMode(A7,OUTPUT);
  pinMode(A6,OUTPUT);          
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("OLED_show_Needle_Magnetism-2024-04-20");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(100);
  testdrawline(50);
  display.display();
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("  Magnetic Strength");
  display.println("");
 display.setTextSize(4);
  int N = 9999;
  display.println(N, DEC);
  display.display();
  delay(100);
}


void loop() {
//  i = analogRead(A0)*3;
  while(Serial.available()){
    i = Serial.parseInt();
    if(i > 0){
      AV = (AV * 29 + i) / 30;
      Serial.print(i);
      Serial.print(", ");
      Serial.println(AV);
    // delay (1);
    lpcnt++;
      if(lpcnt > 40){
        lpcnt = 0;
        display.clearDisplay();
        testprintaverage(AV);
      }
    }
  }
}
 




