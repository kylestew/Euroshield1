#include <MIDI.h>

// 1010MIDINoteDouble - target: the 1010music Euroshield with the PJRC Teensy 3.2
//
// This sketch demonstrates MIDI receive and send functionality. The code routes
// note messages from the MIDI In port to the MIDI Out port and adds a second
// note 7 semitones higher.
//
// This code is in the public domain.

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

#define ledPinCount 4
int ledPins[ledPinCount] = { 3, 4, 5, 6 };
int ledPos = 0;


void doSomeStuffWithNoteOn(byte channel, byte pitch, byte velocity)
{
  MIDI.sendNoteOn(pitch, velocity, channel);
  MIDI.sendNoteOn(pitch + 7, velocity, channel);
}

void doSomeStuffWithNoteOff(byte channel, byte pitch, byte velocity)
{
  MIDI.sendNoteOff(pitch, velocity, channel);
  MIDI.sendNoteOff(pitch + 7, velocity, channel);
}

void setup()
{
  for (int i = 0; i < ledPinCount; i++)
    pinMode(ledPins[i], OUTPUT);
  MIDI.begin();                      // Launch MIDI and listen
  MIDI.setHandleNoteOn(doSomeStuffWithNoteOn);
  MIDI.setHandleNoteOff(doSomeStuffWithNoteOff);
  MIDI.turnThruOff();
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
    }
}
