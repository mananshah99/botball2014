/*
* Main program for LINK driving
* 
* Need to fix 
* 	1. the arm needs distance in order to function
*
*/

#include "./drive.h"			// driving library
#include "./generic.h"			// generic functionality
#include "./slowservo.h"		//

#define MAIN
//#define DPTEST

#define ARM 0					// arm port
#define LS 0					// light sensor port
#define HANGER-HOLDER 3			// mini-servo for holding hangers in's port

// TODO: change ks and motor ports in library

/*******ARM SERVO IMPORTANT VALUES****
*
*	Position		Value
*	----------------------
*	Top				400		
*	Middle			1000
*	Bottom			1800
*
* servo_slow(int port, int end, float time) 
* 
*************************************/

/***
	Hanger holder miniservo position values
Position	Value
Left close	Unknown
Right close	unknown
***/
#define TOP 285
#define DROP 480
#define MID 1116
#define BOT 1655

//Define MAIN to run the primary program 
#ifdef MAIN
int main()
{
	//light_start(LS);			// light start
	enable_servos();
	printf("here\n");
	set_servo_position(ARM,BOT);
	forward(40.00);				// forward for 40 cm	
	left(220,ks/2);				// left 90 degrees (more because the function undershoots)
	forward(30.00);				// forward 30 cm
	
	/**TODO: add clearing out exercise bench and botguy before hangers**/
	
	right(220,ks/2);	// right 90 degrees
	printf("going to lift up servo\n");
	msleep(1000);
	set_servo_position(ARM, TOP);		// move arm up, not slowservo anymore (slowservo) to put the hangers into the scoring area
	msleep(1500);
	printf("done\n");
	forward(15.00);	// get over to the scoring area
	msleep(100);	// stop to stop the arm shaking
	forward(15.00);
	set_servo_position(ARM, DROP);	// move arm down to drop hangers on ledge
	
	//wiggle to drop off the hangers
	
	left(40,ks/2);				// left 30 degrees
	right(60,ks/2);				// right 50 degrees
	left(20,ks/2);				// deposit hangers and push them to the sides, left 20 degrees back
	backward(5.00);				// back up 5 cm, going to get blue hangers next
	
	/**TODO: FIX WITH SLOWSERVO**/
	
	int i;			
	for(i=0; i<2; i++) {			// moves each blue hanger up 
		set_servo_position(ARM, TOP);	// move to the top 
		forward(5.00);				// get arm down to the blue hangers
		set_servo_position(ARM,TOP+20);				// 
		forward(5.00);				// check if breaks something
		set_servo_position(ARM,DROP);
		backward(10.00);	
		set_servo_position(ARM,MID);
		forward(10.00);
		set_servo_position(ARM,MID+10);
		backward(7.00);
		forward(2.00);
		set_servo_position(ARM,MID);
		backward(10.00);
		set_servo_position(ARM,MID+10);
		forward(7.00);			//collect one bottom blue multiplier hanger and deliver top
		backward(5.00);
	}
	
	//TODO: go back a little - do same thing as the regular hangers to place blue on top
	
	printf("finished");
	return 0;
}
#endif

#ifdef DPTEST
int main()
{
	enable_servos();
	forward(40.00);
	left(90,ks/2);
	forward(20.00);
	//add clearing out exercise bench and botguy before hangers
	right(90,ks/2);
	servo_slow(ARM,1000,10);//move arm up
	forward(20.00);//get over to the scoring area
	return 0;
}
#endif
