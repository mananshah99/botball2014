//#define aldsks
#ifdef aldsks
#include "template.h"
//>>>>>>> 469fb0234cd4a8bda8084755da5cd752f78be533
int mainsqr() {
	
	square_up_angle();
	square_up_distance(300);
	square_up_angle();
	square_up_distance(300);
	square_up_angle();
	
}

void square_up_angle(){
	//P constant
	double Con = 40.0;
	int leftDistance = analog_et(2);
	int rightDistance = analog_et(3);
	
	//make returned values usable
	set_analog_pullup(2, 0);
	set_analog_pullup(3, 0);
	
	//acceptable difference between the distances
	int aDiff = .1;
	
	// distance between IR sensors
	double dia = 430;//200units = about 3.5 in they are 7.5 in apart

	//difference between the distances
	int diff = leftDistance-rightDistance;
	double AE = 0;
	
		leftDistance = analog_et(2);
		rightDistance = analog_et(3);
		diff = leftDistance-rightDistance;
		//squares robot
		while (abs(diff) > aDiff) {
			leftDistance = analog_et(2);
			rightDistance = analog_et(3);
			diff = leftDistance-rightDistance;
			AE = atan(diff/dia);
			//turn robot until square
			printf("left: %d\n",leftDistance);
			printf("right: %d\n",rightDistance);
			motor(MOT_LEFT,-1*Con*AE);
			motor(MOT_RIGHT,Con*AE);
			//msleep(1);
		}
	
	
}

void square_up_distance(int distance){
	//distance is not in inches do testing to find out for each case distance of 300 is about 3 inches
	//for our purposes it is a small number for a big distance but it is not a linear value so we can't just convert it into inches
	
	//motor power for straight part of the squareup
	int sqpow = 23;
	
	int leftDistance = analog_et(2);
	int rightDistance = analog_et(3);
	
	//make returned values usable
	set_analog_pullup(2, 0);
	set_analog_pullup(3, 0);
	
	//acceptable difference between the distances
	int aDiff = .1;

	
		//moves robot to correct distance
		while (abs((leftDistance+rightDistance)/2-distance) > aDiff){
			leftDistance = analog_et(2);
			rightDistance = analog_et(3);
			printf("leftf: %d\n",leftDistance);
			printf("rightf: %d\n",rightDistance);
			if((leftDistance+rightDistance)/2 < distance){
				//move robot forward
				motor(MOT_LEFT,sqpow);
				motor(MOT_RIGHT,sqpow);
			} else {
				//move robot backward
				motor(MOT_LEFT,-sqpow);
				motor(MOT_RIGHT,-sqpow);
			}
			msleep(1);
		}
}
	#endif
