#include "template.h"
void square_up(int distance){

	//P constant
	double Con = 20.0;
	
	// distance between IR sensors
	double dia = 0;
	
	//replace p with the correct values later
	int leftDistance = analog(int p);
	int rightDistance = analog(int p);
	
	//make returned values usable
	set_analog_pullup(p, 0);
	set_analog_pullup(p, 0);
	
	//acceptable difference between the distances
	int aDiff = 0.1;

	//difference between the distances
	int diff = abs(leftDistance-rightDistance);
	
	//squares robot
	while (diff > aDiff) {
		diff = abs(leftDistance-rightDistance);
		double AE = atan(diff/dia));
		//turn robot untill square
		motor(MOT_LEFT,con*AE));
		motor(MOT_RIGHT,-1*con*AE);
	}
	
	//moves robot to correct distance
	while ((leftDistance+rightDistance)/2 != distance){
		//move robot forward or back
	}
}
