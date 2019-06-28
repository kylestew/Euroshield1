#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010Saw - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates the simplest possible generation of a Sawtooth waveform
// from OUT 1/2
//
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=110,75
AudioOutputI2S           audioOutput;        // audio shield: headphones & line-out
AudioConnection          patchCord1(waveform1, 0, audioOutput, 0);
AudioConnection          patchCord2(waveform1, 0, audioOutput, 1);
// GUItool: end automatically generated code

AudioControlSGTL5000 audioShield;

void setup()
{
  audioShield.enable();
  audioShield.volume(0.82);
  
  AudioMemory(15);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.frequency(10);
  waveform1.amplitude(0.99);
}

void loop() {
}
