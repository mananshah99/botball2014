// Created on Fri February 14 2014

#include ".\drive.h"
#include ".\generic.h"
#include ".\slowservo.h"

#define ARM 3//arm port
// change "ks" in library
int main()
{
	light_start();
	forward(50.00);
	left(90,0);
	forward(20.00);
	right(90,0);
	motor(ARM,50);//move arm up
	forward(2.5);//move forward so hangers are directly above the scoring pipe
	motor(ARM,-30);//move arm down to drop hangers
	left(30,ks/2);
	right(40,ks/2);//turn to drop hangers down
	left(10,ks/2);//turn back to be straight against scoring area
	backward(2.5);//back up
	motor(ARM,-20);//collect bottom blue multiplier hangers
	//go back a little
	//do same thing as the regular hangers to place blue on top
	printf("finished");
	return 0;
}
