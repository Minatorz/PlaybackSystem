#include "_midi.h"

ESPNATIVEUSBMIDI usbmidi;
MIDI_CREATE_INSTANCE(ESPNATIVEUSBMIDI,usbmidi,MIDI)

void initilaizeMIDI() {
  // Initialize USB
  USB.productName("AbletonThesis");
  if(!USB.begin()) {
    Serial.println("USB didn't Initialize");
  }
  Serial.println("USB successfully Init!");
  // Initialize MIDI Protocol 
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Initialize MIDIUSB port
  usbmidi.begin();
  Serial.println("MIDI port Initialized!");
}

void MIDInoteSent(int note, int velocity, int channel) {
    MIDI.sendNoteOn(note, velocity, channel);
    MIDI.sendNoteOff(note, velocity, channel); 
}