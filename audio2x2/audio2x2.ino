#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=401,315
AudioOutputI2S           i2s1;           //xy=747,327
AudioConnection          patchCord1(usb1, 0, i2s1, 0);
AudioConnection          patchCord2(usb1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=733,619
// GUItool: end automatically generated code


void setup() {
    AudioMemory(10);

    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);

}

void loop() {
  // put your main code here, to run repeatedly:

}
