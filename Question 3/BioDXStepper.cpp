// 
// 
// 

#include "BioDXStepper.h"

BioDXStepperClass::BioDXStepperClass(uint8_t uchpulsePin, uint8_t uchdirPin, uint8_t uchHallEffectPin)
{
	_uchPulsePin = uchpulsePin;
	_uchDirPin = uchdirPin;
	_uchHallEffectSensorPin = uchHallEffectPin;

	_pStp = new AccelStepper(AccelStepper::DRIVER, _uchPulsePin, _uchDirPin);
}

void BioDXStepperClass::init()
{
	_pStp->setEnablePin(STEPPER_ENABLE_PIN);
	_pStp->setPinsInverted(false, false, true);
	_pStp->disableOutputs();
	_pStp->setMaxSpeed(6400);
	_pStp->setAcceleration(20000);
	_pStp->stop();
	_pStp->enableOutputs();

	pinMode(HALLEFFECT_SENSOR, INPUT);
}

//Returns 1 when the stepper motor has stopped at the quadrant
uint8_t BioDXStepperClass::manager()
{

	switch (_uchStepperMode)
	{
		case IDLE:
		{
			break;
		}

		case CONTINUOUS_ROTATION:
		{
			//Serial.println("Continuous Rotation \r\n");

			if (!_uchTargetReached)
			{
				//Serial.println("Running \r\n");
				_uchTargetReached = _pStp->run();
			}
			else
			{
				_pStp->moveTo(6400);
				_pStp->setSpeed(1600);
				_uchTargetReached = false;
			}

			break;
		}

		case HOMING:
		{
			//Serial.println("Busy Homing1 \r\n");
			if (digitalRead(_uchHallEffectSensorPin) && ((_uchQuadrantTarget == FIRST)||(_bFourInOne == false)))
			{
				//Serial.println("Busy Homing2 \r\n");
				_pStp->runSpeed();
			}
			else
			{
				//Homing is done
				//Serial.println("Set quadrant target \r\n");
				if ((_bFourInOne==false) || (_uchQuadrantTarget==FIRST))
				{
					_pStp->setCurrentPosition(0);
				}
				
				_pStp->stop();
				//_uchTargetReached = 0;
				_uchStepperMode = SET_QUADRANT_TARGET;
				//_uchHomingReady = true;
			}

			break;
		}

		case SET_QUADRANT_TARGET:
		{
			if (_uchGoToQuadrant)
			{
				if (_uchQuadrantTarget == FIRST)
				{
					_pStp->moveTo(0);
					_pStp->setSpeed(3200);
				}
				else if (_uchQuadrantTarget == SECOND)
				{
					//Serial.println("Second Quadrant \r\n");
					_pStp->moveTo(1600);
					_pStp->setSpeed(3200);
				}
				else if (_uchQuadrantTarget == THIRD)
				{
					_pStp->moveTo(3200);
					_pStp->setSpeed(3200);
				}
				else if (_uchQuadrantTarget == FOURTH)
				{
					_pStp->moveTo(4800);
					_pStp->setSpeed(3200);
				}

				//Serial.println("Target Quadrant set \r");

				int targetPosition = _pStp->targetPosition();
				Serial.println(targetPosition);
				Serial.println(_pStp->distanceToGo());

				_uchStepperMode = GO_TO_QUADRANT;


			}
			else
			{
				_uchStepperMode = IDLE;
			}
			break;
		}

		case GO_TO_QUADRANT:
		{
			if (_pStp->distanceToGo() != 0)
			{
				_pStp->run();
				//_pStp->runToPosition();
			}
			else
			{
				Serial.println("At Target \r");
				Serial.println(_pStp->distanceToGo());
				delay(500);
				stopMotor();
				_uchStepperMode = IDLE;
				_uchPreviousQuadrant = _uchQuadrantTarget;
				_uchGoToQuadrant = false;
				return 1;
			}
		}
	}
	return 0;
}

void BioDXStepperClass::startContinuousCycle()
{
	//Set the motor target
	_pStp->enableOutputs();
	_pStp->moveTo(6400);
	_pStp->setSpeed(1600);
	_uchStepperMode = CONTINUOUS_ROTATION;
}

void BioDXStepperClass::stopMotor()
{
	_pStp->stop();
	digitalWrite(STEPPER_ENABLE_PIN, HIGH);
	_uchStepperMode = IDLE;
}

void BioDXStepperClass::goToQuadrant(uint8_t uchQuadrant, boolean bContinuous)
{
	//_pStp->enableOutputs();
	homing();
	_uchGoToQuadrant = true;
	_uchQuadrantTarget = uchQuadrant;
	_bFourInOne = bContinuous;
}

void BioDXStepperClass::homing()
{
	_pStp->enableOutputs();
	_pStp->moveTo(6400);
	_pStp->setSpeed(6400);
	//Serial.println("Start Homing \r\n");
	_uchStepperMode = HOMING;
}