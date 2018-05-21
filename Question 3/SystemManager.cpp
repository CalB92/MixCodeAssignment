// 
// 
// 

#include "SystemManager.h"

SystemManagerClass::SystemManagerClass()
{

	_pLEDCluster = new LEDClusterClass(LED_SET1, LED_SET2, LED_SET3, LDR_SENSOR);
	_pStepper = new BioDXStepperClass(STEPPER_PULSE_PIN, STEPPER_DIR_PIN, HALLEFFECT_SENSOR);
	//_pOW = new OneWire(ONE_WIRE_BUS);
	//_pSensor = new DallasTemperature(_pOW);
	
}

void SystemManagerClass::init()
{
	Serial.begin(9600);
	//_pSensor->begin();
	_pLEDCluster->init();
	_pStepper->init();
	delay(1000);
	readLDRSensor();
	//_pStepper->startContinuousCycle();
	//_pStepper->goToQuadrant(THIRD);

	readWaterTemperature();
	Serial.println(_uchWaterTempC);
}

void SystemManagerClass::manager()
{
	static uint32_t _ulTime_10ms = 0;
	static uint32_t _ulTime_5000ms = 0;

	switch (_uchProcessState)
	{
		case IDLE:
		{
			if (_uchLastProcessState != IDLE)
			{
				//_pStepper->startContinuousCycle();
				_uchLastProcessState = IDLE;
			}
			break;
		}

		case GO_TO_QUADRANT:
		{
			//Go to the quadrant 
			if (_uchLastProcessState != GO_TO_QUADRANT)
			{
				_pStepper->goToQuadrant(_uchNextQuadrant, true);
				_uchLastProcessState = GO_TO_QUADRANT;
			}
			
			//If the motor has stopped at the quadrant, proceed with LDR reading
			if (_uchQuadrantReady)
			{
				_uchProcessState = COMMENCE_LDR_READING;
				_uchQuadrantReady = false;
			}
			break;
		}

		case COMMENCE_LDR_READING:
		{
			//Start the LDR reading
			if (_uchLastProcessState != COMMENCE_LDR_READING)
			{
				_pLEDCluster->readLDR();
				_uchLastProcessState = COMMENCE_LDR_READING;
			}

			if (_uchClusterReadingEnd)
			{
				_uchProcessState = GO_TO_QUADRANT;

				if (_uchNextQuadrant == FIRST)
				{
					_uchNextQuadrant = SECOND;
					Quadrant1Reading = _pLEDCluster->getCurrentLDRReadings();
				}
				else if (_uchNextQuadrant == SECOND)
				{
					_uchNextQuadrant = THIRD;
					Quadrant2Reading = _pLEDCluster->getCurrentLDRReadings();
				}
				else if (_uchNextQuadrant == THIRD)
				{
					_uchNextQuadrant = FOURTH;
					Quadrant3Reading = _pLEDCluster->getCurrentLDRReadings();
				}
				else if (_uchNextQuadrant == FOURTH)
				{
					//_uchNextQuadrant = FIRST;
					Quadrant4Reading = _pLEDCluster->getCurrentLDRReadings();
					Serial.println("");
					Serial.println(Quadrant1Reading.set1);
					Serial.println(Quadrant1Reading.set2);
					Serial.println(Quadrant1Reading.set3);
					Serial.println("");
					Serial.println(Quadrant2Reading.set1);
					Serial.println(Quadrant2Reading.set2);
					Serial.println(Quadrant2Reading.set3);
					Serial.println("");
					Serial.println(Quadrant3Reading.set1);
					Serial.println(Quadrant3Reading.set2);
					Serial.println(Quadrant3Reading.set3);
					Serial.println("");
					Serial.println(Quadrant4Reading.set1);
					Serial.println(Quadrant4Reading.set2);
					Serial.println(Quadrant4Reading.set3);
			
					_uchProcessState = IDLE;
				}
			}
			break;
		}
	}

	if ((millis() - _ulTime_10ms) > TIME_10_MS)
	{
		_ulTime_10ms = millis();

		if (_pLEDCluster->manager())
		{
			_uchClusterReadingEnd = true;
			_uchQuadrantReady = false;
		}
	}

	if (_pStepper->manager())
	{
		_uchQuadrantReady = true;
		_uchClusterReadingEnd = false;

	}
	
}

void SystemManagerClass::readLDRSensor()
{
	_uchNextQuadrant = FIRST;
	_uchProcessState = GO_TO_QUADRANT;
}

void SystemManagerClass::readWaterTemperature()
{
	//_pSensor->requestTemperatures(); // Send the command to get temperature readings
	//_uchWaterTempC = _pSensor->getTempCByIndex(0);
}

uint16_t SystemManagerClass::getTempValue()
{
	return _uchWaterTempC;
}
