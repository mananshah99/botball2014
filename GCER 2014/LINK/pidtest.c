#ifdef PIDTEST
#include ".\template.h"
int main() { 
	int K_p = 0;
	enable_servos();
	camera_open();
	//A increases
	//B decreases
	//C starts
	while(!c_button()) {
		WAIT(!(a_button() || b_button()));
		WAIT(a_button() || b_button());
		int x = 0;
		if (a_button()) x+=.5;
		if (b_button()) x-=.5;
		printf("increasing by -> %d\n", x);
	}
	K_p += x;
	
	/*
	rem TURNING: 
	
	while the error is not within a certain EPSILON
		set the motor power (1) equal to (K_p)*(error)
		set the motor power (2) equal to -(K_p)*(error)
		sleep for 1ms
		update the camera image
		calculate the new error from the image
		set error equal to the new error
		loop again 
	end
	
	
	*/
	int x, y;
	int x_curr = 0;
	int y_curr = 0;
	while(1) {
		printf("area of nearest blob -->  %d\n", cam_area(0));
		x = get_object_center(0,0).x;  
		y = get_object_center(0,0).y;  
		double E = atan(y
		motor(MOT_LEFT, K_p)* E);
		motor(MOT_RIGHT, K_p* E);
}
#endif
