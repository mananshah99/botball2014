// Created on Fri February 14 2014

#include ".\drive.h"
#include "generic.h"
#include ".\slowservo.h"

int main()
{
	light_start()
	forward(50.00);
	left(90,0);
	forward(20.00);
	right(90,0);
	//move arm up
	//move forward so hangers are directly above the scoring pipe
	//move arm down
	//collect bottom blue multiplier hangers
	//go back a little
	//do same thing as the regular hangers
	printf("finished");
	return 0;
}
