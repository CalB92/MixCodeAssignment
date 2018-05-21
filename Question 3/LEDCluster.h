// LEDCluster.h

#ifndef _LEDCLUSTER_h
#define _LEDCLUSTER_h

#include "arduino.h"
#include "main_HAL.h"

#define LED_DELAY_SETTING		50

struct LDRReading
{
	uint16_t set1;
	uint16_t set2;
	uint16_t set3;
};

class LEDClusterClass
{

protected:
	uint8_t _uchLEDPinSet1;
	uint8_t _uchLEDPinSet2;
	uint8_t _uchLEDPinSet3;
	uint8_t _uchLDRpin;
	LDRReading LDRreadings; //Store the LDR readings of each LED set

	uint8_t _uchLEDSetState = READING_SET1;
	uint8_t _uchClusterState;
	uint8_t _uchLEDClusterCountdown;

public:
	LEDClusterClass(uint8_t uchLEDPin_Set1, uint8_t uchLEDPin_Set2, uint8_t uchLEDPin_Set3, uint8_t uchLDR_ADC_Pin);
	void init();
	//Turn a specific LED set on or off
	void setLEDs(uint8_t uchLEDSet_Pin, boolean bState);

	//Manages the LDR reading process. A 1 is returned when a set of readings is complete.
	uint8_t manager();
	//Starts the LDR reading process
	void readLDR();
	//Returns the readings for the three sets of LEDs as a struct
	LDRReading getCurrentLDRReadings();

};

#endif

