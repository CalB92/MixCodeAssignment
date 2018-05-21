#include "SystemManager.h"
#include "BioDXStepper.h"
#include "main_HAL.h"
#include "Arduino.h"
#include "LEDCluster.h"
//#include "OneWire.h"
//#include "DallasTemperature.h"

//#define ONE_WIRE_BUS 5 

//OneWire oneWire(ONE_WIRE_BUS);

//DallasTemperature sensors(&oneWire);
//#include "AccelStepper_L.h"

//LEDClusterClass LEDCluster1 = LEDClusterClass(LED_SET1, LED_SET2, LED_SET3, LDR_SENSOR);
//BioDXStepperClass stepper = BioDXStepperClass(STEPPER_PULSE_PIN, STEPPER_DIR_PIN, HALLEFFECT_SENSOR);
SystemManagerClass BIoDXSystem;

boolean toggle = false;

void setup()
{
	//sensors.begin();
	BIoDXSystem.init();
}

void loop()
{
	BIoDXSystem.manager();

	//Serial.print(" Requesting temperatures...");
	//sensors.requestTemperatures(); // Send the command to get temperature readings 
	//Serial.println("DONE");
	/********************************************************************/
	//Serial.print("Temperature is: ");
	//Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
											  // You can have more than one DS18B20 on the same bus.  
											  // 0 refers to the first IC on the wire 
}
