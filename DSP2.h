#include "OpenAudio_ArduinoLibrary.h"
#include "AudioStream_F32.h"
#include "Hilbert.h"
#include <Audio.h>
#include <Wire.h>
#include "analyze_peak_f32.h"
#include "AudioFilterFIRGeneral_F32.h"
#include "AudioFilterConvolution_F32.h"
#include "AudioSpectralDenoise_F32.h"    


extern void displayMode();
extern void displayFilter();
void displayFilter();
String Mode="LSB";
String modeTxt="CWn";
int m;
float FC;
float BW;
  float* pPwr;
const float sample_rate_Hz = 48000.0f ;  // 24000, 44117, or other frequencies listed above
const int   audio_block_samples = 128;

AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

AudioInputI2S_F32        audioInI2S1; 
AudioFilterFIR_F32 filterFIRgeneral2; 
AudioFilterFIR_F32 filterFIRgeneral1; 
AudioMixer4_F32          mixer4_1;   
AudioAnalyzePeak_F32    peak; 
AudioAnalyzeFFT1024_IQ_F32 FFT1024iq1;      //xy=243,532
AudioFilterConvolution_F32 LPF;  
AudioSpectralDenoise_F32 spectral;
radioNoiseBlanker_F32        nb1;
AudioOutputI2S_F32       audioOutI2S1;  

AudioConnection_F32          patchCord0l(audioInI2S1, 0,FFT1024iq1, 0);
AudioConnection_F32          patchCord0r(audioInI2S1, 1,FFT1024iq1, 1);

AudioConnection_F32          patchCord1(audioInI2S1, 0, filterFIRgeneral1, 0);
AudioConnection_F32          patchCord2(audioInI2S1, 1, filterFIRgeneral2, 1);
AudioConnection_F32          patchCord3(filterFIRgeneral1, 0, mixer4_1, 0);
AudioConnection_F32          patchCord4(filterFIRgeneral2, 0, mixer4_1, 1);
AudioConnection_F32          patchCord4d(mixer4_1, 0, peak, 0);
AudioConnection_F32          patchCord4a(mixer4_1, 0, spectral, 0);
AudioConnection_F32          patchCord5a(mixer4_1, 0, LPF, 0);
AudioConnection_F32          patchCord5b(LPF, 0, audioOutI2S1, 0);
AudioConnection_F32          patchCord6a(LPF, 0, audioOutI2S1, 1);

//AudioConnection_F32          patchCord10(audioInI2S1, 0, audioOutI2S1, 0);
//AudioConnection_F32          patchCord11(audioInI2S1, 1, audioOutI2S1, 1);


void initDsp()
{

//float32_t workspace[4128];

AudioMemory(20); // 16 bit audio memory allocation
AudioMemory_F32(50, audio_settings);

//filterFIRgeneral1.LoadCoeffs(101, Hilbert_Plus45_3000H,workspace);
//filterFIRgeneral2.LoadCoeffs(101, Hilbert_Minus45_3000H,workspace);

filterFIRgeneral1.begin(Hilbert_Plus45_3000N,101);   //Left Channel
filterFIRgeneral2.begin(Hilbert_Minus45_3000N,101);  //Right Channel
mixer4_1.gain(0,1.0);
mixer4_1.gain(1,-1.0);
//spectral.setup(audio_settings, 128);
LPF.initFilter(1350.0f, 60.0f, BANDPASS, 2300.0f);
}

void setMode()
{
      if(m==0)  
      {
        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);
        
        FC=500.0f;
        BW=200.0f;
        modeTxt="CWn";
        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);
        LPF.initFilter(FC, 60.0f, BANDPASS,BW);
     
      }
    
      if(n==1)
      {

        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);
        
        FC=500.0f;
        BW=500.0f;
        
        modeTxt="CW";
        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);
        LPF.initFilter(FC, 60.0f, BANDPASS,BW);
        void displayFilter();
      }

      if(n==2)
      {

        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,-1.0);
        
        FC=1150.0f;
        BW=2300.0f;
        
        modeTxt="LSB";
        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,-1.0);
        LPF.initFilter(FC, 60.0f, BANDPASS,BW);
        void displayFilter();
      }

      if(n==3)
      {

        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);

        FC=1150.0f;
        BW=2300.0f;
        modeTxt="USB";
        mixer4_1.gain(0,1.0);
        mixer4_1.gain(1,1.0);
        LPF.initFilter(FC, 60.0f, BANDPASS, BW);
      }

      if(n==4)
      {

        FC=900.0f;
        BW=1800.0f;
        modeTxt="RTTY";
        LPF.initFilter(FC, 60.0f, BANDPASS,BW);
      }

       if(n==5)
      {

        FC=2000.0f;
        BW=4000.0f;
        modeTxt="DATA";
        LPF.initFilter(FC, 60.0f, BANDPASS,BW);
      }
     
      if(n==5)
      {
        n=0;   // no more steps
      }
      else
      {
        n=n+1; // still steps left
      }
       displayMode(); // Serial.println(Steptxt);  //show me the step in serial monitor
       displayFilter();
}

void initSpectrum()
{
  float* pPwr;
  Serial.begin(9600);
  delay(1000);
  AudioMemory_F32(50);
  Serial.println("FFT1024IQ Test");

 
  // or pick T4.x bin center
  //sine_cos1.frequency(689.0625f);

  // or pick any old frequency
  //sine_cos1.frequency(7100.0);

  // elect the output format
  FFT1024iq1.setOutputType(FFT_DBFS);

  // Select the wndow function
  //FFT1024iq1.windowFunction(AudioWindowNone);
  //FFT1024iq1.windowFunction(AudioWindowHanning1024);
  //FFT1024iq1.windowFunction(AudioWindowKaiser1024, 55.0f);
  FFT1024iq1.windowFunction(AudioWindowBlackmanHarris1024);

  // Uncomment to Serial print window function
  float* pw = FFT1024iq1.getWindow();   // Print window
  for (int i=0; i<512; i++) Serial.println(pw[i], 4);

  FFT1024iq1.setNAverage(4);

  // xAxis, bit 0 left/right;  bit 1 low to high;  default 0X03
  FFT1024iq1.setXAxis(0X02);

  delay(1000);
 // // Print output, once
 // if( FFT1024iq1.available() )  {
 //     pPwr = FFT1024iq1.getData();
 //     for(int i=0; i<1024; i++)
 //       Serial.println(*(pPwr + i), 8 );
 //     }
 // Serial.println("");
}

void getFFT()
{
 if(FFT1024iq1.available()) 
 {
      pPwr = FFT1024iq1.getData();
      for(int i=0; i<1024; i++)
      Serial.println(*(pPwr + i), 8 );
 }
  Serial.println("");
}
  


  
