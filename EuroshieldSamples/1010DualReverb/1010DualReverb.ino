#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// 1010DualReverb - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a custom reverb algorithm using the IN1 as the
// source and Out 1/2 as the stereo wet-only result. The controls are as follows:
// 1) Top pot: Early reverb level
// 2) Bottom pot: Late reverb level
//
// Contributed by Nick Peck
// www.youtube.com/underthebigtree
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=73,233
AudioEffectFreeverb      earlyReverb;        //xy=263,331
AudioEffectFreeverb      lateReverb;      //xy=264,242
AudioMixer4              final_mixer;         //xy=558,378
AudioFilterStateVariable final_HPF;        //xy=712,379
AudioOutputI2S           i2s2;           //xy=847,377
AudioConnection          patchCord1(i2s1, 0, lateReverb, 0);
AudioConnection          patchCord2(i2s1, 0, earlyReverb, 0);
AudioConnection          patchCord3(earlyReverb, 0, final_mixer, 2);
AudioConnection          patchCord4(lateReverb, 0, final_mixer, 1);
AudioConnection          patchCord5(final_mixer, 0, final_HPF, 0);
AudioConnection          patchCord6(final_HPF, 2, i2s2, 0);
AudioConnection          patchCord7(final_HPF, 2, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=68,525
// GUItool: end automatically generated code

// Tuned Parameters - adjust to taste
float earlyReverbRoomSize = 0.28;
float earlyReverbDamping = 0.1;
float earlyReverbLevel = 1.0;

float lateReverbRoomSize = 0.6;
float lateReverbDamping = 0.7;
float lateReverbLevel = 1.0;

//final high pass filter to get rid of tubbiness
int HPFCutoff = 60;

int upperPotInput = 20;
int lowerPotInput = 21;

void setup()
{
  AudioMemory(16);

  // turn on debug
  Serial.begin(38400);

    // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.82);
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.lineInLevel(0,0);
  sgtl5000_1.unmuteHeadphone();


  // final HPF filter cutoff
  final_HPF.frequency(HPFCutoff);

  // early verb settings
  final_mixer.gain(2, earlyReverbLevel);
  earlyReverb.roomsize(earlyReverbRoomSize);
  earlyReverb.damping(earlyReverbDamping);  
  
  // late verb settings
  final_mixer.gain(1, lateReverbLevel);
  lateReverb.roomsize(lateReverbRoomSize);
  lateReverb.damping(lateReverbDamping);
}

void loop()
{
  // use two pots as a mixer between early and late reverb
  int upperPotValue = analogRead(upperPotInput);
  final_mixer.gain(2, (float(upperPotValue) / 1024));

  int lowerPotValue = analogRead(lowerPotInput);
  final_mixer.gain(1, (float(lowerPotValue) / 1024));
}
