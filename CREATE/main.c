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

#define LTOUCH 15
#define RTOUCH 14

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
	create_backward(63,100);
	tdist+=50;
	create_block();
	SHOW(printf("moved...")); 
	msleep(1000);
	set_servo_position(GRABBER, 990);		//used to be 400
	msleep(500);
	set_servo_position(GRABBER, 2047);
	msleep(500);
	set_servo_position(GRABBER, 990);		//used to be 400
}

void getCubes()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>400)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		create_backward(2,10); 
		tdist+=2;
		SHOW(printf("tdist is %d\n", tdist));
		if(tdist>450){
			tdist=0;
			set_servo_position(GRABBER, 990);	//used to be 2047
			return;
		}
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 2047);
		
	if(tdist<450) getCubes();
	else {
		tdist=0;
		set_servo_position(GRABBER, 990);		//used to be 2047
	}
}

//CLOSE HANDLE 2----------------------------------------------------------------
void closeHandle2() 
{
	printf("FOUND A CUBE: %d\n",analog_et(ET));
	create_backward(15,100);
	tdist-=20;
	create_block();
	SHOW(printf("moved...")); 
	msleep(1000);
	set_servo_position(GRABBER, 990);		//used to be 400
	msleep(500);
	set_servo_position(GRABBER, 2047);
	msleep(500);
	set_servo_position(GRABBER, 990);		//used to be 400
}

void getCubes2()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>400)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		create_forward(2,30);
		tdist+=2;
		SHOW(printf("tdist is %d\n", tdist));
		if(tdist>340){
			tdist=0;
			set_servo_position(GRABBER, 990);	//used to be 2047
			return;
		}
	}
	
	closeHandle2();
	msleep(1000);
	create_forward(20,20);
	set_servo_position(GRABBER, 2047);
		
	if(tdist<340) getCubes2();
	else {
		tdist=0;
		set_servo_position(GRABBER, 990);		//used to be 2047
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
	do{ 
		create_drive_direct(-300,-300); 
		SHOW(printf("ltouch: %d\n", digital(LTOUCH))); 
		SHOW(printf("rtouch: %d\n", digital(RTOUCH))); 
	}
	while(digital(LTOUCH)==0&&digital(RTOUCH)==0);
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
	create_backward(62,100); //previously 65
	create_block();
	
	//we're now in front of the first goal 
	create_right(85,0,60); 
	create_block();
	
	printf("In front of the cubes");
	
	//search moving backwards across the cubes
	
	/**ARM MOVEMENT, 1**/
	
	arm_open();
	bmd(MOTARM);
	getCubes();
	
	/**SECOND BLOCK PICKUP POSITION**/
	
	set_servo_position(GRABBER, 400);				//close claw
	create_left(30, 0, 60);							//left 30 degrees
	create_block();
	printf("Left turn complete\n");
	create_backward(250, 1000);						//backward 10 inches
	printf("Drive 1 complete\n");
	create_right(30, 0, 60);						//right 30 degrees
	create_block();
	create_backward(500, 800);						//backward 40 inches
	create_block();
	printf("Drive 2 complete\n");
	backward_bump();
	printf("Finished square up");
	create_block();
	create_forward(60,500);
	create_block();
	create_left(90,0,60);
	create_block();
	msleep(1000);
	forward_bump();
	create_block();
	create_backward(50,100);
	create_right(86,0,60);	
	create_block();
	tdist=0;
	/**ARM MOVEMENT, 2**/
	
	set_servo_position(GRABBER, 2047);
	arm_open();
	bmd(MOTARM);
	getCubes2();
	set_servo_position(GRABBER, 990);

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
