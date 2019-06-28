#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// 1010VCOCalibration - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates how to get precise values from the CV inputs for the
// 1010VCO sample. The process requires calibration for each hardware device.
// The default values are a useful starting point for demonstration.
//
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=195,187
AudioAnalyzePeak         peak1;          //xy=367,171
AudioAnalyzePeak         peak2;          //xy=367,206
AudioConnection          patchCord1(i2s1, 0, peak1, 0);
AudioConnection          patchCord2(i2s1, 1, peak2, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=246,330
// GUItool: end automatically generated code

// Calibration procedure:
// 1) Connect a steady 1V value to the IN1 and IN2
// 2) Run this sketch with the Serial monitor open
// 3) Record the average peak value for the 1V input
// 4) Change the input voltage to 4V.
// 5) Recording the average peak value for the 4V input.
// 6) Update the relevant values in the VCO sample.
// 7) Comment out the Serial.println for IN1 and uncomment for IN2
// 8) Repeat steps 2-6 for IN2.


void setup()
{
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.82);
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.lineInLevel(0,0);
  sgtl5000_1.unmuteHeadphone();

  Serial.begin(9600);
}

void loop()
{
  if (peak1.available())
  {
    float peakValue1 = peak1.read();
    // Uncomment this line for IN1 calibration
    Serial.println(peakValue1, 4);
  }

  if (peak2.available())
  {
    float peakValue2 = peak2.read();
    // Uncomment this line for IN2 calibration
//    Serial.println(peakValue2, 4);
  }

  delay(2);
}


