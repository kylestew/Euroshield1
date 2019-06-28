#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010NoiseFoller - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a mono noise algorithm that adds white noise that
// follows the overall level of the incoming audio. The upper pot controls the
// noise threshold. This sample uses IN1 and OUT1.
//
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=108,232
AudioAnalyzeRMS          peak1;          //xy=218,78
AudioSynthNoiseWhite     noise1;         //xy=239,148
AudioMixer4              mixer1;         //xy=416,167
AudioOutputI2S           i2s2;           //xy=610,242.19000244140625
AudioConnection          patchCord1(i2s1, 0, peak1, 0);
AudioConnection          patchCord2(i2s1, 0, mixer1, 1);
AudioConnection          patchCord3(i2s1, 1, i2s2, 1);
AudioConnection          patchCord4(noise1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s2, 0);
AudioControlSGTL5000     codec;     //xy=98,449
// GUItool: end automatically generated code

int upperPotInput = 20;
int lowerPotInput = 21;
#define kMaxPotValue  1024

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

}

void loop()
{
    if (peak1.available())
    {
      float peakValue = peak1.read();
      float noiseThreshold = float(analogRead(upperPotInput)) / kMaxPotValue;
      if (peakValue < noiseThreshold)
        noise1.amplitude(0);
      else
        noise1.amplitude(peakValue);
    }
}
