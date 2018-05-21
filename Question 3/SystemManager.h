// SystemManager.h

#ifndef _SYSTEMMANAGER_h
#define _SYSTEMMANAGER_h

#include "BioDXStepper.h"
#include "LEDCluster.h"
#include "main_HAL.h"
#include "Arduino.h"

class SystemManagerClass
{
 protected:
	//DallasTemperature *_pSensor;
	//OneWire *_pOW;
	uint8_t	_uchNextQuadrant = FIRST;
	boolean _uchQuadrantReady = false;
	uint8_t _uchLastProcessState = IDLE;
	uint8_t _uchProcessState;
	boolean _uchClusterReadingEnd = false;

	LDRReading Quadrant1Reading;
	LDRReading Quadrant2Reading;
	LDRReading Quadrant3Reading;
	LDRReading Quadrant4Reading;
	uint16_t _uchWaterTempC;
	LEDClusterClass *_pLEDCluster;
	BioDXStepperClass *_pStepper;

 public:
	SystemManagerClass();

	void init();
	void manager();
	void readLDRSensor();
	void readWaterTemperature();
	uint16_t getTempValue();
	
};


#endif

