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
#define ARM_UMID 700
#define ARM_DMID 1200
#define ARM_DOWN 2100 //used to be 2000 b4 new servo
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
	set_servo_position(ARM,ARM_DOWN);*/
	/**wait_for_light(LIGHTSENSOR);**/ /** PUT BACK **/
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
	set_servo_position(HANGER,HANGER_CLOSE);
	printf("GO!");
	disable_servos();
	sleep(20);//WAIT FOR LINK
	enable_servos();
	
	create_right(85,0,150);
	create_backward(50,50);//square up
	create_stop();
	create_wait_time(10);
	create_block();
	
	
	
	create_forward(400, 200);// (distance in mm,speed)
	create_stop();
	arm_lift();
	create_block();//out of base

	create_left(82,0,150);
	create_forward(314, 200);//scrape against pipe is deliberate
	//the forward used to be 310
	create_stop();
	create_left(85,0,150);//face the rack; IMPORTANT

	create_forward_until_lbump();
	create_stop();
	//create_wait_time(5);
	create_left(2,0,100);//ANGLE THE FIRST HANGER DROP
	create_backward(240,150);
	create_block();//At the Pipes
	msleep(100);
	
	set_servo_position(HANGER,HANGER_OPEN);
	set_servo_position(ARM,ARM_UMID);
	create_forward_until_lbump();
	create_block(); //scored and backed away from hangers
	
	wait_till(55.);
	arm_lower();
	create_right(2,0,100);//COMPENSATE ANGLE TOWARD BLUE HANGER
	create_backward(320,100);//WITHOUT THE DOUBLE FORWARD
	create_block();
	
	/*create_backward(215,200);//approach blue hanger (facing away)
	create_left(5,0,100);//turn
	create_block();
	
	msleep(100);
	create_backward(40,150);
	create_block();*/
	
	set_servo_position(HANGER,HANGER_CLOSE);
	//msleep(50);
	//create_backward(10,150);
	//create_block();
	
	set_servo_position(ARM,ARM_DMID);
	msleep(50);
	set_servo_position(ARM,ARM_DOWN);//get blue
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
	
	set_servo_position(ARM,ARM_UMID);
	//create_left(2,0,100);//turn
	create_backward(340,200);//approach for score
	create_block();
	
	set_servo_position(ARM,ARM_UP);
	create_backward(5,200);//jerk to lift arm
	create_stop();
	create_wait_time(10);
	//create_right(18,0,70);//turn; push hangers out of way
	//create_left(14,0,70);//reset
	create_forward(200,200);//score blue hanger
	create_block();
	//blue hanger now scored (on pipe), moving to second blue hanger and dropping 1st off
	
	msleep(100);
	set_servo_position(HANGER,HANGER_OPEN);
	set_servo_position(ARM,ARM_UMID);
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
	set_servo_position(ARM,ARM_DMID);
	create_block();
	
	//arm_lower();
	set_servo_position(ARM,ARM_DOWN);
	create_backward(275,175);//collect 2nd blue
	create_block();
	
	set_servo_position(HANGER,HANGER_CLOSE);
	set_servo_position(ARM,ARM_DMID);
	create_forward(375,200);
	create_block();
	
	arm_lift();
	create_right(2,0,150);
	create_backward(400,200);//score 2nd blue
	create_block();
	
	set_servo_position(HANGER,HANGER_OPEN);
	set_servo_position(ARM,ARM_UMID);
	create_forward(700,300);
	create_block();
	printf("%d\n", seconds()-time);
	
	disable_servos(); ao(); printf("Done\n");
}
