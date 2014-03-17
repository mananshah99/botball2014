#include "./createDrive.h"
#include "./createSlow.h"
#include "./generic.h"

#define FULL 100

#define SERV_ARM 1
void arm_close(){
	set_servo_position(SERV_ARM,2040);
}
void arm_open(){
	set_servo_position(SERV_ARM,646);
}
void arm_half()
{
	set_servo_position(SERV_ARM,1800);
}

#define MOT_ARM  3 //the mot_arm that isn't the create
#define SEN_ARM() (digital(15))

void liftArm()
{
	fd(MOT_ARM);//fd(MOT_ARM2);
	create_motor_slow(80);
	WAIT(SEN_ARM());

	mrp(MOT_ARM,0,1000);
	create_motor_slow(10);
	msleep(1000);
	create_motor_slow(25);

	WAIT(SEN_ARM());
	ao();

	create_motor_slow(0);
	mrp(MOT_ARM,0,1000);
}

//bump functions
void forward_bump(c)
{
	do{ create_drive_direct(300,300); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	do{ create_drive_direct(-300,-300); }
	while(get_create_lbump()==0);
}

int main()
{
	create_connect();
	
	create_wait_time(20); //20 deciseconds for the link to pass
	create_drive_direct_dist(FULL,FULL,50); //50 centimeters
	
	//block here, square up, and get to the next box area
	forward_bump();
	create_block(); //finish the bump
	
	/**COLOR SORTING AND SERVO MOVEMENT HERE**/
	
	create_drive_direct_dist(-FULL,-FULL,50);
	
	/*
	 Angle is 87 because 90 degrees never works
	 Radius is 0 
	 Speed is 60 (too fast?)
	*/
	create_right(87,0,60);
	//drive to the other end of the board
	forward_bump();
	
	//TODO: Get the actual distance (replace 30)
	create_drive_direct_dist(-FULL,FULL,30);
	create_right(87,0,60);
	
	//next box area after squaring up
	printf("finished");
	create_disconnect();
	return 0;
}
