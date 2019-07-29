#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


#include "faustPM.h"
faustPM                 faust;

AudioInputI2S           in;
AudioOutputI2S          out;

//AudioAnalyzeRMS         gateRMS;

// gate input
//AudioConnection          patchCord1(in, 0, gateRMS, 0);

// outputs
AudioConnection          patchCord3(faust, 0, out, 0);

AudioControlSGTL5000    codec;

const int POT0 = 20;
const int POT1 = 21;


void setup() {
    Serial.begin(9600);

    AudioMemory(10);

    codec.enable();
    codec.inputSelect(AUDIO_INPUT_LINEIN);
    codec.volume(0.82);
    codec.adcHighPassFilterDisable();
    codec.lineInLevel(0,0);
    codec.unmuteHeadphone();
}

bool gateOpen = false;
long int lastGate = millis();

void loop() {
    /*
    // Hold Length
    int pot0  = analogRead(POT0);
    float holdLength = map(float(pot0) / 1024, 0, 1, 1, 200);
    faust.setParamValue("holdLength", holdLength);

    // Strike Position
    int pot1  = analogRead(POT1);
    int strikePosition = (int)map(float(pot1) / 1024, 0, 1, 0, 5);
    faust.setParamValue("strikePosition", strikePosition);

    // Gate
    if (gateRMS.available()) {
        float rmsValue = gateRMS.read();

//        Serial.print(rmsValue);
//        Serial.print(" ");
//        Serial.print(gateOpen);
//        Serial.print(" ");
//        Serial.println(tap2.read());
//            delay(4);

        // trigger gate
        if (rmsValue > 0.2 && !gateOpen) {

            faust.setParamValue("gate", 1);
            delay(20);
            faust.setParamValue("gate", 0);

            gateOpen = true;

        } else if (rmsValue < 0.2 && gateOpen) {

            gateOpen = false;

        }
        // TODO: retrigger delay?
    }
     */
}
