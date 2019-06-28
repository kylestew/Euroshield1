#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010GatedReverbWetDry - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a gated reverb algorithm using the IN1/2 as the
// stereo source and Out 1/2 as the wet+dry result
//
// The controls are as follows:
// 1) Upper Pot: Gate threshold
// 2) Lower Pot: Gate decay time.
// This code is in the public domain.

// Freeverb may require downloading of the Audio Master library from github:
// https://github.com/PaulStoffregen/Audio

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=88,244
AudioMixer4              inputMixer;         //xy=230,145
AudioEffectFreeverbStereo freeverbs1;     //xy=376,189
AudioAnalyzeRMS          rms1;           //xy=381,123
AudioEffectEnvelope      envelope1;      //xy=534,159
AudioEffectEnvelope      envelope2; //xy=536,314
AudioMixer4              outputMixerL;         //xy=692,244
AudioMixer4              outputMixerR;         //xy=706,343
AudioOutputI2S           i2s2;           //xy=860,274.19000244140625
AudioConnection          patchCord1(i2s1, 0, inputMixer, 0);
AudioConnection          patchCord2(i2s1, 0, outputMixerL, 1);
AudioConnection          patchCord3(i2s1, 1, inputMixer, 1);
AudioConnection          patchCord4(i2s1, 1, outputMixerR, 1);
AudioConnection          patchCord5(inputMixer, rms1);
AudioConnection          patchCord6(inputMixer, freeverbs1);
AudioConnection          patchCord7(freeverbs1, 0, envelope1, 0);
AudioConnection          patchCord8(freeverbs1, 1, envelope2, 0);
AudioConnection          patchCord9(envelope1, 0, outputMixerL, 0);
AudioConnection          patchCord10(envelope2, 0, outputMixerR, 0);
AudioConnection          patchCord11(outputMixerL, 0, i2s2, 0);
AudioConnection          patchCord12(outputMixerR, 0, i2s2, 1);
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

  inputMixer.gain(0, 0.5);
  inputMixer.gain(1, 0.5);

  freeverbs1.damping(0);
  freeverbs1.roomsize(1.0);

  envelope1.sustain(1.0);
  envelope1.hold(25);
  envelope2.sustain(1.0);
  envelope2.hold(25);

  outputMixerL.gain(0, 1.0);
  outputMixerL.gain(1, 1.0);
  outputMixerR.gain(0, 1.0);
  outputMixerR.gain(1, 1.0);
}

bool gateOpen = false;

void loop()
{
  if (rms1.available())
  {
    int upperPotValue = analogRead(upperPotInput);
    float gateThreshold = float(upperPotValue) / 1024;

    float rmsValue = rms1.read();

    if (gateThreshold < rmsValue  &&  !gateOpen)
    { 
       envelope1.noteOn();
       envelope2.noteOn();
       gateOpen = true;
    }

    if (rmsValue < gateThreshold  &&  gateOpen  &&  envelope1.isSustain())
    {
       envelope1.noteOff();
       envelope2.noteOff();
       gateOpen = false;
    }

    int lowerPotValue = analogRead(lowerPotInput);
    float releaseTime = ((float(lowerPotValue) / 1024) * 1000) + 30;

    envelope1.release(releaseTime);
    envelope2.release(releaseTime);
  }
}
