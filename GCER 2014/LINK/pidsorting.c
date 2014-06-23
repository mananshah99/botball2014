//#define PID
#ifdef PID
#include "./template.h"
int main() {
	enable_servos();
	camera_open();
	int x, y;
while(1){	
	x = get_object_center(0,0).x;  
	y = get_object_center(0,0).y;  
	/*
	int x_diff = abs(115-x);
	int y_diff = abs(91-y);
	right(atan(x_diff/y_diff)+90);
	forward(sqrt(x_diff*x_diff+y_diff*y_diff));
	*/
	printf("%d    %d\n", x, y);
	camera_update();
}
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
}
#endif
