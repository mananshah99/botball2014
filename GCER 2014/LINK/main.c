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
	
	//1534, 100
	
	//constants
	double K_p = 25.0;
	double K_i = 0.03;
	double K_d = 0.01;
	
	//enabling things
	
	enable_servos();
	camera_open();
	camera_update();
	
	//values (rob is robot) 
	int x_blob, y_blob;
	int x_rob = 100;  
	int y_rob = -113; //old: 156
	
	int x_target = x_rob; //new: 100
	int y_target = 69; //new: 68 (old = 25)
	
	//for PID
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	//threshold value
	double EPSILON = 0.02;
	double E = 100;
		
	//init
	set_servo_position(1, 1584);
	while(1/*!in_range(E, 0, EPSILON) || !in_range(E, 0, -EPSILON)*/) {
		ghj: 
		camera_update();
		SHOW(printf("area of nearest blob -->  %d\n", cam_area(0)));
		if(cam_area(0)!=0) {
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
		else {
			SHOW(printf("!!!!!!!!!! NO BLOB IN SIGHT !!!!!!!!!!!!\n")); 
			goto ghj;
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
		
		if(E<=EPSILON && E>=-EPSILON) 
		{
			ao();
			break;
		}
		
	}
	printf("done with angle correction");
	beep();
	msleep(1000);
	
	///////////driving/////////////
	
	camera_update();
	do{
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);
	
	E = -y_blob + y_target;
	//11 used to be 10.4 here
	backward(-(((double)E)*12)/1000.);
	/*
	K_p = 1.0;
	K_i = 0.1;
	K_d = 0.001;	

	integral = 0.0;
	derivative = 0.0;
	prev_error = 0.0; 

	while(1) {
		camera_update();
		printf("area of nearest blob -->  %d\n", cam_area(0));
		if(cam_area(0)!=0) {
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
		else {
			printf("!!!!!!!!!! NO BLOB IN SIGHT !!!!!!!!!!!!\n"); 
			msleep(2000);
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
			
		double E = -y_blob+y_target;
		
		//this is a bit sketchy but it should work
		if(prev_error==0) prev_error = E;
			
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		int spd = (K_p*E)+(integral*K_i)+(derivative*K_d);
		spd = (spd > 60 ? 60 : spd);
		motor(MOT_LEFT, spd);
		motor(MOT_RIGHT, spd);
		
		msleep(1);
		printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		
		if(E<=EPSILON && E>=-EPSILON) {
			ao();
			break;
		}
	}*/
	printf("[log] done overall");
	msleep(1000);
	
	//dropping 
	set_servo_position(1, 200);
	msleep(1500);
	//shaking
	forward(.1);
	msleep(100);
	backward(.2);
	msleep(100);
	forward(.1);
	msleep(100);
	set_servo_position(1, 1800);
	msleep(2000);
	printf("[log] finished tribble pickup");
	disable_servos();
}
#endif
