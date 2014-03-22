/*
* Main program for CREATE driving
* 
* Assumes that the arm to pick up the cubes is facing to the right
* as the create moves alongside the PVC pipe
*
*
*/

#include "./createDrive.h"
#include "./createSlow.h"
#include "./generic.h"
#include "./camera.h"

#define FULL 100

//TODO Fix this based on the actual port for the arm
#define MOTARM 1
#define TOPHAT 2
#define TBUTTON 8 //port 8

/**#defines for which method to run**/
//#define MAIN 
#define ARMTEST

int ccount = 0;
void resetcount() {ccount = 0;}

/**ARM TEST - BASIC FUNCTIONALITY**/

#ifdef ARMTEST
//tester for the arm functions
int main()
{
	printf("Arm Opening..");
	arm_open();
	msleep(10000);
	printf("Arm Closing...");
	arm_close();
	msleep(10000);
}
#endif

/*************MAIN************/

#ifdef MAIN
int main()
{
	/**INITIALIZE CODE**/
	printf("Connecting...\n");
	create_connect();
	create_full(); //needed?
	printf("Complete!\n");
	shut_down_in(120.); 
	
	/**FIRST BLOCK PICKUP POSITION**/

	create_wait_time(20); //20 deciseconds for the link to pass	
	forward_bump(); //forward to pvc pipe
	create_block(); //finish the bump

	//we're now in front of the first goal 
	
	create_drive_direct_dist(-FULL-FULL,20); //more or less? 
	create_right(87,0,60); 
	forward_bump();

	//search moving backwards across the cubes

	/**COLOR SORTING AND ARM MOVEMENT**/
	arm_open();	
	//run getcubes for 30 seconds 
	run_for(30.,getCubes());
	arm_close();
	
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
	run_for(30.,getCubes());
	arm_close();
	
	/**COMPLETED PICKUP**/
	
	//dump here
	
	//next box area after squaring up
	printf("finished");
	create_disconnect();
	return 0;
}
#endif

void getCubes()
{
	while(!(analog(TOPHAT)<700) //haven't found an orange blob (normally around 800-900)
	{ create_drive_direct(10,10,2); }
	else
	{
		arm_half(); //should move and close the arm around the block
		ccount++;
		if(ccount!=2) getCubes();
		else resetcount(); //no recursive call, function ends
	}
}

//arm functions
//1 indicates the switch is closed
//0 indicates the switch is open
void arm_open(){
	while(digital(TBUTTON)==0) motor(MOTARM, 70);
}

//moves arm backwards for 5 seconds
void arm_close(){
	run_for(5.,movArm(-70));
}

void movArm(int spd)
{ motor(MOTARM, spd); }

//bump functions
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
