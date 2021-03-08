#include <stdint.h>

#define bool int
#define true 1
#define false 0
#define noOfSounds 8
#define noOfScales 12
int numAnalogPins = noOfSounds;
int noOfLDRs = 8;
uint32_t thresholds[noOfSounds];
float percentThresh = 0.9;
int absoluteThresh = 100;
int noteVelocity = 63;

int reCalibrate = 50;
int loopCount = 0;

void setup();
void calibrate();
uint16_t analogRead(int pinNo);
void turnOnOffSounds(bool newSoundState[noOfSounds]);
void initMIDI(int channel);
void setBasicChannel(int channel);
void setOmniAndPoly(int channel, bool omni, bool poly);
void noteOn(int channel, uint8_t note);
void noteOff(int channel, uint8_t note);
void initialiseNotes();
int getKey();
int getMajorMinor();

volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up

bool soundState[noOfSounds] = { false, false, false, false, false, false, false, false };
int notes[noOfSounds] = { 60, 70, 80, 90, 100, 110, 120, 130 };
int midiChannel = 0;
int majorMinorHarmonicMelodic = 0;
int baseNoteForScale[noOfScales];

int defaultKey = 1;
