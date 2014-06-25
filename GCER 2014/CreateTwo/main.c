#include "createDrive.h"
#include "generic.h"
//Start: Monday 23 June 2014
#define ARM 0
#define HANGER 3
#define ELEVATOR 0
#define SENSOR_UP 15
#define SENSOR_DOWN 14
#define ARM_UP 150
#define ARM_UMID 400
#define ARM_DMID 1200
#define ARM_DOWN 2000
#define HANGER_CLOSE 0
#define HANGER_OPEN 1365
//#define LIGHTSTART
/*..............................................Functions Begin..............................................*/
void arm_lift(){
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_UP);
	msleep(1000);
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
	
	create_right(82,0,100); //(angle,radius,speed); 82 = 90deg
	create_backward(400, 100);// (distance in mm,speed)
	create_left(82,0,100);
	create_backward(885, 100);
	create_right(90,0,100);
	create_backward(250,100);
	arm_lift();//armlift while robot moves
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	create_forward(300,100);
	create_block();//Backed-up from Pipes
	
	arm_lower();
	create_backward(215,25);
	create_block();
	
	servo_set(HANGER,HANGER_CLOSE,0.5);
	msleep(500);
	servo_set(ARM,ARM_DMID,0.5);
	servo_set(ARM,ARM_DOWN,0.5);
	create_forward(300,100);
	create_block();
	
	arm_lift();
	servo_set(ARM,ARM_UMID,0.5);
	create_backward(215,25);
	create_block();
	
	servo_set(ARM,ARM_UP,0.5);
	
	//Temp End Code
	sleep(1);
	disable_servos();
}
