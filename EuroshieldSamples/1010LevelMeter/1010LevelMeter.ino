#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010LevelMeter - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a simple level meter using the IN 1/2 as audio inputs
// and the 4 LEDs as a bar graph.
//
// This code is in the public domain.


AudioInputI2S        audioInput;         // audio shield: mic or line-in
AudioAnalyzePeak     peak_L;
AudioAnalyzePeak     peak_R;
AudioOutputI2S       audioOutput;        // audio shield: headphones & line-out

AudioConnection c1(audioInput,0,peak_L,0);
AudioConnection c2(audioInput,1,peak_R,0);
AudioConnection c3(audioInput,0,audioOutput,0);
AudioConnection c4(audioInput,1,audioOutput,1);
AudioControlSGTL5000 codec;

#define ledPinCount 4
int ledPins[ledPinCount] = { 3, 4, 5, 6 };

void setup()
{
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield, select input, and enable output
  codec.enable();
  codec.inputSelect(AUDIO_INPUT_LINEIN);
  codec.volume(0.82);
  codec.adcHighPassFilterDisable();
  codec.lineInLevel(0,0);

  for (int i = 0; i < ledPinCount; i++)
    pinMode(ledPins[i], OUTPUT);
}

elapsedMillis fps;

void loop()
{
  if(fps > 24)
  {
    if (peak_L.available() && peak_R.available())
    {
        float peakValueL = peak_L.read();
        float peakValueR = peak_R.read();

        float peakValue = peakValueL;
        if (peakValue < peakValueR)
          peakValue = peakValueR;

        for (int i = 0; i < ledPinCount; i++)
        {
          float levelThreshold = float(i + 1) * 0.2;
          
          if (levelThreshold < peakValue)
            digitalWrite(ledPins[i], HIGH);   // turn the LED on (HIGH is the voltage level)
          else
            digitalWrite(ledPins[i], LOW);   // turn the LED on (HIGH is the voltage level)
        }
        fps=0;
    }
  }
}


