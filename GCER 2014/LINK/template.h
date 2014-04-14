/********************************************************************************
 * Botball LACT Template							*
 * Include this in each of your programs as a default library. 			*
 * 										*
 * Sample Usage: 								*
 *										*
 *	Place the following files inside the Link folder			*
 *		: menu.h							*
 *		: drive.h							*
 *										*
 *	Place the following files inside the Create folder			*
 *		: createDrive.h							*
 *		: finalscripting.c						*
 *										*
 *	Place the version of this file (either with the create or link mode	*
 *	defined) in the same directory as your create or link folder.		*
 * 										*
 *	Then, include the following line at the beginning of your program:	*
 *		#include "./template.h"						*
 *										*
 * @author Manan								*
 * Version 421014								*
 ********************************************************************************/

/*
 * Comment out LINK if you are running the Create code, and comment out CREATE if
 * you are running the link code. 
 *
 * Default: #define CREATE
 */

//#define CREATE
#define LINK

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
 *	--> 				if debug is not defined (nothing printed)
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
#define LIMIT(thing,time); {double _tmptime = seconds()+time; while(!(thing) && (_tmptime > seconds())){msleep(1);}}

#define gmpc(port) get_motor_position_counter(port)

#define DEGTORAD 0.017453292519943295769236907684886
#define RADTODEG 57.295779513082320876798154814105
#define pi 3.1415926535897932384626433832795

//States
#define state(State) if (currstate == State)
#ifndef MENU
	#define next(State) currstate = State
#endif
int currstate;

#ifdef MENU

//Menu
struct menuitem{
	int snum;
	char* name;
};
extern struct menuitem menu[];

int selectionlist(int length){
	int current = DEFAULT_OPTION;
	int counter = 1;
	int oldcurrent = DEFAULT_OPTION;
	while(1){
		if(a_button()){
			while(a_button())msleep(1);
			return(current);
		}
		if(c_button()){
			while(c_button())msleep(1);
			oldcurrent = current;
			current --;
			counter = 1;
			if(current < 0) current=length-1;
		}
		if(b_button()){
			while(b_button())msleep(1);
			oldcurrent = current;
			current ++;
			counter = 1;
			if (current >= length) current=0;
		}
		if(counter == 1){
			display_printf(0,oldcurrent+1," ");
			display_printf(0,current+1,"*");
			counter = 0;
		}
	}
}
int options(){
	display_clear();
	msleep(10);
	int charlength;
	int result;
	display_printf(0,0,"A Accept|B down|C up\n");
	WAIT(!a_button());
	result = selectionlist(draw_screen());
	display_clear();
	return(result);
}

int draw_screen(){
	int i;
	for(i=0;i<MENUSIZE;i++){
		display_printf(0,i+1,"  %s",menu[i].name);
	}
	return(MENUSIZE);
}

void next(int State) {
	int i;
	currstate = State;
	i = -1;
	while (!strcmp(menu[++i].name,"FIN")){
		if (menu[i].snum==State){
			nowstr(menu[i].name);
			return;
		}
	}
	now();
}

#define DEFAULT_OPTION 0
#define get_mode() currstate = menu[options()].snum

#endif

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

void nowstr(char *s)
{
	printf("%s %f\n",s,curr_time());
}

void wait_till(float t)
{
    now();
    msleep(((long)(t*1000))-curr_time());
}

//Servo Utility
void servo_set(int port, int end, float time)
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

//Camera Utility
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

//ASUS Xtion Depth Sensor Utility

//0 if not interactive, 1 if interactive
//only need meaningful x and y values if not interactive
int depth_distance(int interactive, int x, int y) 
{
	depth_open();
	if(interactive==1)
	{
		int r,g,b,row,c,val;
		graphics_open(320,240); // open up graphics window (full screen on Link)
		while(!get_mouse_left_button()) 
		{ 
			depth_update(); 
			for(row=0; row<240; row++) 
			{ 
				for(c=0; c<320; c++) 
				{ 
					val = get_depth_value(row,c) ; // get distance for pixel in mm
					// if its not a legal value or its too far (1.5m for this program), color it black
					if(val > 1536 || val==0) graphics_pixel(c,row,0,0,0);
					else 
					{ 
					       val=val - 512; 
					       r=val > 512 ? 0 : 255-val/2;  		// red if close
					       g=val > 512 ? 255-(val-512)/2 : val/2; 	// green if mid value
					       b=val > 512 ? val/2-255 : 0;  		// blue if far (~1.5m)
					       graphics_pixel(c,row, r,g,b); 		// draw the pixel
					}
				}
			}
			graphics_update(); // paint the screen with all of the pixels
		}
		get_mouse_position(&c,&row); 		
		depth_close(); graphics_close();  
		printf("Distance to pixel %i,%i is %imm\n\n\n",c,row,get_depth_value(row,c))
	}
	else return get_depth_value(x,y);
}
  
//points a servo centered on the camera's fov towards an object that fits the color defined at camchannel
void set_servo_color(int servo, int camchannel) 
{
	int offset, x, y;
	enable_servo(servo);	// enable servo
	camera_open();	
	camera_update();    
	while (get_object_count < 0) { camera_update(); msleep(1); }
	
	//largest blob - we now have an object in sight
	point2 p = get_object_center(camchannel,0);
	x = p.x;
	y = p.y;
	
	display_printf(0,1,"Center of largest blob: (%d,%d)   ",x,y);
	offset=5*(x-80); // amount to deviate servo from center
	set_servo_position(0,1024+offset);
}