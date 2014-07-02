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
//for create cliff sensors
#define lcliff get_create_lcliff_amt(.002)
#define rcliff get_create_rcliff_amt(.002)
/*..............................................Functions Begin..............................................*/
void create_setup(){
	create_backward(10,50);
	create_wait_time(1);
	create_forward(15,50);
	create_left(85,0,50);
	create_forward(50,50);
	create_block();
	msleep(1000);
	printf("Now in starting position, proceed to activate light start...\n");
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
void arm_lower(){
	//le elevator
	while(digital(SENSOR_DOWN)==0)
	{
		motor(ELEVATOR, -10);
		msleep(50);
	}
	motor(ELEVATOR,0);
	msleep(400);
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_DOWN);
	msleep(400);
}
void create_forward_until_lbump(){
	while(get_create_lbump() == 0){
		create_drive_direct(100,100);//(r_speed,l_speed)
	}
}
void create_forward_until_rbump(){
		while(get_create_rbump() == 0){
		create_drive_direct(100,100);//(r_speed,l_speed)
	}
}
/*..............................................Functions End..............................................*/
int main()
{
	//wait_for_light(LIGHTSTART);
	shut_down_in(119.);
	create_connect();
	create_setup();
	//light_start(LIGHTSTART);
	
	enable_servos();
	servo_set(HANGER,HANGER_CLOSE,0.3);
	arm_lift();//DO NOT lift as robot moves, it will break the Create
	create_right(85,0,100);
	create_backward(50,50);//square up
	create_stop();
	create_wait_time(10);
	create_forward(390, 100);// (distance in mm,speed)
	create_block();
	ao();

	create_left(82,0,100);
	create_forward(310, 100);//scrape against pipe is deliberate
	create_left(82,0,100);//face the rack
	create_backward(230,100);
	create_block();//At the Pipes
	printf("Now at the pipes and will drop off green/pink hangers\n");
	msleep(100);
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	create_forward_until_lbump();
	create_block();//Backed-up from Pipes
	
	arm_lower();
	create_backward(190,50);//approach blue hanger (facing away)
	create_left(5,0,100);//turn
	create_block();
	
	msleep(500);
	create_backward(45,50);
	create_block();
	
	servo_set(HANGER,HANGER_CLOSE,0.5);
	msleep(500);
	create_backward(10,100);
	create_block();
	
	servo_set(ARM,ARM_DMID,0.5);
	msleep(500);
	servo_set(ARM,ARM_DOWN,0.5);//get blue
	create_forward(10,100);
	create_right(5,0,100);//reset angle
	create_block();
	
	create_forward_until_lbump();
	create_block();
	
	create_left(80,0,100);//turn for lift
	create_backward(75,100);
	create_block();
	
	arm_lift();
	create_right(80,0,100);//reset angle
	create_forward(50,100);
	create_block();
	
	servo_set(ARM,ARM_UMID,0.5);
	create_left(2,0,100);//turn
	create_backward(340,100);//approach for score

	create_block();
	
	servo_set(ARM,ARM_UP,0.5);
	create_backward(5,200);//jerk to lift arm
	create_stop();
	create_wait_time(10);
	create_right(18,0,50);//turn; push hangers out of way
	create_left(14,0,50);//reset
	create_forward(200,100);//score blue hanger
	create_block();
	
	msleep(100);
	servo_set(HANGER,HANGER_OPEN,0.3);
	msleep(500);
	create_forward_until_rbump();
	create_block();
	
	create_right(82,0,100);
	create_backward(100,50);//square up one
	create_forward(230,100);//line up for 2nd 
	create_right(82,0,100);
	create_backward(50,50);//square up two
	create_stop(); create_wait_time(10);
	create_forward(100,100);
	create_right(172,0,100);
	create_backward(340,100);//approach 2nd blue
	create_block();
	//Temp End Code
	sleep(10); disable_servos(); printf("Done\n");
}
