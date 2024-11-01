#ifndef _MIDI_H
#define _MIDI_H

#include <USB.h>
#include <ESPNATIVEUSBMIDI.h>
#include <MIDI.h>

void initilaizeMIDI();
void MIDInoteSent(int note, int velocity, int channel);

#endif
