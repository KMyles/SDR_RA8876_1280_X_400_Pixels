#include "font_Arial.h"
#include "ER-TFT0784_t3.h"

extern float old_sample;
extern String stepTxt;
extern volatile uint32_t Step;
extern String modeTxt;
extern float FC;
extern float BW;

// Pin connection mapping
ER_TFT0784_t3 tft = ER_TFT0784_t3(
// Teensy pin  // Display        pin
    10,        // RA8876 CS      5
     6,        // RA8876 RESET   11
    11,        // RA8876 MOSI    7
    13,        // RA8876 SCLK    8
    12,        // RA8876 MISO    6
    3,        // SSD2828 CS     31
    5 ,        // SSD2828 RESET  43
    2,         // SSD2828 SDI    34
    4         // SSD2828 SCK    35
);
//External backlight control connected to this Arduino pin
#define BACKLIGHT 9 // Display pin: 14

// Array of Simple RA8876 Basic Colors
PROGMEM uint16_t myColors[] = {
  0x0000,
  0xffff,
  0xf800,
  0xfc10,
  0x8000,
  0x07e0,
  0x87f0,
  0x0400,
  0x001f,
  0x051f,
  0x841f,                   
  0x0010,
  0xffe0,
  0xfff0,
  0x8400,
  0x07ff,
  0x87ff,
  0x0410,
  0xf81f,
  0xfc1f,
  0x8010,
  0xA145
};

void initDisplay()
{

 pinMode(BACKLIGHT, OUTPUT);
 analogWriteFrequency(BACKLIGHT,50000);
 analogWrite(BACKLIGHT, 128);
 
  tft.begin(25000000);
  tft.setRotation(1);
  tft.graphicMode(true);
  tft.setFont(Arial_20);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(735,15);
  tft.print("MHz");
  tft.drawLine(0,100,1280,100,WHITE);
  tft.drawLine(0,325,1280,325,WHITE);
 
}

/////////////////////////////////////////////////////
void meterScale()
{
  int numx=4;
  int numy=80;
  int liney=60;
  
  tft.setFont(Arial_14);   
  tft.setCursor(40,45);
  tft.print("S-Meter:");
  
  tft.setFont(Arial_12);
  tft.setTextColor(WHITE);

   tft.fillRect(125, 58, 176 , 3,WHITE); 
   tft.fillRect(301, 59, 125 , 3,RED); 
  
  
  //tft.drawLine(125,liney,300,liney,WHITE);

  tft.setCursor(125-numx,numy);
  tft.print("0");

  tft.drawLine(150,liney,150,liney+10,WHITE);
  tft.setCursor(150-numx,numy);
  tft.print("1");

  tft.drawLine(175,liney,175,liney+10,WHITE); 
  tft.setCursor(175-numx,numy);
  tft.print("3");


  tft.drawLine(200,liney,200,liney+10,WHITE); 
  tft.setCursor(200-numx,numy);
  tft.print("6");


  tft.drawLine(225,liney,225,liney+10,WHITE); 
  tft.setCursor(225-numx,numy);
  tft.print("7");

  tft.drawLine(250,liney,250,liney+10,WHITE); 
  tft.setCursor(250-numx,numy);
  tft.print("9");

  tft.setTextColor(RED);
 // tft.drawLine(300,liney,425,liney,RED); 
  tft.drawLine(300,liney,300,liney+10,RED); 
  tft.setCursor(295-numx,numy);
  tft.print("20");

  tft.drawLine(355,liney,355,liney+10,RED); 
  tft.setCursor(350-numx,numy);
  tft.print("40");

  tft.drawLine(425,liney,425,liney+10,RED); 
  tft.setCursor(420-numx,numy);
  tft.print("60");
 
}

void drawMeter()
{
   
    tft.fillRect(125, 30, int(old_sample), 10,BLUE);
}

void displayFrequency()
{
  tft.fillRect(570, 5, 160, 40,BLACK);
  tft.setFont(Arial_20);
  tft.setCursor(580, 15);
  tft.setTextColor(myColors[5]);
  tft.print(float(Frequency)/1000,3);
}

void displayMode()
{
  
  tft.fillRect(455, 5, 100, 40,BLACK);
  tft.setFont(Arial_20);
  tft.setCursor(480, 15);
  tft.setTextColor(WHITE);
  tft.print(modeTxt);

}

void displayAGC()
{
 tft.setFont(Arial_14);
 tft.setCursor(1133, 70);
 tft.setTextColor(WHITE);
 tft.print("AGC:");
 tft.setTextColor(GREEN);
 tft.setCursor(1185, 70);
 tft.print("SLOW");
}

void displayStep()
{
 tft.setFont(Arial_16);
 tft.setCursor(740, 70);
 tft.fillRect(770, 65, 90, 23,BLACK);
 tft.setTextColor(WHITE);
 tft.print("TS:");
 tft.setTextColor(GREEN);
 tft.setCursor(778, 70);
 tft.print(String(Step) +" Hz");

}


void displayFilter()
{
 tft.setFont(Arial_16);
 tft.setCursor(865, 15);
 tft.setTextColor(WHITE);
 tft.print("FLT-FC:");
 tft.fillRect(950, 12, 90, 23,BLACK);
 tft.setTextColor(GREEN);
 tft.setCursor(955, 16);
 tft.print(String(FC));

 tft.setCursor(1075, 15);
 tft.setTextColor(WHITE);
 tft.print("FLT-BW:");
 tft.fillRect(1163, 12, 85, 23,BLACK);
 tft.setTextColor(GREEN);
 tft.setCursor(1169, 16);
 tft.print(String(BW));
}

void displayNb()
{
 tft.setFont(Arial_16);
 tft.setCursor(875, 70);
 tft.setTextColor(WHITE);
 tft.print("NB:");
 tft.setTextColor(GREEN);
 tft.setCursor(910, 70);
 tft.print("On");

}

void displaySP()
{
 tft.setFont(Arial_16);
 tft.setCursor(990, 70);
 tft.setTextColor(WHITE);
 tft.print("SP:");
 tft.setTextColor(GREEN);
 tft.setCursor(1025, 70);
 tft.print("On");

}


void displayAttn()
{
 tft.setFont(Arial_16);
 tft.setCursor(480, 70);
 tft.setTextColor(WHITE);
 tft.print("ATTN:");
 tft.setTextColor(GREEN);
 tft.setCursor(543, 70);
 tft.print("-3dB");
}


void displayPre()
{
 tft.setFont(Arial_16);
 tft.setCursor(640, 70);
 tft.setTextColor(WHITE);
 tft.print("PRE:");
 tft.setTextColor(GREEN);
 tft.setCursor(690, 70);
 tft.print("On");
}

void displayTouchbar()
{
 
//tft.drawRoundRect(x0,y0,x1-x0,y1-y0,xr,yr,myColors[c]);

 int z=69; // button height
 int liney=327;
 
 tft.drawLine(127,liney,127,liney+z,WHITE); 
 tft.drawLine(241,liney,241,liney+z,WHITE); 
 tft.drawLine(355,liney,355,liney+z,WHITE); 
 tft.drawLine(469,liney,469,liney+z,WHITE); 
 tft.drawLine(583,liney,583,liney+z,WHITE); 
 tft.drawLine(697,liney,697,liney+z,WHITE); 
 tft.drawLine(801,liney,801,liney+z,WHITE); 
 tft.drawLine(915,liney,915,liney+z,WHITE); 
 tft.drawLine(1039,liney,1039,liney+z,WHITE); 
 tft.drawLine(1153,liney,1153,liney+z,WHITE); 
 
 tft.setFont(Arial_14);
 tft.setCursor(35,355);
 tft.setTextColor(WHITE);
 tft.print("BAND +");

 tft.setFont(Arial_14);
 tft.setCursor(160,355);
 tft.setTextColor(WHITE);
 tft.print("BAND -");

 tft.setFont(Arial_14);
 tft.setCursor(270,355);
 tft.setTextColor(WHITE);
 tft.print("MODE");
 
 tft.setFont(Arial_14);
 tft.setCursor(387,355);
 tft.setTextColor(WHITE);
 tft.print("ATTN");

 tft.setFont(Arial_14);
 tft.setCursor(505,355);
 tft.setTextColor(WHITE);
 tft.print("PRE");

 tft.setFont(Arial_14);
 tft.setCursor(630,355);
 tft.setTextColor(WHITE);
 tft.print("TS");

 tft.setFont(Arial_14);
 tft.setCursor(725,355);
 tft.setTextColor(WHITE);
 tft.print("N/R-T");

 tft.setFont(Arial_14);
 tft.setCursor(840,355);
 tft.setTextColor(WHITE);
 tft.print("N/R-D");

 tft.setFont(Arial_14);
 tft.setCursor(953,355);
 tft.setTextColor(WHITE);
 tft.print("N/R-SP");

 tft.setFont(Arial_14);
 tft.setCursor(1060,355);
 tft.setTextColor(WHITE);
 tft.print("FILTER");

 tft.setFont(Arial_14);
 tft.setCursor(1195,355);
 tft.setTextColor(WHITE);
 tft.print("AGC");
}
