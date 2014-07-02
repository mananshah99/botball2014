/*#include "template.h"
=======
#ifdef aldsks
#include "template.h"
>>>>>>> 469fb0234cd4a8bda8084755da5cd752f78be533
void square_up(int distance){
	//distance is not in inches do testing to find out for each case distance of 300 is about 3 inches
	
	//note don't know if sensor outputs a small number for a big distance or opposite code might have to be
	//changed because of this
	//for our purposes it is a small number for a big distance but it is not a linear value so we can't just convert it into inches

	//P constant
	double Con = 20.0;
	
	//motor power for straight part of the squareup
	int sqpow = 30
	
	// distance between IR sensors
	double dia = 430;//200units = about 3.5 in they are 7.5 in apart
	
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
	
	//allows it to loop so that it can recorect angle and distance 
	//shouldn't add time if it gets to the right position
	for (i=0;i<2;i++)
	{
	
		//squares robot
		while (diff > aDiff) {
			diff = abs(leftDistance-rightDistance);
			double AE = atan(diff/dia));
			//turn robot until square
			motor(MOT_LEFT,con*AE));
			motor(MOT_RIGHT,-1*con*AE);
		}
	
		//moves robot to correct distance
		while (abs((leftDistance+rightDistance)/2-distance) < aDiff){
			if((leftDistance+rightDistance)/2 < distance){
				//move robot forward
				motor(MOT_LEFT,sqpow));
				motor(MOT_RIGHT,sqpow);
			} else {
				//move robot backward
				motor(MOT_LEFT,-sqpow));
				motor(MOT_RIGHT,-sqpow);
			}
		}
	}
}
	#endif
*/