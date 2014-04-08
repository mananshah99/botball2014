/*
* Main program for CREATE driving
* 
* Assumes that the arm to pick up the cubes is facing to the right
* as the create moves alongside the PVC pipe
*
* 
*
*/

#include <stdio.h>
#include "./createDrive.h"
#include "./createSlow.h"
#include "./generic.h"

#define FULL 100
#define MOTARM 0
#define ET 2
#define GRABBER 1
#define TBUTTON 8 
#define MICRO 0
//debug?
#define DEBUG 

#ifdef DEBUG 
	#define SHOW(x) printf("DEBUG: "); x 
#else 
	#define SHOW(x) 
#endif

/**#defines for which method to run**/
#define MAIN 
//#define ARMTEST

//1751 to -1740
void arm_open(){
	SHOW(printf("Here"));
	do{
		bk(MOTARM);
	}
	while(digital(TBUTTON)==0);
}

void arm_close(){
	mrp(MOTARM, 1000, 3491);
}

void micro_crash(){
	set_servo_position(MICRO, 1994);
}

int tdist = 0;

void closeHandle() 
{
	printf("FOUND A CUBE: %d\n",analog_et(ET));
	create_backward(53,100);
	tdist+=50;
	create_block();
	SHOW(printf("moved...")); 
	msleep(1000);
	set_servo_position(GRABBER, 400);
}

void getCubes()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>480)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		create_backward(2,10); 
		tdist+=2;
		SHOW(printf("tdist is %d\n", tdist));
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 2047);
		
	if(tdist<500) getCubes();
	else {
		tdist=0;
		arm_close();
	}
}

//bump functions
void forward_bump()
{
	do{ create_drive_direct(280,280); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	do{ create_drive_direct(-300,-300); }
	while(get_create_lbump()==0);
}

/*************MAIN************/

#ifdef MAIN
int main()
{
	/**INITIALIZE CODE**/
	
	set_analog_pullup(ET,0);
	SHOW(printf("analog pullup is %d\n", get_analog_pullup(ET)));
	enable_servos();
	set_servo_position(GRABBER, 2047);
	
	SHOW(printf("Connecting...\n"));
	create_connect();
	SHOW(printf("Complete!\n"));
	shut_down_in(120.); 
	mrp(MOTARM, 1000, 573);
	
	/**FIRST BLOCK PICKUP POSITION**/
	
	printf("First block pickup position running...");
	
	create_wait_time(20); 	//20 deciseconds for the link to pass	
	forward_bump(); 		//forward to pvc pipe
	create_block(); 		//finish the bump	
	create_backward(55,100); //previously 65
	create_block();
	
	//we're now in front of the first goal 
	create_right(86,0,60); 
	create_block();
	
	printf("In front of the cubes");
	
	//search moving backwards across the cubes
	
	/**COLOR SORTING AND ARM MOVEMENT**/
	
	arm_open();
	bmd(MOTARM);
	getCubes();
	
	/**SECOND BLOCK PICKUP POSITION**/
	
	//change this to drive around the LINK
	create_drive_direct_dist(-FULL,-FULL,50);
	
	/*
	 * Angle is 187 to make a full turn 
	 * Radius is 0 
	 * Speed is 60 (too fast?)
	 */
	create_right(175,0,60);
	
	//drive to the other end of the board
	forward_bump();
	
	//TODO: Get the actual distance (replace 30)
	create_drive_direct_dist(-FULL,FULL,30);
	create_right(87,0,60);
	forward_bump();
	
	/**COLOR SORTING AND ARM MOVEMENT, 2**/
	
	arm_open();
	getCubes();
	arm_close();
	
	/**COMPLETED PICKUP**/
	
	//dump here
	
	//next box area after squaring up
	printf("finished");
	create_disconnect();
	return 0;
}
#endif

/**ARM TEST - BASIC FUNCTIONALITY**/

#ifdef ARMTEST

//tester for the arm functions
int main()
{
	//successful
	SHOW(printf("Arm Opening.."));
	arm_open();
	bmd(MOTARM);
	enable_servo(MICRO);
	micro_crash();
	arm_close();
	bmd(MOTARM);
}
#endif
