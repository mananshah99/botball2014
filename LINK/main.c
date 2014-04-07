//Created in Spring 2014
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
#define HANGER_HOLDER 3			// mini-servo for holding hangers in's port

// NOTE: RIGHT MOTOR TURN 90 DEGREES TO THE LEFT:
// mrp(MOT_RIGHT, Power, -1544)

/*******ARM SERVO IMPORTANT VALUES****
*
*	Position		Value
*	----------------------
*	Top				350		
*	Middle			1000
*	Bottom			1800
*
* servo_slow(int port, int end, float time) 
* 
*************************************/

#define TOP 350
#define DROP 480
#define MID 1116
#define BOT 1655

/***
	Hanger holder miniservo position values
Position	Value
LEFT_CLOSE	2000 //holding hangers on the left side of the arm
RIGHT_CLOSE	0 //holding hangers of the right side of the arm
***/

#define LEFT_CLOSE 2000
#define RIGHT_CLOSE 0

//Define MAIN to run the primary program 
#ifdef MAIN
int main()	//start position is with back against PVC pipe and left side one inch from left pipe surrounding starting box
{
	//light_start(LS);			// light start
	enable_servos();
	printf("here\n");
	set_servo_position(HANGER_HOLDER, RIGHT_CLOSE);
	msleep(1000);
	set_servo_position(ARM,BOT);
	msleep(500);
	forward(50.00);				// forward for 40 cm	
	left(220,ks/2);				// left 90 degrees (more because the function undershoots)
	forward(30.00);				// forward 33 cm
	
	/**TODO: add clearing out exercise bench and botguy before hangers maybe, but it does it by itself with the turning**/
	
	right(250,ks/2);	// right 90 degrees, but uses the arm to move cube,so adding more, not changed to using both wheels anymore
	msleep(1000);
	left(20,ks/2); 		//push cube away from robot
	backward(10.00);	//sometimes arm hits the bottom rack after
	/*mrp(MOT_LEFT,400,5);
	mrp(MOT_RIGHT,-400,5); //turn 90 degrees*/
	printf("going to lift up arm\n");
	msleep(1000);
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
	set_servo_position(ARM, TOP);		// move arm up, not slowservo anymore (slowservo) to put the hangers into the scoring area
	msleep(2000);
	printf("At Hangers\n");
	forward(20.00);	// get over to the scoring area
	msleep(1500);	// stop to stop the arm shaking
	set_servo_position(HANGER_HOLDER, LEFT_CLOSE);
	msleep(3000);
	forward(16.00);
	msleep(1000);
	set_servo_position(ARM, DROP);	// move arm down to drop hangers on ledge
	msleep(1000);
	motor(MOT_LEFT, -100);
	msleep(500);
	//left(220,ks/2); //let go of hangers onto the ledge
	
	//wiggle to drop off the hangers (BACKUP CODE)
	
//Not using this	left(40,ks/2);				// left 30 degrees
					/*right(60,ks/2);				// right 50 degrees
					left(20,ks/2);*/				// deposit hangers and push them to the sides, left 20 degrees back*/
	
	/* testing code so commenting rest of code
	
	mrp(MOT_LEFT, 500, 1544); // undo the turn to be straight again
	backward(10.00);	// back up 10 cm, going to get blue hangers next
	msleep(500);
	
	
	
	/** Don't FIX WITH SLOWSERVO anymore, slowservo library broken**/
	/*
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
	*/
	//TODO: go back a little - do same thing as the regular hangers to place blue on top
	
	
	ao();
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
