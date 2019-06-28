#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010Reverb - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a mono reverb algorithm. The output is just the reverberations.
// 1) Top pot: Room Size
// 2) Bottom pot: Damping
//
// This code is in the public domain.
//
// Freeverb may require downloading of the Audio Master library from github:
// https://github.com/PaulStoffregen/Audio

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=183,239
AudioEffectFreeverb      freeverb1;      //xy=378,232
AudioOutputI2S           i2s2;           //xy=700,266.19000244140625
AudioConnection          patchCord1(i2s1, 0, freeverb1, 0);
AudioConnection          patchCord2(freeverb1, 0, i2s2, 0);
AudioControlSGTL5000     codec;     //xy=630,604
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

}

void loop()
{
  int upperPotValue = analogRead(upperPotInput);
  freeverb1.roomsize(float(upperPotValue) / 1024);

  int lowerPotValue = analogRead(lowerPotInput);
  freeverb1.damping(float(lowerPotValue) / 1024);
}
