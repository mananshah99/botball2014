#include "createDrive.h"
#include "generic.h"
//Start: Thursday 3 July 2014
#define ARM 0
#define HANGER 3
#define ELEVATOR 0
#define SENSOR_UP 15
#define SENSOR_DOWN 14
#define ARM_UP 150
#define ARM_UMID 700
#define ARM_DMID 1200
#define ARM_DOWN 2000
#define HANGER_CLOSE 0
#define HANGER_OPEN 1365
//#define LIGHTSTART
/*..............................................Functions Begin..............................................*/
void create_setup(){
	create_backward(10,50);
	create_wait_time(1);
	create_forward(15,50);
	create_left(85,0,50);
	create_forward(50,50);
	create_block();
	msleep(1000);
}
void arm_lift(){
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_UP);
	msleep(1000);
	//le elevator
	while(digital(SENSOR_UP)==0)
	{
		motor(ELEVATOR, 80);
		msleep(50);
	}
	motor(ELEVATOR,0);
}
/*..............................................Functions End..............................................*/
int main(){
	create_connect(); start();
	create_setup();
	//light_start(LIGHTSTART);
	shut_down_in(119.);
	enable_servos();
	servo_set(ARM,ARM_DOWN,0.3);
	servo_set(HANGER,HANGER_CLOSE,0.3);
	
	create_right(85,0,250);
	create_backward(30,50);//square up
	create_stop();
	create_wait_time(1);
	create_forward(390, 400);// (distance in mm,speed)
	create_left(82,0,250);
	create_forward(310, 300);//scrape against pipe is deliberate
	create_block();
	
	arm_lift();
	create_left(82,0,250);//face the rack
	create_forward(100,200);
	create_backward(230,200);
	create_forward(50,200);
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	//Temp End Code
	sleep(10); disable_servos(); printf("Done\n");
}
