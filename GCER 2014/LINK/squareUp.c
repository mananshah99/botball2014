//#define aldsks
#ifdef aldsks
#include "template.h"
int main() {
	
	square_up(300);
	
}

void square_up(int distance){
	//distance is not in inches do testing to find out for each case distance of 300 is about 3 inches
	
	//note don't know if sensor outputs a small number for a big distance or opposite code might have to be
	//changed because of this
	//for our purposes it is a small number for a big distance but it is not a linear value so we can't just convert it into inches

	//P constant
	double Con = 20.0;
	
	//motor power for straight part of the squareup
	int sqpow = 30;
	
	// distance between IR sensors
	double dia = 430;//200units = about 3.5 in they are 7.5 in apart
	
	
	int leftDistance = analog_et(2);
	int rightDistance = analog_et(3);
	
	//make returned values usable
	set_analog_pullup(2, 0);
	set_analog_pullup(3, 0);
	
	//acceptable difference between the distances
	int aDiff = 0.1;

	//difference between the distances
	int diff = leftDistance-rightDistance;
	double AE = 0;
	/*int i = 0;
	//allows it to loop so that it can recorect angle and distance 
	//shouldn't add time if it gets to the right position
	for (i<2;i++;)
	{
	*/
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
			msleep(1);
		}
	
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
	//}
}
	#endif
