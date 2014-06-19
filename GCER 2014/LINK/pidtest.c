#ifdef PIDTEST
#include "template.h"

int main() { 
	//correct constants are: 25, 0.01, 0.01
	double K_p = 20.0;
	double K_i = 0.0;
	double K_d = 0.1;
	enable_servos();
	camera_open();

	while(!c_button()) {
		WAIT(a_button() || b_button() || c_button());
		if (a_button()) K_p+=5;
		else if (b_button()) K_p-=5;
		else break;
		printf("K_p -> %f\n", K_p);
		WAIT(!(a_button() || b_button() || c_button()));
	}
	
	printf("K_p is %f\n", K_p);
	printf("=====MOVING TO K_i=====\n");
	msleep(2000);
	while(!c_button()) {
		WAIT(a_button() || b_button() || c_button());
		if (a_button()) K_i+=0.01;
		else if (b_button()) K_i-=0.01;
		else break;
		printf("K_i -> %f\n", K_i);
		WAIT(!(a_button() || b_button() || c_button()));
	}
	
	printf("K_i is %f\n", K_i);
	
	printf("=====MOVING TO K_d=====\n");
	msleep(2000);
	while(!c_button()) {
		WAIT(a_button() || b_button() || c_button());
		if (a_button()) K_d+=0.01;
		else if (b_button()) K_d-=0.01;
		else break;
		printf("K_d -> %f\n", K_d);
		WAIT(!(a_button() || b_button() || c_button()));
	}
	printf("K_d is %f\n", K_d);
	msleep(1000);
	
	/*	
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

	double integral = 0.0;
	double derivative = 0.0;
		
	double prev_error = 0.0; 
		
	while(1) {
		camera_update();
		printf("area of nearest blob -->  %d\n", cam_area(0));
		if(cam_area(0)!=0) {
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
		else {
			printf("!!!!!!!!!!!!!!!!!!!!!!! NO BLOB IN SIGHT !!!!!!!!!!!!!!!!!!!!!!!"); 
			msleep(2000);
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
			
		double E = atan(
			((double)(-1*(x_blob-x_rob)))
			/((double)(y_blob-y_rob))
		);
		
		//this is a bit sketchy but it should work
		if(prev_error==0) prev_error = E;
			
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		motor(MOT_LEFT, -1*((K_p*E)+(integral*K_i)+(derivative*K_d)));
		motor(MOT_RIGHT, (K_p*E)+(integral*K_i)+(derivative*K_d));
		
		msleep(1);
		printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
	}
}
//#endif
