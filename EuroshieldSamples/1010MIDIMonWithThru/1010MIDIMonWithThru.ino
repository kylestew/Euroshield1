#include <MIDI.h>

// 1010MIDIMonWithThru - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates MIDI setup with automatic thruing. The LEDs will blink
// each time a message is received.
//
// This code is in the public domain.

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

#define ledPinCount 4
int ledPins[ledPinCount] = { 3, 4, 5, 6 };
int ledPos = 0;

void setup()
{
  for (int i = 0; i < ledPinCount; i++)
    pinMode(ledPins[i], OUTPUT);
  MIDI.begin();
}

void advanceLED()
{
  digitalWrite(ledPins[ledPos % ledPinCount], LOW);
  ledPos++;  
  digitalWrite(ledPins[ledPos % ledPinCount], HIGH);
}

void loop()
{
    if (MIDI.read())                    // If we have received a message
    {
        advanceLED();
        // MIDI Thru happens automatically with the library
    }
}
