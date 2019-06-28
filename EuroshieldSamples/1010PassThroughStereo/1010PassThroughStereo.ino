#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// 1010PassThroughStereo - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates the simplest possible routing of audio from IN 1/2 to OUT 1/2
//
// This code is in the public domain.

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=200,69
AudioOutputI2S           i2s2;           //xy=365,94
AudioConnection          patchCord1(i2s1, 0, i2s2, 0);
AudioConnection          patchCord2(i2s1, 1, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=302,184
// GUItool: end automatically generated code


const int myInput = AUDIO_INPUT_LINEIN;

void setup()
{
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.82);
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.lineInLevel(0,0);
  sgtl5000_1.unmuteHeadphone();
}

void loop()
{
}


