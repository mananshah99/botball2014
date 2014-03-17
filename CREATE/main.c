#include "./createDrive.h"
#include "./createSlow.h"
#include "./generic.h"
#include "./camera.h"

#define FULL 100
//TODO Fix this based on the actual port for the servo arm
#define SERV_ARM 1
#define TOPHAT 2

/**#defines for which method to run**/
#define MAIN 
//#define ARMTEST
/***********************************/

//arm functions
//CHECK THESE VALUES BEFORE TESTING
void arm_close(){
	set_servo_position(SERV_ARM,2040);
}
void arm_open(){
	set_servo_position(SERV_ARM,646);
}
void arm_half(){
	set_servo_position(SERV_ARM,1800);
}

//bump functions
void forward_bump(c)
{
	do{ create_drive_direct(300,300); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	do{ create_drive_direct(-300,-300); }
	while(get_create_lbump()==0);
}

#ifdef ARMTEST
//tester for the arm functions
int main()
{
	printf("Arm Opening..");
	arm_open();
	msleep(10000);
	printf("Arm Midway...");
	arm_half();
	msleep(10000);
	printf("Arm Closing...");
	arm_close();
	msleep(10000);
}
#endif

#ifdef MAIN
int main()
{
	/**INITIALIZE CODE**/
	printf("Connecting...\n");
	create_connect();
	create_full();
	start(); //from the camera library
	printf("Complete!\n");
	shut_down_in(120.); //IMPORTANT!
	
	/**FIRST BLOCK PICKUP POSITION**/

	create_wait_time(20); //20 deciseconds for the link to pass	
	forward_bump(); //drives and blocks all the way
	create_block(); //finish the bump
	//we're now in front of the first goal (NOT TESTED)
	
	/**COLOR SORTING AND SERVO MOVEMENT**/
	arm_open();	
	//run the getcubes function for 30 seconds
	//note that getCubes() is not complete yet 
	run_for(30.,getCubes());
	
	arm_close();
	
	/**SECOND BLOCK PICKUP POSITION**/
	
	create_drive_direct_dist(-FULL,-FULL,50);
	
	/*
	 Angle is 87 because 90 degrees never works
	 Radius is 0 
	 Speed is 60 (too fast?)
	*/
	create_right(87,0,60);
	//drive to the other end of the board
	forward_bump();
	
	//TODO: Get the actual distance (replace 30)
	create_drive_direct_dist(-FULL,FULL,30);
	create_right(87,0,60);
	forward_bump();
	//we're now in front of the second goal (NOT TESTED)
	
	/**COLOR SORTING AND SERVO MOVEMENT, 2**/
	
	arm_open();
	
	//run the getcubes function for 30 seconds
	//note that getCubes() is not complete yet 
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
	{
		//move right
	}
	else
	{
		arm_half(); //should move and close the arm around the block
		
	}
}
