#include "SensorMidiController.h"

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

#include "MCP3008.h"

#include "USART.h"

void setup()
{
    clock_prescale_set(clock_div_1);
    initUSART();
    initMIDI(midiChannel);
//	printString("Piano stairs starting\r\n");

    initSPI();

    calibrate();

    initialiseNotes();
//	printString("Piano stairs calibrated\r\n");
}

uint16_t analogRead(int pinNo)
{
    uint16_t ret = 0;
    switch (pinNo)
    {
        case 0:
            ret = ADC_readWord(ADC_CH0_READ);
            break;
        case 1:
            ret = ADC_readWord(ADC_CH1_READ);
            break;
        case 2:
            ret = ADC_readWord(ADC_CH2_READ);
            break;
        case 3:
            ret = ADC_readWord(ADC_CH3_READ);
            break;
        case 4:
            ret = ADC_readWord(ADC_CH4_READ);
            break;
        case 5:
            ret = ADC_readWord(ADC_CH5_READ);
            break;
        case 6:
            ret = ADC_readWord(ADC_CH6_READ);
            break;
        case 7:
            ret = ADC_readWord(ADC_CH7_READ);
            break;
    }

    return ret;
}

void calibrate()
{
    int maxSteps = 100;
    for (int curStep = 0; curStep < maxSteps; curStep++)
    {
        for (int pin = 0; pin < numAnalogPins; pin++)
        {
            thresholds[pin] += analogRead(pin);
        }
    }

    for (int pin = 0; pin < numAnalogPins; pin++)
    {
        thresholds[pin] = thresholds[pin] / maxSteps;
    }
}

void turnOnOffSounds(bool newSoundState[])
{
	for (int soundNo = 0; soundNo < noOfSounds; soundNo++)
	{
		if (soundState[soundNo] != newSoundState[soundNo])
		{
			soundState[soundNo] = newSoundState[soundNo];
			if (soundState[soundNo] == false)
				noteOff(midiChannel, notes[soundNo]);
			else
				noteOn(midiChannel, notes[soundNo]);
		}
	}
}

void initMIDI(int channel)
{
    setBasicChannel(channel);
    setOmniAndPoly(channel, true, true);
}

void setBasicChannel(int channel)
{
   // May have misunderstood here. This may only be applicable to a receiver
}

void setOmniAndPoly(int channel, bool omni, bool poly)
{
	/* */
    if (omni)
    {
        transmitByte(0b10110000 | channel);
        transmitByte(125);
        transmitByte(0);

        if (poly)
        {
            // Mode 1
            transmitByte(0b10110000 | channel);
            transmitByte(127);
            transmitByte(0);
        }
        else
        {
            // Mode 2
            transmitByte(0b10110000 | channel);
            transmitByte(126);
            transmitByte(0);
        }
    }
    else
    {
        transmitByte(0b10110000 | channel);
        transmitByte(124);
        transmitByte(0);

        if (poly)
        {
            // Mode 3
            transmitByte(0b10110000 | channel);
            transmitByte(127);
            transmitByte(0);
        }
        else
        {
            // Mode 4
            transmitByte(0b10110000 | channel);
            transmitByte(126);
            transmitByte(0);
        }
    }
    /* */
}

void noteOn(int channel, uint8_t note)
{
	transmitByte(0b10010000 | channel);
	transmitByte(note);
	transmitByte(noteVelocity);
}

void noteOff(int channel, uint8_t note)
{
	transmitByte(0b10000000 | channel);
	transmitByte(note);
	transmitByte(noteVelocity);
}

int getKey()
{
	return 0;
}

int getMajorMinor()
{
	return 0;
}

void initialiseNotes()
{
	int key = getKey();
	int majorMinor = getMajorMinor();

	switch (key)
	{
		case 0:
			if (majorMinor == 0)
				notes[0] = 60; // C Major
			else
				notes[0] = 69; // A Minor
			break;
		case 1:
			if (majorMinor == 0)
				notes[0] = 62; // D Major
			else
				notes[0] = 70; // A# Minor
			break;
		case 2:
			if (majorMinor == 0)
				notes[0] = 64; // E Major
			else
				notes[0] = 71; // B Minor
			break;
		case 3:
			if (majorMinor == 0)
				notes[0] = 65; // F Major
			else
				notes[0] = 60; // C Minor
			break;
		case 4:
			if (majorMinor == 0)
				notes[0] = 67; // G Major
			else
				notes[0] = 61; // C# Minor
			break;
		case 5:
			if (majorMinor == 0)
				notes[0] = 69; // A Major
			else
				notes[0] = 62; // D Minor
			break;
		case 6:
			if (majorMinor == 0)
				notes[0] = 71; // B Major
			else
				notes[0] = 63; // D# Minor
			break;
		case 7:
			if (majorMinor == 0)
				notes[0] = 61; // C# Major
			else
				notes[0] = 64; // E Minor
			break;
		case 8:
			if (majorMinor == 0)
				notes[0] = 63; // D# Major
			else
				notes[0] = 65; // F Minor
			break;
		case 9:
			if (majorMinor == 0)
				notes[0] = 66; // F# Major
			else
				notes[0] = 66; // F# Minor
			break;
		case 10:
			if (majorMinor == 0)
				notes[0] = 68; // G# Major
			else
				notes[0] = 67; // G Minor
			break;
		case 11:
			if (majorMinor == 0)
				notes[0] = 70; // A# Major
			else
				notes[0] = 68; // G# Minor
			break;
	}

	// TODO worry about harmonic and melodic minor scales later
	for (int noteCount = 1; noteCount < noOfSounds; noteCount++)
	{
		switch (noteCount)
		{
			case 1:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				else
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				break;
			case 2:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				else
					notes[noteCount] = notes[noteCount - 1] + 1; // semitone
				break;
			case 3:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 1; // semitone
				else
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				break;
			case 4:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				else
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				break;
			case 5:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				else
					notes[noteCount] = notes[noteCount - 1] + 1; // semitone
				break;
			case 6:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				else
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				break;
			case 7:
				if (majorMinor == 0)
					notes[noteCount] = notes[noteCount - 1] + 1; // semitone
				else
					notes[noteCount] = notes[noteCount - 1] + 2; // tone
				break;
			default:
				notes[noteCount] = 60; // middle C - so we get something to hear
				break;
		}
	}
}

int main(void)
{
    setup();

    while (1)
    {
    	bool newSoundState[noOfSounds] =  { false, false, false, false, false, false, false, false };
        for (int i = 0; i < numAnalogPins; i++)
        {
            uint16_t val = analogRead(i);
            if (i < noOfLDRs)
            {
            int limit = thresholds[i] * percentThresh;
            if (val < limit)
                newSoundState[i] = true;
            }
        }

        turnOnOffSounds(newSoundState);

        _delay_ms(100);
    }
}
