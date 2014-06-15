// Created on Sat June 14 2014 by Howard Wang

#include "./createArm.h"
//a lot of #defined variables are in "createArm.h"

//#define main
#define arm_lift
#define elevator_lift_test

#ifdef main
int main()
{
	shut_down_in(119.);
	create_connect();
	enable_servos();
	create_drive_right(50,50,90);
	msleep(100);
	create_drive_direct_dist(100, 100, 635);
	msleep(100);
	create_drive_left(50,50,90);
	msleep(100);
}
#endif

/******************************************************************************************************************************/

#ifdef full_arm_lift
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

