#define MAIN
#ifdef MAIN
#include "./template.h"
int main() {
	#define DEBUG // comment this out when in actual competition 
	
	/**	
	 * while the error is not within a certain EPSILON
	 *	set the motor power (1) equal to (K_p, K_i, K_d, etc. )*(error)
	 *	set the motor power (2) equal to -(K_p, K_i, K_d)*(error)
	 *	sleep for 1ms
	 * 	update the camera image
	 * 	calculate the new error from the image
	 * 	set error equal to the new error
	 * 	loop again 
	 * end
	**/
	
	//constants
	double K_p = 25.0;
	double K_i = 0.01;
	double K_d = 0.01;
	
	//enabling things
	enable_servos();
	camera_open();
	camera_update();
	
	//values (rob is robot) 
	int x_blob, y_blob;
	int x_rob = 91;
	int y_rob = -156;
	
	//for PID
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	//threshold value
	double EPSILON = 0.05;
		
	while(abs(E)>EPSILON) {
		camera_update();
		SHOW(printf("area of nearest blob -->  %d\n", cam_area(0)));
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
#endif
