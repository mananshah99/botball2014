// Created on Sat June 14 2014 by Howard Wang
// Brandon was here

#include "./createArm.h"
//a lot of #defined variables are in "createArm.h"

//#defines go here

/** Create is facing backwards, so forward commands move the create backwards **/

//#define MAIN
#define full_arm_lift_test
//#define elevator_lift_test
//#define full_arm_drop_test
//#define elevator_drop_test
//#define front_arm_lift_test

/**=============================================================================**/

#ifdef MAIN
int main()
{
	shut_down_in(119.);
	create_connect();
	enable_servos();
	set_servo_position(hanger_holder, hanger_holder_closed);
	msleep(100);
	create_drive_direct_left(50,50,90);
	msleep(200);
	create_backward(635, 100);
	msleep(200);
	full_arm_lift();
	msleep(300);
	create_drive_direct_right(50,50,90);
	msleep(100);
	create_backward(635, 100);
	msleep(200);
	create_drive_direct_right(50,50,90);
	msleep(200);
	create_backward(100, 100);
	msleep(200);
	create_drive_direct_left(50,50,180);
	msleep(200);
	create_backward(50,50);
	msleep(200);
	hanger_release();
	msleep(200);
	printf("Recovering!\n");
	set_servo_position(front_arm, front_arm_bot_position);
	msleep(200);
	motor(elevator_motor,-20);
	msleep(2000);
	ao();
	msleep(200);
	
	/** BLUE HANGER TIME !!!!!!!!!!!!!!!!!! **/
	
	printf("Blue hanger time!\n");
	create_drive_direct_right(50, 50, 270);
	msleep(100);
	create_backward(20,50);
	msleep(100);
	create_drive_direct_right(50, 50, 90);
	msleep(100);
	create_backward(100,50);
	msleep(500);
	set_servo_position(hanger_holder, hanger_holder_closed);
	msleep(100);
	motor(elevator_motor,-20);
	msleep(300);
	ao();
	msleep(100);
	create_forward(50,50);
	msleep(50);
	create_forward(50,100);
	full_arm_lift();
	msleep(100);
	hanger_release();
	msleep(100);
	motor(elevator_motor,20);
	msleep(300);
	ao();
	full_arm_drop();
	msleep(200);
	create_drive_direct_right(50, 50, 90);
	msleep(100);
	create_backward(50, 50);
	msleep(100);
	
	
	
	
	
	
	printf("DONE\n");
	ao();
	create_disconnect();
}
#endif


/**============================================================================**/


#ifdef full_arm_lift_test
int main()
{
	enable_servos();
	full_arm_lift();
	ao();
}
#endif

#ifdef elevator_lift_test
int main()
{
	elevator_lift();
}
#endif

#ifdef full_arm_drop_test
int main
{
	full_arm_drop();
}
#endif

#ifdef elevator_drop_test
int main
{
	elevator_drop();
}
#endif

#ifdef front_arm_lift_test
int main()
{
	enable_servos();
	front_arm_lift();
	int x = get_servo_position(front_arm);
	printf("%d\n", x);
	ao();
}
#endif



