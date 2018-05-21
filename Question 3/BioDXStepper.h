// BioDXStepper.h

#ifndef _BIODXSTEPPER_h
#define _BIODXSTEPPER_h

#include "AccelStepper_L.h"
#include "arduino.h"
#include "main_HAL.h"


class BioDXStepperClass : public AccelStepper
{
 protected:
	 uint8_t _uchPulsePin;
	 uint8_t _uchDirPin;
	 uint8_t _uchHallEffectSensorPin;
	 uint8_t _uchStepperMode;
	 boolean _uchTargetReached = false;
	// boolean _uchHomingReady = false;
	 boolean _uchGoToQuadrant = false;
	 uint8_t _uchQuadrantTarget;
	 uint8_t _uchPreviousQuadrant = FIRST;
	 boolean _bFourInOne = false;
	 AccelStepper *_pStp;

 public:
	BioDXStepperClass(uint8_t uchpulsePin, uint8_t uchdirPin, uint8_t uchHallEffectPin);

	void init();
	uint8_t manager();
	void startContinuousCycle();
	void goToQuadrant(uint8_t uchQuadrant, boolean bContinuous);
	void stopMotor();
	void homing();

};

//extern BioDXStepperClass BioDXStepper;

#endif

