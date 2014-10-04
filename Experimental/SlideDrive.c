#pragma config(Sensor, S1,     ,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../Libraries/I2C.h"
#include "JoystickDriver.c"

const int Deadband = 10;
const int MiddleSpeed = 100;
const int LockSpeed = 10;

int LeftSideLastEncoder;
int RightSideLastEncoder;
int MiddleLastEncoder;

void SetInitialEncoderPositions()
{
	LeftSideLastEncoder = I2C_GetEncoderPosition(S1, 1, 1);
	RightSideLastEncoder = I2C_GetEncoderPosition(S1, 1, 2);
	MiddleLastEncoder = I2C_GetEncoderPosition(S1, 2, 2);
}

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

		RightSideLastEncoder = I2C_GetEncoderPosition(S1, 1, 2);

	} else {
		I2C_SetEncoderPosition(S1, 1, 2, RightSideLastEncoder, LockSpeed);
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

		LeftSideLastEncoder = I2C_GetEncoderPosition(S1, 1, 1);
	} else {
		I2C_SetEncoderPosition(S1, 1, 1, LeftSideLastEncoder, LockSpeed);
	}
}

void HandleMiddle()
{
	bool MovedMiddle = true;

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
		I2C_SetEncoderPosition(S1, 2, 2, MiddleLastEncoder, LockSpeed);
		MovedMiddle = false;
	}

	if (MovedMiddle)
	{
		MiddleLastEncoder = I2C_GetEncoderPosition(S1, 2, 2);
	}
}

task main()
{
	SetInitialEncoderPositions();

	while(true)
	{
		getJoystickSettings(joystick);

		HandleSides();
		HandleMiddle();

		Sleep(10);
	}
}
