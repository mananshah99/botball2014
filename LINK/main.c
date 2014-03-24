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
#define TOP 285
#define DROP 480
#define MID 1116
#define BOT 1800

//Define MAIN to run the primary program 
#ifdef MAIN
int main()
{
	enable_servos();
	servo_slow(ARM,BOT,5);
	//light_start(LS);			// light start
	forward(40.00);				// forward for 40 cm	
	left(110,ks/2);				// left 90 degrees (97 because the function undershoots)
	forward(20.00);				// forward 20 cm
	
	/**TODO: add clearing out exercise bench and botguy before hangers**/
	
	right(117,ks/2);					// right 90 degrees
	servo_slow(ARM, MID, 10);		// move arm up (slowservo) to put the hangers into the scoring area
	forward(20.00);					// get over to the scoring area
	servo_slow(ARM, MID-100, 20);	// move arm down to drop hangers on ledge
	
	//wiggle to drop off the hangers
	
	left(40,ks/2);				// left 30 degrees
	right(60,ks/2);				// right 50 degrees
	left(20,ks/2);				// deposit hangers and push them to the sides, left 20 degrees back
	backward(5.00);				// back up 5 cm, going to get blue hangers next
	
	/**TODO: FIX WITH SLOWSERVO**/
	
	int i;			
	for(i=0; i<2; i++) {			// moves each blue hanger up 
		servo_slow(ARM, TOP, 10);	// move to the top 
		forward(5.00);				// get arm down to the blue hangers
		servo_slow(ARM,TOP+20,10);				// 
		forward(5.00);				// check if breaks something
		servo_slow(ARM,DROP,10);
		backward(10.00);	
		servo_slow(ARM,MID,10);
		forward(10.00);
		servo_slow(ARM,MID+10,10);
		backward(7.00);
		forward(2.00);
		servo_slow(ARM,MID,10);
		backward(10.00);
		servo_slow(ARM,MID+10,10);
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
