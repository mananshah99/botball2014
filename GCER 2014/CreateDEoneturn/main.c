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
//#define ARM_UMID 700 //SERVO VALUES CHANGED SO NOT WORKING ANYMORE
#define ARM_UMID1 400
#define ARM_DMID 1000	//new servo, old value 1200
#define ARM_DOWN 2000
#define HANGER_CLOSE 0
#define HANGER_OPEN 1365
#define LIGHTSENSOR 7
/*..............................................Functions Begin..............................................*/
void create_setup(){
	create_backward(10,50);
	create_wait_time(1);
	create_forward(15,50);
	create_left(85,0,50);
	create_forward(50,50);
	create_block();
	msleep(1000);
	enable_servo(ARM);
	servo_set(ARM,ARM_DOWN,0.3);
	wait_for_light(LIGHTSENSOR);
	/*printf("Press A to start");
	while(a_button()==0){ //MANUAL START
		msleep(1);
	}*/
}
void arm_lift(){
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_UP);
	msleep(100);
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
	msleep(100);
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_DOWN);
	msleep(100);
}
/*..............................................Functions End..............................................*/
int main(){
	create_connect();
	create_full();
	create_setup();
	shut_down_in(119.);  start(); printf("GO!");
	enable_servos(); 
	servo_set(HANGER,HANGER_CLOSE,0.3);
	
	servo_set(ARM,ARM_DMID,0.3);//to protect it from hitting the pipe
	create_left(80,0,200);//ADJUST
	create_backward(350, 300);// OUT OF BASE DISTANCE
	create_left(37,0,250);//ANGLE TOWARD RACK
	create_backward(320, 300);//FORWARD TOWARD RACK
	create_stop(); 
	arm_lift();
	create_block();
	
	msleep(100);
	create_backward(150,300);
	create_forward(150,200);
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	servo_set(ARM,ARM_UMID1,0.3);
	
	wait_till(105); now();
	servo_set(ARM,ARM_UP,0.3);
	create_forward(300,150);
	disable_servos(); ao();
	printf("Done\n");
}
