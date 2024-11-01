#include "_midi.h"

ESPNATIVEUSBMIDI usbmidi;
MIDI_CREATE_INSTANCE(ESPNATIVEUSBMIDI,usbmidi,MIDI)

void initilaizeMIDI() {
  // Initialize USB
  USB.productName("AbletonThesis");
  USB.begin();
  // Initialize MIDI Protocol 
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Initialize MIDIUSB port
  usbmidi.begin();
}

void MIDInoteSent(int note, int velocity, int channel) {
    MIDI.sendNoteOn(note, velocity, channel);
    MIDI.sendNoteOff(note, velocity, channel); 
}