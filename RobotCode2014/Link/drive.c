// Created on Fri February 14 2014

#include ".\drive.h"
#include ".\generic.h"
#include ".\slowservo.h"

#define ARM 3//arm port
// change "ks" and motor ports in library

int main()
{
	light_start();
	forward(40.00);
	left(90,ks/2);
	forward(20.00);
	right(90,ks/2);//get over to the scoring area
	motor(ARM,50);//move arm up
	forward(2.5);//move forward so hangers are directly above the scoring pipe
	motor(ARM,-30);//move arm down to drop hangers
	left(30,ks/2);
	right(40,ks/2);
	left(10,ks/2);//turn back to be straight against scoring area
	backward(2.5);//back up
	motor(ARM,20);
	left(50,ks/2);
	forward(5.00);
	motor(ARM,-20);
	backward(10.00);
	motor(ARM,40);
	forward(10.00);
	motor(ARM,10);
	backward(7.00);
	forward(2.00);
	motor(ARM,-10);
	backward(10.00);
	motor(ARM,10);
	forward(7.00);//collect one bottom blue multiplier hanger and deliver to top
	
	//go back a little
	//do same thing as the regular hangers to place blue on top
	printf("finished");
	return 0;
}
