#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010ReverbStereoWetDry - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a reverb algorithm with stereo input and output. The
// incoming signal is passed through to the output and combined with the reverberations
// 1) Top pot: Room Size
// 2) Bottom pot: Damping
//
// This code is in the public domain.
//
// Freeverb may require downloading of the Audio Master library from github:
// https://github.com/PaulStoffregen/Audio


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=116,132
AudioMixer4              mixer3;         //xy=279,225
AudioEffectFreeverbStereo freeverbs1;     //xy=448,299
AudioMixer4              mixer2;         //xy=652,269
AudioMixer4              mixer1;         //xy=653,148
AudioOutputI2S           i2s2;           //xy=827,205
AudioConnection          patchCord1(i2s1, 0, mixer3, 0);
AudioConnection          patchCord2(i2s1, 0, mixer1, 0);
AudioConnection          patchCord3(i2s1, 1, mixer3, 1);
AudioConnection          patchCord4(i2s1, 1, mixer2, 0);
AudioConnection          patchCord5(mixer3, freeverbs1);
AudioConnection          patchCord6(freeverbs1, 0, mixer1, 1);
AudioConnection          patchCord7(freeverbs1, 1, mixer2, 1);
AudioConnection          patchCord8(mixer2, 0, i2s2, 1);
AudioConnection          patchCord9(mixer1, 0, i2s2, 0);
AudioControlSGTL5000     codec;          //xy=192,403
// GUItool: end automatically generated code


int upperPotInput = 20;
int lowerPotInput = 21;

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

  // This is the amount of dry signal present in the output
  mixer1.gain(0, 1.0);
  mixer2.gain(0, 1.0);

  // This is the level of the wet output
  mixer1.gain(1, 1.0);
  mixer2.gain(1, 1.0);

  // This sums the incoming stereo signal to mono as source for the reverb
  mixer3.gain(0, 0.5);
  mixer3.gain(1, 0.5);
}

void loop()
{
  int upperPotValue = analogRead(upperPotInput);
  freeverbs1.roomsize(float(upperPotValue) / 1024);

  int lowerPotValue = analogRead(lowerPotInput);
  freeverbs1.damping(float(lowerPotValue) / 1024);
}
