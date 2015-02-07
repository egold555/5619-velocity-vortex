#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Sensor, S3,     HTPB,           sensorI2CCustom9V)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//autonomous.c

/*

	(C) Copyright 2014, 2015 Alex Jordan, Aidan Wood

	This file is part of the FTC team 5619 application code.

	FTC team 5619 application code is free software: you can
	redistribute it and/or modify it under the terms of the GNU
	General Public License as published by the Free Software
	Foundation, either version 2 of the License, or (at your
	option) any later version.

	FTC team 5619 application code is distributed in the hope that
	it will be useful, but WITHOUT ANY WARRANTY; without even the
	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE.  See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with FTC team 5619 application code. If not, see
	<http://www.gnu.org/licenses/>.

*/

/*

	DOCUMENTATION:

	You may find an overview of how this code works in doc/autonomous.md.

*/

#include "JoystickDriver.c"
#include "IRLineFollower.c"
#include "../teleop/5619Drive.h"

const tSensors IRport = S3;

task main()
{

	typedef enum { ONRAMP, MOVEFROMRAMP, MOVEFROMPARKINGZONE, LINEFOLLOWING, DISPENSING, KICKSTAND, STOPPED } AutoState;
	AutoState State = ONRAMP;

	clearDebugStream();
	Drive_scissorLiftInit();
	//waitForStart();

	while(true)
	{
		// state machine loop

		switch(State)
		{
			case ONRAMP:
				MoveDownRampAndGetTube(sonarSensor);
				State = MOVEFROMRAMP;
				break;
			case MOVEFROMRAMP:
				MoveTubesToParkingZone();
				State = STOPPED;
				break;
			case MOVEFROMPARKINGZONE:
				int position = 2;// GetIRFieldPosition(GetIRPosition(IRport));
				writeDebugStreamLine("Center field position guess: %i", position);
				MoveToIRPosition(position);
				State = STOPPED;
				break;
			case LINEFOLLOWING:
				writeDebugStreamLine("Running loop: LINEFOLLOWING");
				bool readyToChange = IRLineFollow(IRport);
				if (readyToChange) {
					State = DISPENSING;
				}
				break;
			case DISPENSING:
				//writeDebugStreamLine("Running loop: DISPENSING");
				break;
			case KICKSTAND:
				MoveToKickstand();
				State = STOPPED;
				break;
			case STOPPED:
				Drive_allStop();
				Sleep(10);
				break;
			default:
				writeDebugStreamLine("FATAL ERROR ENCOUNTERED");
				writeDebugStreamLine("The state machine has encountered an unknown state. Something is SERIOUSLY wrong!");
				writeDebugStreamLine("Aborting program.");
				// TODO: stop all motors
				StopAllTasks();
				break;
		}
	}

}
