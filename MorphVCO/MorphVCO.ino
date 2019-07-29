#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>


#include "faustCore.h"
faustCore               core;

AudioInputI2S           in;
AudioOutputI2S          out;

AudioAnalyzePeak        vOctCV;
AudioAnalyzePeak        shapeCV;

AudioConnection         patchCord0(in, 0, vOctCV, 0);
AudioConnection         patchCord1(in, 1, shapeCV, 0);

AudioConnection         patchCord2(core, 0, out, 0);
//AudioConnection         patchCord2(faust, 1, out, 1);

AudioControlSGTL5000    codec;

const int FREQ_POT = 20;
const int SHAPE_POT = 21;

const int OCTAVE_BUTTON = 2;
Bounce octaveButton = Bounce(OCTAVE_BUTTON, 10);  // 10 ms debounce

const int LED0_PIN = 3; // LEDs on pins 3, 4, 5, and 6

/*
 * CALIBRATION DATA
 * Use the 1010VCOCalibration sketch to update
 */
#define kPeakValue1V_IN1   0.223
#define kPeakValue4V_IN1   0.7758
#define kPeakValue1V_IN2   0.218
#define kPeakValue4V_IN2   0.771
#define kC1VFrequency      32.703

int octaveShift = 1;
int centsOffset = 0;

void setup() {
    Serial.begin(9600);

    AudioMemory(10);

    pinMode(OCTAVE_BUTTON, INPUT_PULLUP);
    pinMode(LED0_PIN, OUTPUT);
    pinMode(LED0_PIN+1, OUTPUT);
    pinMode(LED0_PIN+2, OUTPUT);
    pinMode(LED0_PIN+3, OUTPUT);

    codec.enable();
    codec.inputSelect(AUDIO_INPUT_LINEIN);
    codec.volume(0.82);
    codec.adcHighPassFilterDisable();
    codec.lineInLevel(0,0);
    codec.unmuteHeadphone();

    updateOctaveState();
}

float calcFreqFromCV(float cvValue) {
    return pow(2, cvValue + octaveShift + (centsOffset / (12.0 * 100))) * kC1VFrequency;
}

float calcFreqFromPeakValueIN1(float peakValue) {
    float peakPerOctave = (kPeakValue4V_IN1 - kPeakValue1V_IN1) / 3;
    float cvValue = (peakValue - kPeakValue1V_IN1) / peakPerOctave;
    return calcFreqFromCV(cvValue);
}

//float calcFreqFromPeakValueIN2(float peakValue) {
//    float peakPerOctave = (kPeakValue4V_IN2 - kPeakValue1V_IN2) / 3;
//    float cvValue = (peakValue - kPeakValue1V_IN2) / peakPerOctave;
//    return calcFreqFromCV(cvValue);
//}

void updateOctaveState() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LED0_PIN + i, octaveShift == i ? HIGH : LOW);
    }
}

void loop() {
    // button sets octave shift (4 settings)
    if (octaveButton.update()) {
        if (octaveButton.fallingEdge()) {
            octaveShift++;
            if (octaveShift >= 4) octaveShift = 0;
            updateOctaveState();
        }
    }

    // Hold Length
    int freqPot  = analogRead(FREQ_POT);
    centsOffset = map(freqPot, 0, 1024, 0, 200) - 100; // [-100, 100] cents fine tuning

    // input 1 -> V/OCT
    if (vOctCV.available()) {
        float peak = vOctCV.read();
        float freq = calcFreqFromPeakValueIN1(peak);
        core.setParamValue("freq", freq);
    }

    /*
    if (shapeCV.available()) {
        float peakValue2 = shapeCV.read();
        Serial.println(peakValue2);
//        waveform2.frequency(calcFreqFromPeakValueIN2(peakValue2));
    }
     */

//    delay(2);
    delay(12);
}



