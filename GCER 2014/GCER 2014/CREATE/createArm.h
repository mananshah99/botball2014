// Created on Fri June 13 2014 by Howard Wang
//library: to lift the arm for the Create, and also other stuff for create

#include "template.h"

#define front_arm 0
#define hanger_holder 3
#define elevator_motor 0
#define elevator_sensor 15

#define front_arm_top_position 150
#define front_arm_bot_position 1900
#define hanger_holder_closed 0
#define hanger_holder_open 1365

void full_arm_lift()
{
	front_arm_lift();
	elevator_lift();
}


void elevator_lift()
{
	printf("%d\n", digital(elevator_sensor));
	while(digital(elevator_sensor)==0)
	{
		motor(elevator_motor, 80);
		msleep(500);
	}
	ao();
}

void full_arm_drop()
{
	elevator_drop();
	front_arm_drop();
	ao();
}

void elevator_drop()
{
	motor(elevator_motor,-20);
	msleep(2500);
	ao();
	msleep(300);
}

void front_arm_lift()
{
	set_servo_position(front_arm, front_arm_top_position);
	msleep(200);
}

void front_arm_drop()
{
	set_servo_position(front_arm ,front_arm_bot_position);
}

void hanger_release()
{
	create_backward(50, 50);
	msleep(100);
	set_servo_position(hanger_holder, hanger_holder_open);
	msleep(200);
	motor(elevator_motor,-20);
	msleep(500);
	ao();
	create_forward(100,50);
	ao();
}


