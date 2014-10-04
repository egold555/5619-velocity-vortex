#pragma config(Sensor, S1,     ,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../Libraries/I2C.h"
#include "JoystickDriver.c"

const int Deadband = 10;
const int MiddleSpeed = 100;

void HandleSides()
{
	if (abs(joystick.joy1_y2) > Deadband)
	{
		int Speed = joystick.joy1_y2;
		if (joystick.joy1_y2 < -100) {
			Speed = -100;
		}
		
		if (joystick.joy1_y2 > 100) {
			Speed = 100;
		}
		
		I2C_SetMotorSpeed(S1, 1, 2, -Speed);
		
	} else {
		I2C_SetMotorSpeed(S1, 1, 2, 0);
	}

	if (abs(joystick.joy1_y1) > Deadband)
	{
		int Speed;
		if (joystick.joy1_y1 < -100) {
			Speed = -100;
		}
		
		if (joystick.joy1_y1 > 100) {
			Speed = 100;
		}

		I2C_SetMotorSpeed(S1, 1, 1, Speed);
	} else {
		I2C_SetMotorSpeed(S1, 1, 1, 0);
	}
}

void HandleMiddle()
{
	if (joy1Btn(8))
	{
		I2C_SetMotorSpeed(S1, 2, 2, -MiddleSpeed);
	}
	else if (joy1Btn(7))
	{
		I2C_SetMotorSpeed(S1, 2, 2, MiddleSpeed);
	}
	else
	{
		I2C_SetMotorSpeed(S1, 2, 2, 0);
	}
}

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);

		HandleSides();
		HandleMiddle();

		Sleep(10);
	}
}
