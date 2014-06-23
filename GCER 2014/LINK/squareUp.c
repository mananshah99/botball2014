#include "template.h";
int main(int distance){

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
	
	while (diff > aDiff) {
		
	}
}
