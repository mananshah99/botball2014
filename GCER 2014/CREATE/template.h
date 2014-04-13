/************************************************************************
 * Botball LACT Template												*
 * Include this in each of your programs as a default library. 			*
 * 																		*
 * Sample Usage: 														*
 *																		*
 *	Place the following files inside the Link folder					*
 *		: menu.h														*
 *		: drive.h														*
 *																		*
 *	Place the following files inside the Create folder					*
 *		: createDrive.h													*
 *		: finalscripting.c												*
 *		: X menu.h (TODO: fix 4/12/14)									*
 *		: finalscripting.c												*
 *																		*
 *	Place the version of this file (either with the create or link mode	*
 *	defined) in the same directory as your create or link folder.		*
 * 																		*
 *	Then, include the following line at the beginning of your program:	*
 *		#include "./template.h"											*
 *																		*
 * @author Manan														*
 * Version 421014														*
 ************************************************************************/

/*
 * Comment out LINK if you are running the Create code, and comment out CREATE if
 * you are running the link code. 
 *
 * Default: #define CREATE
 */

#define CREATE
//#define LINK

#include <stdio.h>

#ifdef CREATE
	#include "./createDrive.h"
#endif

#ifdef LINK
	#include "./drive.h"
#endif

//for now, menu.h doesn't work. TODO: Fix this
//#include "./menu.h"

//common light sensor port
#define LS 0
#define ls() light_start(LS)

/*
 * Method to show/hide print statements
 * based on whether DEBUG is defined. 
 *
 * Usage: SHOW(printf("Hello World")); 
 *	--> Debug: Hello World		if debug is defined
 *	--> 						if debug is not defined (nothing printed)
 *
 */
#ifdef DEBUG 
	#define SHOW(x) printf("DEBUG: "); x 
#else 
	#define SHOW(x) 
#endif

#ifdef CREATE
	#define WHEEL_DROP 1
	#define CLIFF 10
	#define BUMP 5
	#define LEFT_BUMP 6
	#define RIGHT_BUMP 7
	#define BUTTON_ADVANCED 16
	#define BUTTON_PLAY 17			//TODO: finish all events.  p16 of create docs
	#define SEN_0 18
		
	#define get_high_byte2(a) ((a)>>8)
	#define get_low_byte2(a) ((a)&255)
#endif

#define WAIT(x); while(!(x)){msleep(10);}
#define gmpc(port) get_motor_position_counter(port)

#define DEGTORAD 0.017453292519943295769236907684886
#define RADTODEG 57.295779513082320876798154814105
#define pi 3.1415926535897932384626433832795

#define state(State) if (currstate == State)
#define next(State) currstate = State
int currstate;

//Generic Utility
float bound(float num, float max)
{
	if (num > max) return max;
	else if (num < -max) return -max;
	else return num;
}
//1 if true, 0 if false
int in_range(int input, int wanted, int fudge)
{
	if (wanted+fudge >= input && wanted-fudge <= input) return 1;
	else return 0;
}

//actual distance away from object with ET sensor
float ET_distance(int port){
    return ((sqrt(100.0/analog10(port)))-2.2);
}

//Light Start
#define light_s() analog10(sensor)
void light_start(int sensor)
{
	int max = 0,min = 9999,curr = 0,avg = 0;
	display_clear();
	display_printf(0,0,"Max:");
	display_printf(0,1,"Min:");
	display_printf(0,2,"Curr:");
	display_printf(0,3,"avg:");
	while(!b_button() && !c_button())	//Interaction Button
	{
		curr = light_s();
		if (curr > max) max = curr;
		if (curr < min) min = curr;
		
		avg = (max+min)/2;
		display_printf(5,0,"%d   ",max);
		display_printf(5,1,"%d   ",min);
		display_printf(6,2,"%d   ",curr);
		display_printf(5,3,"%d   ",avg);
		
		if (curr > avg) display_printf(10,5,"XX");
		else display_printf(10,5,"OO");
		msleep(50);
	}
	display_clear();
	display_printf(0,4,"Prepared to begin: c to skip");
	while(light_s() > avg && !(c_button())) msleep(50);
}

//Timing Utility 
long _start_time;
void start()
{
	_start_time = systime();
}
float curr_time()
{
    return (systime()-_start_time)/1000.0;
}
void now()
{
    printf("now %f\n",curr_time());
}

void wait_till(float t)
{
    now();
    msleep(((long)(t*1000))-curr_time());
}

//Servo functions
void servo_set(int port,int end,float time)//,float increment)
{
	//position is from 0-2047
	float increment = .01;
	float curr,start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	curr = start;
	if (start > end)
	{
		while(curr > end)
		{
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	set_servo_position(port,end);
}

//camera utility
int cam_area(int channel){
	//returns largest blob in channel, or 0 if none
	if (get_object_count(channel) > 0) return get_object_area(channel,0);
	return 0;
}
void update_wait(){
	//updates the camera, and waits until success
	while(!camera_update()) msleep(1);
}

//deprecated, use update_wait()
void cam_block() { update_wait(); }