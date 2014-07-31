#include "createDrive.h"
#include "generic.h"
//Start: Monday 23 June 2014
//Create 2.1 working version backed-up
//Create 2.2 started on Monday 7 July 2014
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
	create_forward(15,50);
	create_left(85,0,50);
	create_forward(50,50);
	create_block();
	msleep(1000);
	/*enable_servo(ARM);
	servo_set(ARM,ARM_DOWN,0.3);*/
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
		motor(ELEVATORTWO,75);
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
void create_forward_until_lbump(){
	while(get_create_lbump() == 0){
		create_drive_direct(150,150);//(r_speed,l_speed)
	}
}
void create_forward_until_rbump(){
		while(get_create_rbump() == 0){
		create_drive_direct(150,150);//(r_speed,l_speed)
	}
}
/*..............................................Functions End..............................................*/
int main()
{
	create_connect();
	create_full();
	create_setup();
	shut_down_in(119.); float time = seconds(); start();
	enable_servos();
	servo_set(HANGER,HANGER_CLOSE,0.3);
	printf("GO!");
	disable_servos();
	sleep(16);//WAIT FOR LINK, used to be 20
	enable_servos();
	
	servo_set(ARM,ARM_DMID,0.3);//to protect it from hitting the pipe
	create_right(85,0,150);//hits pvc pipe, causes problems
	create_backward(50,50);//square up
	create_stop();
	create_wait_time(10);
	create_block();
	
	
	
	create_forward(390, 200);// (distance in mm,speed), used to be 400
	create_stop();
	arm_lift();
	create_block();//out of base

	create_left(82,0,150);
	create_forward(317, 200);//scrape against pipe is deliberate
	//the forward used to be 310
	create_stop();
	create_left(86,0,150);//face the rack; IMPORTANT
	//used to be 85 degrees

	create_forward_until_lbump();
	create_stop();
	//create_wait_time(5);
	create_left(2,0,100);//ANGLE THE FIRST HANGER DROP
	create_backward(240,150);
	create_block();//At the Pipes
	msleep(100);
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	servo_set(ARM,ARM_UMID1,0.5); //now slower
	create_forward_until_lbump();
	create_block(); //scored and backed away from hangers
	
	wait_till(55.);
	arm_lower();
	create_right(5,0,100);//COMPENSATE ANGLE TOWARD BLUE HANGER
	create_backward(310,100);//WITHOUT THE DOUBLE FORWARD
	//used to be 320
	create_block();
	
	/*create_backward(215,200);//approach blue hanger (facing away)
	create_left(5,0,100);//turn
	create_block();
	
	msleep(100);
	create_backward(40,150);
	create_block();*/
	
	servo_set(HANGER,HANGER_CLOSE,0.5);
	//msleep(50);
	//create_backward(10,150);
	//create_block();
	
	servo_set(ARM,ARM_DMID,0.5);
	msleep(50);
	servo_set(ARM,ARM_DOWN,0.5);//get blue
	create_forward(10,150);
	create_left(2,0,100);//reset angle
	create_block();
	
	create_forward_until_lbump();
	create_block();
	//get out
	
	create_right(265,0,150);//270
	create_backward(100,175);//OFFSET
	create_block();
	
	create_right(80,0,150);//reset angle 
	create_forward(50,200);
	create_stop();
	arm_lift();
	create_block();
	
	servo_set(ARM,ARM_UMID1,0.5);
	//create_left(2,0,100);//turn
	create_backward(340,200);//approach for score
	create_block();
	
	servo_set(ARM,ARM_UP,0.5);
	create_backward(5,200);//jerk to lift arm
	create_stop();
	create_wait_time(10);
	//create_right(18,0,70);//turn; push hangers out of way
	//create_left(14,0,70);//reset
	create_forward(200,200);//score blue hanger
	create_block();
	//blue hanger now scored (on pipe), moving to second blue hanger and dropping 1st off
	
	msleep(100);
	servo_set(HANGER,HANGER_OPEN,0.3);
	servo_set(ARM,ARM_UMID1,0.3);
	msleep(500);
	create_forward_until_rbump();
	create_block();
	//moving again to second blue hanger
	
	create_right(82,0,150);
	create_drive_direct(-100,-100);//square up one
	create_wait_time(20);
	create_forward(145,200);//line up for 2nd 
	create_right(82,0,150);
	create_drive_direct(-100,-100);//square up two
	create_wait_time(15);
	create_stop();
	create_forward(100,150);
	create_left(176,0,150);
	create_backward(260,175);//approach 2nd 
	create_stop();
	arm_lower();
	servo_set(ARM,ARM_DMID,0.3);
	create_block();
	
	//arm_lower();
	servo_set(ARM,ARM_DOWN,0.3);
	create_backward(275,175);//collect 2nd blue
	create_block();
	
	servo_set(HANGER,HANGER_CLOSE,0.3);
	servo_set(ARM,ARM_DMID,0.5);
	create_forward(375,200);
	create_block();
	
	arm_lift();
	create_right(2,0,150);
	create_backward(400,200);//score 2nd blue
	create_block();
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	servo_set(ARM,ARM_UMID1,0.3);
	create_forward(700,300);
	create_block();
	printf("%d\n", seconds()-time);
	
	disable_servos(); ao(); printf("Done\n");
}
