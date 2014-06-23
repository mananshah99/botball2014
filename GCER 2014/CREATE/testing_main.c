// Created on Sun June 22 2014

#define drive_path_test
//#define full_arm_lift_test
//#define elevator_lift_test
//#define full_arm_drop_test
//#define elevator_drop_test
//#define front_arm_lift_test

/** TESTING PARTS OF MAIN.C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! **/

/**============================================================================**/

#ifdef drive_path_test
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
}
#endif






							/** ARM TESTING **/
/** ========================================================================= **/
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
	enable_servos();
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
								/** END OF ARM TESTING **/
/** ============================================================================**/

