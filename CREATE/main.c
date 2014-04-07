/*
* Main program for CREATE driving
* 
* Assumes that the arm to pick up the cubes is facing to the right
* as the create moves alongside the PVC pipe
* -1212
* -639
*
*/

#include <stdio.h>
#include "./createDrive.h"
#include "./createSlow.h"
#include "./generic.h"

#define FULL 100

/* Grabber positions
 *	Closed: 635
 *	Open: 2047
*/


//TODO Fix these ports
#define MOTARM 0
#define TOPHAT 2
#define GRABBER 1
#define TBUTTON 8 //port 8
#define MICRO 0
#define DEBUG 

//show debugging? 
#ifdef DEBUG 
  #define SHOW(x) printf("DEBUG: "); x 
#else 
#define SHOW(x) 
#endif

/**#defines for which method to run**/

#define MAIN 
//#define ARMTEST

//arm functions
//1 indicates the switch is closed
//0 indicates the switch is open

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

//variables for counting the cubes
int cCount = 0;
void resetcount() {cCount = 0;}
int time = 0;

void closeHandle() 
{
	printf("FOUND A CUBE: %d\n",analog(TOPHAT));
	create_backward(5,100);
	create_block();
	msleep(1000);
	set_servo_position(GRABBER, 635);
}

void getCubes()
{
	printf("init: %d\n",analog(TOPHAT));
	while(!(analog(TOPHAT)<750)) //haven't found an orange blob
	{ 
		printf("value: %d\n",analog(TOPHAT));
		create_backward(2,10); 
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 2047);
	//arm_close();
	//arm_half(); //should move and close the arm around the block
	
	cCount++;
	if(cCount!=2) getCubes();
	else {
		resetcount(); //no recursive call, function ends
		arm_close();
	}
}

//1994
//bump functions
//drive forward until a bumper's hit
void forward_bump()
{
	do{ create_drive_direct(300,300); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	do{ create_drive_direct(-300,-300); }
	while(get_create_lbump()==0);
}

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

/*************MAIN************/

#ifdef MAIN
int main()
{
	//enable grabber, is this going to fix anything? 
	enable_servos();
	set_servo_position(GRABBER, 2047);
	
	/**INITIALIZE CODE**/
	SHOW(printf("Connecting...\n"));
	create_connect();
	SHOW(printf("Complete!\n"));
	shut_down_in(120.); 
	mrp(MOTARM, 1000, 573);
	
	/**FIRST BLOCK PICKUP POSITION**/
	
	printf("First block pickup position running...");
	
	create_wait_time(20); //20 deciseconds for the link to pass	
	forward_bump(); //forward to pvc pipe
	create_block(); //finish the bump	
	create_backward(65,100);
	create_block();
	
	//we're now in front of the first goal 
	create_right(80,0,60); 
	create_block();
	
	printf("In front of the cubes");
	
	//search moving backwards across the cubes
	
	/**COLOR SORTING AND ARM MOVEMENT**/
	
	arm_open();
	bmd(MOTARM);
	getCubes();
	
	/**SECOND BLOCK PICKUP POSITION**/
	create_drive_direct_dist(-FULL,-FULL,50);
	
	/*
	Angle is 187 to make a full turn 
	Radius is 0 
	Speed is 60 (too fast?)
	*/
	create_right(175,0,60);
	//drive to the other end of the board
	forward_bump();
	
	//TODO: Get the actual distance (replace 30)
	create_drive_direct_dist(-FULL,FULL,30);
	create_right(87,0,60);
	forward_bump();
	//we're now in front of the second goal 
	
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
