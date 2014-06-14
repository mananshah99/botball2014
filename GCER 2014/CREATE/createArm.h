// Created on Fri June 13 2014 by Howard Wang
//Arm libraries: to lift the arm for the Create

#include createDrive.h
#include singing.h
#include drive.h

#define front_arm 0
#define hanger_holder 1
#define elevator_left_motor 0
#define elevator_right_motor 1
#define elevator_sensor 0

#define front_arm_top_position ?
#define front_arm_bot_position ?


void full_arm_lift()
{
	enable_servos();
	set_servo_position(front_arm ,front_arm_top_position);
	msleep(300);
	elevator_lift();
}


void elevator_lift()
{
	while(digital(elevator_sensor)==1);
	{
		motor(elevator_left_motor,100);
		motor(elevator_right_motor,100);
		msleep(500);
	}
	ao();
}

void full_arm_drop()
{
	enable_servos();
	elevator_drop();
	set_servo_position(front_arm ,front_arm_bot_position);
	msleep(300);
}

void elevator_drop()
{
	while(digital(elevator_sensor)==1);
	{
		motor(elevator_left_motor,-100);
		motor(elevator_right_motor,-100);
		msleep(500);
	}
	ao();
}




