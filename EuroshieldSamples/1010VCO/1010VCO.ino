#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// 1010VCO - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates a dual Voltage Controlled Oscillator:
// IN1 controls the pitch of the sinewave on OUT1 using 1V/Octave
// IN2 controls the pitch of the sawtooth wave on OUT2 using 1V/Octave
//
// For more accurate control of the pitch on your device, refer to the
// 1010VCOCalibration sample
//
// This code is in the public domain.


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=195,187
AudioAnalyzePeak         peak1;          //xy=367,171
AudioAnalyzePeak         peak2;          //xy=367,206
AudioSynthWaveform       waveform1;      //xy=557,164
AudioSynthWaveform       waveform2;      //xy=559,205
AudioOutputI2S           i2s2;           //xy=795,174
AudioConnection          patchCord1(i2s1, 0, peak1, 0);
AudioConnection          patchCord2(i2s1, 1, peak2, 0);
AudioConnection          patchCord3(waveform1, 0, i2s2, 0);
AudioConnection          patchCord4(waveform2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=246,330
// GUItool: end automatically generated code

// Use the 1010VCOCalibration sketch to learn how these values were measured
#define kPeakValue1V_IN1   0.2088
#define kPeakValue4V_IN1   0.7627
#define kPeakValue1V_IN2   0.2092
#define kPeakValue4V_IN2   0.7649
#define kC1VFrequency      32.703 

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

  waveform1.frequency(1000);
  waveform1.amplitude(0.5);
  waveform1.begin(WAVEFORM_SINE);
  
  waveform2.frequency(1000);
  waveform2.amplitude(0.5);
  waveform2.begin(WAVEFORM_SAWTOOTH);
}

float calcFreqFromCV(float cvValue)
{
  return pow(2, cvValue) * kC1VFrequency;
}

float calcFreqFromPeakValueIN1(float peakValue)
{
  float peakPerOctave = (kPeakValue4V_IN1 - kPeakValue1V_IN1) / 3;
  float cvValue = (peakValue - kPeakValue1V_IN1) / peakPerOctave;
  return calcFreqFromCV(cvValue);
}

float calcFreqFromPeakValueIN2(float peakValue)
{
  float peakPerOctave = (kPeakValue4V_IN2 - kPeakValue1V_IN2) / 3;
  float cvValue = (peakValue - kPeakValue1V_IN2) / peakPerOctave;
  return calcFreqFromCV(cvValue);
}

void loop()
{
  if (peak1.available())
  {
    float peakValue1 = peak1.read();
    waveform1.frequency(calcFreqFromPeakValueIN1(peakValue1));
  }

  if (peak2.available())
  {
    float peakValue2 = peak2.read();
    waveform2.frequency(calcFreqFromPeakValueIN2(peakValue2));
  }

  delay(2);
}


