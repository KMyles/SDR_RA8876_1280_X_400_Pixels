#include "font_Arial.h"
#include "ER-TFT0784_t3.h"
#include "VFO.h"
#include "DSP2.h"
#include "Smeter2.h"
#include "Display_RA8876.h"
#include "TouchMenu.h"
#include <Metro.h>

Metro lcd_upd2=Metro(250);  

void setup()
{
Serial.begin(9600);
delay(1000);
initDisplay();
meterScale();
drawMeter();
displayMode();
displayAGC();
displayFilter();
displayNb();
displaySP();
displayAttn();
displayPre();
displayTouchbar();
delay(500);
initVfo();
displayStep(); 
delay(500);
SetFrequency();
initDsp();
initTouch();
 tft.drawLine(0,200,1280,200,GREEN);
}

void loop()
{
  changeFrequency();

  if(lcd_upd2.check()==1) 
    { 
     sMeter();
     getTouch();
    }

} 
