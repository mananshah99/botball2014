// Created on Sat June 14 2014 by Howard Wang

#include "./createArm.h"
//a lot of #defined variables are in "createArm.h"

#define

/** Create is facing backwards, so forward commands move the create backwards **/

#define main
//#define full_arm_lift_test
//#define elevator_lift_test

/**=============================================================================**/

#ifdef main
int main()
{
	shut_down_in(119.);
	create_connect();
	enable_servos();
	set_servo_position(hanger_holder, hanger_holder_close);
	msleep(100);
	create_drive_left(50,50,90);
	msleep(200);
	create_backward(635, 100);
	msleep(200);
	front_arm_lift();
	msleep(300);
	create_drive_right(50,50,90);
	msleep(100);
	create_backward(635, 100);
	msleep(200);
	create_drive_right(50,50,90);
	msleep(200);
	create_backward(100, 100);
	msleep(200);
	create_drive_left(50,50,180);
	msleep(200);
	elevator_lift();
	msleep(200);
	create_backward(100,50);
	msleep(200);
	hanger_release();
	msleep(200);
	
	
}
#endif


/**=============================================================================**/


#ifdef full_arm_lift_test
int main()
{
	enable_servos();
	create_connect();
	full_arm_lift();
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

