#include "Audio.h"       // Teensy I16 Audio Library
#include "OpenAudio_ArduinoLibrary.h" // F32 library
#include "analyze_peak_f32.h"
#include "AudioStream_F32.h"
#include "Hilbert.h"
extern ER_TFT0784_t3 tft;

const float sample_rate_Hz = 48000.0f ;  // 24000, 44117, or other frequencies listed above
const int   audio_block_samples = 128;

AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

AudioInputI2S_F32       Input(audio_settings);

AudioAnalyzePeak_F32    peak;
AudioAnalyzeFFT256_IQ_F32 spectrum;
AudioOutputI2S_F32          Output(audio_settings);

AudioConnection_F32     patchCord3l(Input,0,Output,0);
AudioConnection_F32     patchCord3R(Input,1,Output,1);
AudioConnection_F32     patchCord3M(Input,0,peak,0);

void initDsp()
{
 AudioMemory(20); // 16 bit audio memory allocation
 AudioMemory_F32(50, audio_settings);

}

void Spectrum_ILI9341()
{
  float* pPwr;
  int bar;
  spectrum.setOutputType(FFT_RMS);
 // Select the wndow function
  //FFT256iq1.windowFunction(AudioWindowNone);
  //FFT256iq1.windowFunction(AudioWindowHanning256);
  //FFT256iq1.windowFunction(AudioWindowKaiser256, 55.0f);
  spectrum.windowFunction(AudioWindowBlackmanHarris256);
  spectrum.setXAxis(0X03);
  spectrum.setNAverage(15); 
  
 if(spectrum.available())
 {
      pPwr = spectrum.getData();
     for(int i=1                                                                                                            ; i<256; i++)
     {
      bar= int(*(pPwr + i)*100);        //calculates power in emission
     // bar=bar/6;                      //scaling factor
      if (bar >60) bar=60;              //sets bar height 

   //   tft.drawLine(i,200,i,200,GREEN);

    //   tft.drawLine(i, 145-bar,i,bar,GREEN);//modify these line
      // tft.drawLine((i*1)+32, 80,64-bar,BLACK);   //modify these lines
     }
    
 }

}
