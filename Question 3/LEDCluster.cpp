// 
// 
// 

#include "LEDCluster.h"

LEDClusterClass::LEDClusterClass(uint8_t uchLEDPin_Set1, uint8_t uchLEDPin_Set2, uint8_t uchLEDPin_Set3, uint8_t uchLDR_ADC_Pin)
{
	_uchLEDPinSet1 = uchLEDPin_Set1;
	_uchLEDPinSet2 = uchLEDPin_Set2;
	_uchLEDPinSet3 = uchLEDPin_Set3;
	_uchLDRpin = uchLDR_ADC_Pin;

}

void LEDClusterClass::init()
{

	//Initialize the LED set pins
	pinMode(_uchLEDPinSet1, OUTPUT);
	pinMode(_uchLEDPinSet2, OUTPUT);
	pinMode(_uchLEDPinSet3, OUTPUT);
	//pinMode(uchLDR_ADC_Pin, INPUT);

	_uchClusterState = IDLE;
}

void LEDClusterClass::setLEDs(uint8_t uchLEDSet_Pin, boolean bState)
{
	digitalWrite(uchLEDSet_Pin, bState); //Change the state of the LED set
}

//Returns a 1 if the LDR reading has completed

uint8_t LEDClusterClass::manager()
{
	switch (_uchClusterState)
	{
		case IDLE: //Turn LEDs on
		{

			break;
		}
		case SET_LEDS: //Turn LEDs on
		{
			Serial.println("Light reading started \r\n");
			if (_uchLEDSetState == READING_SET1)
			{
				setLEDs(_uchLEDPinSet1, ON);
			}
			else if (_uchLEDSetState == READING_SET2)
			{
				setLEDs(_uchLEDPinSet2, ON);
			}
			else if (_uchLEDSetState == READING_SET3)
			{
				setLEDs(_uchLEDPinSet3, ON);
			}
			else if (_uchLEDSetState == READING_SET_ALL)
			{
				setLEDs(_uchLEDPinSet1, ON);
				setLEDs(_uchLEDPinSet2, ON);
				setLEDs(_uchLEDPinSet3, ON);
			}
			_uchLEDClusterCountdown = LED_DELAY_SETTING;
			_uchClusterState = TAKE_READING;
			break;
		}
		case TAKE_READING: //Homing
		{

			if (_uchLEDClusterCountdown == 0)
			{
				if (_uchLEDSetState == READING_SET1)
				{
					LDRreadings.set1 = analogRead(_uchLDRpin); //The value of the LDR sensor is stored
					_uchClusterState = SET_LEDS;
					setLEDs(_uchLEDPinSet1, OFF);
					_uchLEDSetState = READING_SET2;
					Serial.println("LDR Reading for SET 1 Done \r");
					Serial.println(LDRreadings.set1);
				}
				else if (_uchLEDSetState == READING_SET2)
				{
					LDRreadings.set2 = analogRead(_uchLDRpin); //The value of the LDR sensor is stored
					_uchClusterState = SET_LEDS;
					setLEDs(_uchLEDPinSet2, OFF);
					_uchLEDSetState = READING_SET3;
					Serial.println("LDR Reading for SET 2 Done \r");
					Serial.println(LDRreadings.set2);
				}
				else if (_uchLEDSetState == READING_SET3)
				{
					LDRreadings.set3 = analogRead(_uchLDRpin); //The value of the LDR sensor is stored
					_uchClusterState = IDLE;
					setLEDs(_uchLEDPinSet3, OFF);
					_uchLEDSetState = READING_SET1;
					Serial.println("LDR Reading for SET 3 Done \r");
					Serial.println(LDRreadings.set3);
					return 1;
				}
				else if (_uchLEDSetState == READING_SET_ALL)
				{
					LDRreadings.set1 = analogRead(_uchLDRpin); //The value of the LDR sensor is stored
					_uchClusterState = IDLE;
					setLEDs(_uchLEDPinSet1, OFF);
					setLEDs(_uchLEDPinSet2, OFF);
					setLEDs(_uchLEDPinSet3, OFF);
					_uchLEDSetState = READING_SET1;
					Serial.println("LDR Reading Done \r");
					Serial.println(LDRreadings.set1);
					return 1;
				}
				
			}
			else
			{
				_uchLEDClusterCountdown--;
				Serial.println(_uchLEDClusterCountdown);
			}

			break;
		}
	}
	return 0;
}

void LEDClusterClass::readLDR()
{
	_uchClusterState = SET_LEDS;

}

LDRReading LEDClusterClass::getCurrentLDRReadings()
{
	return LDRreadings;
}