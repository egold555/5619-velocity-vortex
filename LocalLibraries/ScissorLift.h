#include "../Libraries/Motors.h"

/* TODO: limit switches */

void ScissorLift_MoveUp(int speed)
{
	Motors_SetSpeed(S1, 3, 1, speed);
	Motors_SetSpeed(S1, 3, 2, -speed);
}

void ScissorLift_MoveDown(int speed)
{
	Motors_SetSpeed(S1, 3, 1, -speed);
	Motors_SetSpeed(S1, 3, 2, speed);
}