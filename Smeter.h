// soft AGC and S meter display by Loftur E. Jónasson TF3LJ/VE2LJX 6/14
//

//extern Adafruit_QDTech tft;
//extern Adafruit_S6D02A1 tft;
extern ER_TFT0784_t3 tft;
extern AudioAnalyzePeak_F32        peak;   // Measure Audio Peak for S meter

float new_sample;  // Raw signal strength (max per 1ms)
float old_sample=0.0;
float s_old=0.0;
float uv, dbuv, s;// microvolts, db-microvolts, s-units
 

void sMeter()
{
   if (peak.available())
    {
      new_sample = peak.read();
      
       old_sample = (old_sample + new_sample)/2;
    //   Serial.println(old_sample*3000,7);
    }

    int barlength =(int)(old_sample*3000);

    if(barlength>300)
    {
      barlength=300;
    }
         
    tft.fillRect(125, 29, 300 , 6,BLACK);   
    tft.fillRect(125, 30, barlength, 5,GREEN); 

   // tft.fillRect(20, 65, 90, 20,BLACK);  
   // tft.setFont(Arial_14);  
   // tft.setCursor(20,70);
   // tft.print((int)(old_sample*3000));
}  


void sMeter2()
{

 if (peak.available())
    {
      new_sample = peak.read();
         
   
// Calculate S units. 50uV = S9
      uv = new_sample*1000;        // microvolts, roughly calibrated
      dbuv = 20.0*log10(uv);
      s = 1.0 + (14.0 + dbuv)/6.0;
      if (s <0.0) s=0.0;
      if (s>9.0)
      {
        dbuv = dbuv - 34.0;
        s = 9.0;
      }
      else dbuv = 0;
      // Print S units
     
 
    tft.fillRect(125, 30, 140, 5,GREEN);  
   
    tft.fillRect(20, 65, 90, 20,BLACK);  
    tft.setFont(Arial_14);  
    tft.setCursor(20,70);
    tft.print(dbuv,5);




}
}
