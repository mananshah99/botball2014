#include "slowservo.h"
int main() { 
	enable_servos();
	set_servo_position(1,1500);
	sleep(1);
	servo_slow(1,400,20);
	sleep(5);
	disable_servos();
}

