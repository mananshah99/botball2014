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
void create_setup(){
	create_backward(10,50);
	create_forward(10,50);
	create_left(88,0,50);
	create_forward(50,50);
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
/*..............................................Functions End..............................................*/
int main()
{
	//wait_for_light(LIGHTSTART);
	shut_down_in(119.);
	create_connect();
	create_setup();
	//create_forward(10,10);
	create_block();
	
	enable_servos();
	servo_set(HANGER,HANGER_CLOSE,0.3);
	create_right(82,0,100); //(angle,radius,speed); 82 ~ 90deg
	create_forward(500, 100);// (distance in mm,speed)
	create_lineup();
	create_backward(150,100);
	create_left(82,0,100);
	create_forward(300, 100);
	create_left(90,0,100);//face the rack
	create_backward(200,100);
	arm_lift();//armlift while robot moves
	create_block();//At the Pipes
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	while(get_create_lbump() == 0){
		create_drive_direct(100,100);//(r_speed,l_speed)
	}
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
	
	while(get_create_lbump() == 0){
		create_drive_direct(100,100);//(r_speed,l_speed)
	}
	create_block();
	
	//create_forward(210,200);//away
	create_left(25,0,100);//turn for lift
	create_block();
	
	arm_lift();
	servo_set(ARM,ARM_UMID,0.5);
	create_right(7,0,100);//partial reset angle
	create_backward(310,100);//approach for score
	create_block();
	
	servo_set(ARM,ARM_UP,0.5);
	create_right(18,0,100);//reset angle
	create_left(5,0,50);//turn
	create_forward(100,100);//score blue hanger
	create_right(5,0,100);//reset angle
	create_block();
	
	servo_set(HANGER,HANGER_OPEN,0.3);
	msleep(500);
	create_right(5,0,100);//reset angle
	create_block();
	
	create_drive_direct_dist(100,80,25);
	create_drive_direct_dist(80,100,25);
	//Temp End Code
	sleep(10); disable_servos(); printf("Done\n");
}
