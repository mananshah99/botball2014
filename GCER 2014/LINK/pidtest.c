//#ifdef PIDTEST
#include "template.h"
int main() { 
	double K_p = 0.0;
	enable_servos();
	camera_open();
	//A increases
	//B decreases
	//C starts
	double x = 0.0;
	while(!c_button()) {
		WAIT(a_button() || b_button());
		if (a_button()) x+=0.5;
		else if (b_button()) x-=0.5;
		printf("increasing by -> %f\n", x);
		WAIT(!(a_button() || b_button()));;
	}
	printf("x is %f\n", x);
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
	int x_blob, y_blob;
	int x_rob = 91;
	int y_rob = -156;
	while(1) {
		printf("area of nearest blob -->  %d\n", cam_area(0));
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
		double E = atan(
			(-1*(x_blob-x_rob))
			/(y_blob-y_rob)
			);
		motor(MOT_LEFT, K_p* E);
		motor(MOT_RIGHT, K_p* E);
		msleep(1);
		printf("E --> %d,    K_p --> %d\n", E, K_p);
	}
}
//#endif
