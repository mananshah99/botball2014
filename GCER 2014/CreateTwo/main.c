#include "createDrive.h"
#include "generic.h"
//Start: Monday 23 June 2014
#define ARM 0
#define HANGER 3
#define ELEVATOR 0
#define SENSOR_UP 15
#define SENSOR_DOWN 14
#define ARM_UP 150
#define ARM_DOWN 1900
#define HANGER_CLOSE 0
#define HANGER_OPEN 1365
//#define LIGHTSTART
/*..............................................Functions Begin..............................................*/
void arm_lift(){
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_UP);
	msleep(400);
	//le elevator
	while(digital(SENSOR_UP)==0)
	{
		motor(ELEVATOR, 80);
		msleep(500);
	}
	motor(ELEVATOR,0);
}
void arm_lower(){
	//le elevator
	while(digital(SENSOR_DOWN)==0)
	{
		motor(ELEVATOR, -10);
		msleep(500);
	}
	motor(ELEVATOR,0);
	msleep(400);
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_DOWN);
	msleep(400);
}
/*..............................................Functions End..............................................*/
int main()
{
	//wait_for_light(LIGHTSTART);
	shut_down_in(119.);
	create_connect();
	enable_servos();
	servo_set(HANGER,HANGER_CLOSE,0.3);
	sleep(1);
	
	create_right(82,0,100); //(angle,radius,speed)
	create_backward(400, 100);// (distance in mm,speed)
	create_left(85,0,100);
	create_backward(850, 100);
	create_right(90,0,100);
	create_backward(300,100);
	arm_lift();//armlift while robot moves
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	create_forward(100,100);
	create_block();//Backed-up from Pipes
	
	arm_lower();
	
	sleep(5);
}
