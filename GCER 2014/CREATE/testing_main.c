// Created on Sun June 22 2014

#define arm_low

//#define front_arm 0
//#define hanger_holder 3
//#define elevator_motor 0
//#define elevator_sensor 15

//#define front_arm_top_position 150
//#define front_arm_bot_position 1900
//#define hanger_holder_closed 0
//#define hanger_holder_open 1365 //#include bricks some stuff, perhaps look at later this is copied from createDrive.h

//#define full_arm_lift_test
//#define elevator_lift_test
//#define full_arm_drop_test
//#define elevator_drop_test
//#define front_arm_lift_test
#define ARM 0
#define HANGER 3
#define ELEVATOR 0
#define ELEVATORTWO 2
#define SENSOR_UP 15
#define SENSOR_DOWN 14
#define ARM_UP 150
#define ARM_UMID 700
#define ARM_DMID 1200
#define ARM_DOWN 2000
#define HANGER_CLOSE 0
#define HANGER_OPEN 1365
void arm_lower(){
	//le elevator
	while(digital(SENSOR_DOWN)==0)
	{
		motor(ELEVATOR, -10);
		motor(ELEVATORTWO,-10);
	}
	ao();
	msleep(400);
	//arm
	enable_servo(ARM);
	set_servo_position(ARM,ARM_DOWN);
	msleep(400);
}
/** TESTING PARTS OF MAIN.C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! **/

/**============================================================================**/
#ifdef arm_low
int main(){enable_servos(); arm_lower(); disable_servos();}
#endif

#ifdef drive_path_test
int main()
{
	shut_down_in(119.);
	create_connect();
	enable_servos();
	set_servo_position(hanger_holder, hanger_holder_closed);
	full_arm_lift(); //lift at start to clear room for LINK bot; make this raise while driving; SERVO TURNS OFF FOR SOME REASON
	msleep(100);
	printf("1 is ON\nBEFORE RIGHT\n<<<%d>>>\n", get_servo_enabled(front_arm));//DEBUG
	create_right(82,0,100); //(angle,radius,speed); 82deg IS a 90deg turn; turn create_direct is much more of a hassle
	msleep(200);
	printf("1 is ON\nAFTER RIGHT\n<<<%d>>>>\n", get_servo_enabled(front_arm));//DEBUG
	create_backward(500, 100);// (distance,speed); distance is in mm
	msleep(500);
	create_left(85,0,100);// with the arm up deg changes
	msleep(200);
	create_backward(850, 100);
	msleep(200);
	create_right(90,0,100);
	msleep(200);
	/*create_backward(100, 100);*/
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

