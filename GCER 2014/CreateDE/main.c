#include "createDrive.h"
#include "generic.h"
//Start: Thursday 3 July 2014
#define ARM 0
#define HANGER 3
#define ELEVATOR 0
#define ELEVATORTWO 2
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
	printf("Press A to start");
	while(a_button()==0){
		msleep(1);
	}
}
void arm_lift(){
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_UP);
	msleep(1000);
	//le elevator
	while(digital(SENSOR_UP)==0)
	{
		motor(ELEVATOR, 100);
		motor(ELEVATORTWO,65);
	}
	ao();
}
void arm_lower(){
	//le elevator
	while(digital(SENSOR_DOWN)==0)
	{
		motor(ELEVATOR, -25);
		motor(ELEVATORTWO,-25);
	}
	ao();
	msleep(400);
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_DOWN);
	msleep(400);
}
/*..............................................Functions End..............................................*/
int main(){
	create_connect();
	create_setup();
	//light_start(LIGHTSTART);
	shut_down_in(119.);  start();
	enable_servos(); 
	servo_set(ARM,ARM_DOWN,0.3);
	servo_set(HANGER,HANGER_CLOSE,0.3);
	
	create_right(82,0,250);
	create_forward(390, 400);// (distance in mm,speed)
	create_left(82,0,250);
	create_forward(480, 300);//scrape against pipe is deliberate
	create_stop(); arm_lift();
	create_block();

	

	create_left(86,0,250);//face the rack
	create_forward(100,200);
	create_backward(290,200);
	create_forward(75,200);
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	servo_set(ARM,ARM_UMID,0.3);
	wait_till(110); now();
	servo_set(ARM,ARM_UP,0.3);
	create_forward(150,100);
	//Temp End Code
	disable_servos(); printf("Done\n");
}
