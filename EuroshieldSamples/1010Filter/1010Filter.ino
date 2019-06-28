#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010Filter - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a dual filter:
// IN1 -> Filter -> OUT1
// IN2 -> Filter -> OUT2
// The controls are as follows:
// 1) Top pot: Filter cutoff
// 2) Bottom pot: Filter resonance
//
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=205,207
AudioFilterBiquad        biquad2;        //xy=413,239
AudioFilterBiquad        biquad1;        //xy=422,158
AudioOutputI2S           i2s1;           //xy=666,209
AudioConnection          patchCord1(i2s2, 0, biquad1, 0);
AudioConnection          patchCord2(i2s2, 1, biquad2, 0);
AudioConnection          patchCord3(biquad2, 0, i2s1, 1);
AudioConnection          patchCord4(biquad1, 0, i2s1, 0);
AudioControlSGTL5000     codec;     //xy=318,385
// GUItool: end automatically generated code

int upperPotInput = 20;
int lowerPotInput = 21;
#define kMaxPotInput  1024

void setup()
{
  AudioMemory(10);

    // Enable the audio shield, select input, and enable output
  codec.enable();
  codec.inputSelect(AUDIO_INPUT_LINEIN);
  codec.volume(0.82);
  codec.adcHighPassFilterDisable();
  codec.lineInLevel(0,0);
  codec.unmuteHeadphone();
}

void loop()
{
  int upperPotValue = analogRead(upperPotInput);
  float freqValue = (float(upperPotValue) / kMaxPotInput * 16000) + 40;

  int lowerPotValue = analogRead(lowerPotInput);
  float resValue = (float(lowerPotValue) / kMaxPotInput * 3.75) + 0.25;

  biquad1.setLowpass(0, freqValue, resValue);
  biquad2.setLowpass(0, freqValue, resValue);

  delay(5);
}
