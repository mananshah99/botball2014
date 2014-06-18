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
		WAIT(a_button() || b_button() || c_button());
		if (a_button()) x+=5;
		else if (b_button()) x-=5;
		else break;
		printf("increasing by -> %f\n", x);
		WAIT(!(a_button() || b_button() || c_button()));;
	}
	printf("x is %f\n", x);
	K_p = x;
	printf("K_p is %f\n", K_p);
	
	/*
	 TURNING: 
	
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
	camera_update();
	while(1) {
		camera_update();
		printf("area of nearest blob -->  %d\n", cam_area(0));
		if(cam_area(0)!=0) {
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
		else {
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NO BLOB IN SIGHT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); 
			x_blob = 0;
			y_blob = 0;
		}
			
		double E = atan(
			((double)(-1*(x_blob-x_rob)))
			/((double)(y_blob-y_rob))
			);
		motor(MOT_LEFT, -1*K_p* E);
		motor(MOT_RIGHT, K_p* E);
		msleep(1);
		printf("E --> %f,    K_p --> %f\n", E, K_p);
	}
}
//#endif
