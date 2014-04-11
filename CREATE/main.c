/*
* Main program for CREATE driving
* 
*
*
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

#define LS 0
#define FULL 100
#define MOTARM 0
#define ET 2
#define GRABBER 1
#define TBUTTON 8 
#define MICRO 0

/**
 *  Micro
 *	Closed: 1860
 *	Open:	700
**/


//debug?
#define DEBUG 

#ifdef DEBUG 
	#define SHOW(x) printf("DEBUG: "); x 
#else 
	#define SHOW(x) 
#endif

/**#defines for which method to run**/
//#define DUMPTEST
#define MAIN 
//#define ARMTEST

void arm_open(){
	do{
		bk(MOTARM);
	}
	while(digital(TBUTTON)==0);
	bk(MOTARM);
	msleep(200);
}

void arm_close(){
	mrp(MOTARM, 1000, 3000);
}

void micro_crash(){
	set_servo_position(MICRO, 1994);
}

int tdist = 0;

void closeHandle() 
{
	printf("FOUND A CUBE: %d\n",analog_et(ET));
	create_backward(63,100);
	tdist+=63;
	create_block();
	SHOW(printf("moved...")); 
	msleep(1000);
	set_servo_position(GRABBER, 135);		//used to be 400
	msleep(500);
	set_servo_position(GRABBER, 1500);
	msleep(500);
	set_servo_position(GRABBER, 135);		//used to be 400
}

void getCubes()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>400)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		create_backward(2,30); 
		tdist+=2;
		SHOW(printf("tdist is %d\n", tdist));
		if(tdist>300){
			tdist=0;
			set_servo_position(GRABBER, 135);	//used to be 2047
			set_servo_position(MICRO, 1860);
			return;
		}
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 1500);
		
	if(tdist<300) getCubes();
	else {
		tdist=0;
		set_servo_position(GRABBER, 135);		//used to be 2047
		set_servo_position(MICRO, 1860);
	}
}

int ccount=0;
int tdist2=0;
//CLOSE HANDLE 2----------------------------------------------------------------
void closeHandle2() 
{
	ccount++;
	printf("FOUND A CUBE: %d\n",analog_et(ET));
	create_backward(15,100);
	tdist2-=15;
	create_block();
	SHOW(printf("moved... tdist is %d\n", tdist)); 
	msleep(1000);
	set_servo_position(GRABBER, 135);		//used to be 400
	msleep(500);
	set_servo_position(GRABBER, 1500);
	msleep(500);
	set_servo_position(GRABBER, 135);		//used to be 400
}

void getCubes2()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>400)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		printf("tdist is %d\n", tdist2);
		create_forward(2,30);
		tdist2+=2;
		if(ccount>=2 || tdist2>250){
			set_servo_position(GRABBER, 135);	//used to be 2047
			return;
		}
	}
	
	closeHandle2();
	msleep(1000);
	set_servo_position(GRABBER, 1500);
	create_forward(40,20);
	tdist2+=40;
	create_block();
	printf("Moved forward");
		
	if(ccount<2 && tdist2<250) getCubes2();
	else {
		//set_servo_position(GRABBER, 135);		//used to be 2047
		set_servo_position(MICRO, 1860);
	}
}

//bump functions
void forward_bump()
{
	do{ create_drive_direct(100,100); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	while(digital(LTOUCH)==0) create_drive_direct(-100,-100);
	while(digital(RTOUCH)==0) create_drive_direct(0,-100);
}

/*************MAIN************/

#ifdef MAIN
int main()
{
	/**INITIALIZE CODE**/
	light_start(LS);
	set_analog_pullup(ET,0);
	SHOW(printf("analog pullup is %d\n", get_analog_pullup(ET)));
	enable_servo(MICRO);
	set_servo_position(MICRO, 0);
	SHOW(printf("Connecting...\n"));
	create_connect();
	SHOW(printf("Complete!\n"));
	shut_down_in(120.); 
	
	arm_open();
	bmd(MOTARM);
	printf("Arm opened");
	
	create_forward(40,100);
	create_block();
	create_left(88,0,60);
	create_block();
	backward_bump();
	create_forward(40,100);
	create_block();
	create_right(88,0,60);
	create_block();
	backward_bump();
	
	/**FIRST BLOCK PICKUP POSITION**/
	
	printf("First block pickup position running...");
	
	create_forward(520,600);	//rush forward
	create_block();
	create_block();
	forward_bump(); 			//forward to pvc pipe
	create_block(); 			//finish the bump	
	create_backward(43,100); 	//previously 65
	create_block();
	
	//we're now in front of the first goal 
	create_right(84,0,60); 
	create_block();
	printf("In front of the cubes");
	enable_servo(GRABBER);
	set_servo_position(GRABBER, 1500);
	//search moving backwards across the cubes
	
	/**ARM MOVEMENT, 1**/
	
	arm_open();
	bmd(MOTARM);
	getCubes();
	
	/**SECOND BLOCK PICKUP POSITION**/
	
	set_servo_position(GRABBER, 400);				//close claw
	msleep(1000);
	arm_close();
	msleep(1000);
	create_left(35, 0, 60);							//left 35 degrees
	create_block();
	printf("Left turn complete\n");
	create_backward(250, 1000);						//backward 10 inches
	printf("Drive 1 complete\n");
	create_right(35, 0, 60);						//right 35 degrees
	create_block();
	create_backward(600, 800);						//backward 40 inches
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
	create_backward(40,100);
	create_right(86,0,60);	
	create_block();
	tdist=0;
	
	/**ARM MOVEMENT, 2**/
	
	set_servo_position(MICRO, 700);
	//msleep(2000);
	arm_open();
	bmd(MOTARM);
	msleep(2000);
	set_servo_position(GRABBER, 1500);
	getCubes2();
	set_servo_position(GRABBER, 135);

	/**COMPLETED PICKUP**/
	
	set_servo_position(MICRO, 2047);
	backward_bump();
	arm_close();
	create_forward(40,100);
	create_right(90,0,60);
	create_block();
	//msleep(1000);
	create_forward(320,600);
	create_block();
	forward_bump();
	create_left(90,0,60);
	create_block();
	backward_bump();
	create_block();
	set_servo_position(MICRO, 700);
	//msleep(2000);
	create_forward(20,100);
	create_block();
	create_backward(20,100);
	create_block();
	
	/*
	create_forward(10,100);
	create_block();
	create_backward(10,100);
	create_block();
	*/
	
	printf("finished");
	create_disconnect();
	
	/*
	backward_bump();
	arm_close();
	create_forward(40,100);
	create_right(90,0,60);
	create_block();
	msleep(1000);
	create_forward(320,600);
	create_block();
	forward_bump();
	create_left(90,0,60);
	backward_bump();
	set_servo_position(MICRO, 700);
	msleep(1000);
	create_block();

	printf("finished");
	*/
}
#endif

/**DUMP TEST**/

#ifdef DUMPTEST
int main() {
	create_connect();
	enable_servos();
	set_servo_position(MICRO, 2047);
	backward_bump();
	arm_close();
	create_forward(40,100);
	create_right(90,0,60);
	create_block();
	msleep(1000);
	create_forward(320,600);
	create_block();
	forward_bump();
	create_left(90,0,60);
	backward_bump();
	create_block();
	set_servo_position(MICRO, 700);
	create_block();
	create_forward(10,100);
	create_block();
	create_backward(10,100);
	create_block();
	printf("finished");
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
