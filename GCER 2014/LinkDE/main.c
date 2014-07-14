#define MAIN

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#ifdef MAIN
#include "./template.h"

double turned_angle;
int x_rob = 100;  
int y_rob = -113; //old: 156
int y_target = 69; //new: 68 (old = 25)

/*
 * 100 closed
 * 1300 open
 * port 3
*/
void correct_angle();
void correct_distance();
void square_up_distance(int distance);
void square_up_angle();
void line_squareup(double sensor_angle);
void tsort();

int basket_open = 1300;
int basket_closed = 171;
int basket_up = 400;
int basket_down = 75;

int main() {
	//#define DEBUG // comment this out when in actual competition 
	
	//enabling everything
	enable_servos();
	camera_open();
	camera_update();
	
	set_servo_position(1, 1300);	
	set_servo_position(2, basket_down);
	set_servo_position(3, basket_closed);

	
	//line_squareup(0.349);
	
	///---Drive 1---///
	
	forward(48);
	
	set_servo_position(3, basket_open);
	
	msleep(100);
	left(90, 0);
	forward(8);
	
	correct_angle();
	correct_distance();
	
	correct_angle();
	correct_distance();
	forward(5);
	set_servo_position(3, basket_closed);
	set_servo_position(1, 1300);
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -40);
	sleep(3);
	forward(5);
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -40);
	sleep(1);
	forward(12);
	right(90,0);
	forward(20);
	motor(MOT_LEFT, 68);
	motor(MOT_RIGHT, 60);
	sleep(2);
	backward(1);
	servo_slow(2,basket_up,4);
	right(80,0);
	forward(10);
	set_servo_position(3, basket_open);
	sleep(1);
	backward(40);
			
	disable_servos();
}

void line_squareup(double sensor_angle){
	//srad is distance from wheel to close sensor lrad is distance to far sensor
	//angle is angle between sensors
	
	int lsens = analog(1);
	int rsens = analog(0);
	
	double turn_angle = 0;
	double extra_turn = 0;
	
	int turn_motor = -1;
	
	int dark = 450;
	
	while(lsens >  dark && rsens > dark ) {
		motor(MOT_LEFT,50);
		motor(MOT_RIGHT,50);
		//move forward
		lsens = analog(1);
		rsens = analog(0);
		clear_motor_position_counter(MOT_RIGHT);
		clear_motor_position_counter(MOT_LEFT);
		if (lsens > dark){
			while(rsens < dark ) {
				printf("extra turn:%d\n",extra_turn);
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_RIGHT,50);
				mav(MOT_LEFT,0);
				//turn left by moving right forward
				turn_angle = sensor_angle - (CMtoBEMF * gmpc(MOT_RIGHT))/ks;
				extra_turn = turn_angle + (-2*atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle))));
			//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
			//srad is 12, lrad is 15
				turn_motor = MOT_RIGHT;
			}
		}
		if (rsens > dark){
			while(lsens < dark ) {
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_LEFT,50);
				mav(MOT_RIGHT,0);
				//turn right by moving left forward
				turn_angle = sensor_angle - (CMtoBEMF * gmpc(MOT_LEFT))/ks;
				extra_turn = turn_angle + (-2 * atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle))));
			//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
			//srad is 12, lrad is 15
			//for new values equation is(srad/lrad)*cos(a)=cos(a+turn_angle) a+turn_angle=extra_turn
				turn_motor = MOT_LEFT;
			}
			
		}
	}
	//turn extra
	mrp(turn_motor,50,(extra_turn * ks)/CMtoBEMF);
	while(lsens <  dark && rsens < dark ) {
		lsens = analog(1);
		rsens = analog(0);
		motor(MOT_LEFT,-50);
		motor(MOT_RIGHT,-50);
		//move backward
		//we could change this to forward to have it square up on the far side of the line.
	}
}

void correct_angle() {
	camera_update();

//constants
	double K_p = 26.0;
	double K_i = 0.03;
	double K_d = 0.01;	
	
	//values (rob is robot) 
	int x_blob, y_blob;
	int x_target = x_rob; //new: 100
	
	//for PID
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	//threshold value
	double EPSILON = 0.07;
	
	//init
	set_servo_position(1, 1584);
	prev_error = 0;
	while(1/*!in_range(E, 0, EPSILON) || !in_range(E, 0, -EPSILON)*/) {
		camera_update();
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y; 
		do{
			camera_update();
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}while(cam_area(0)==0);
		
		
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;
		
		printf("x : %d, y: %d\n");
		double E = atan(
			((double)(-1*(x_blob-x_rob)))
			/((double)(y_blob-y_rob))
		);
		
		//this is a bit sketchy but it should work
		if(prev_error==0) {
			prev_error = E;
			turned_angle = E;
		}
			
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		if(E*K_p<3 && E*K_p>0) E=3/K_p;
		if(E*K_p<0 && E*K_p>-3) E=-3/K_p;
				
		motor(MOT_LEFT, -1*((K_p*E)+(integral*K_i)+(derivative*K_d)));
		motor(MOT_RIGHT, (K_p*E)+(integral*K_i)+(derivative*K_d));
		
		msleep(1);
		//printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		
		if(E<=EPSILON && E>=-EPSILON) 
		{
			ao();
			break;
		}
		 
	}
	printf("[DONE] done with angle correction");
	beep();
	msleep(1000);
}

void correct_distance() {
	
	double K_p = 0.18;
	double K_i = 0;
	double K_d = 0;
		
	double x_blob, y_blob;
	double E = 0;	
	
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	double EPSILON = 2;
		
	
	//from other code updates v so that it can correct distance 
	
	camera_update();
	do{
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);
	
	//E = max(-y_blob + y_target, y_blob + y_target);
	E = y_blob - y_target;
	
	//11 used to be 10.4 here
	float v = ( ( (float) E) /8);

	/*********Threshold Camera Blob Issue*********/
	double THRESHOLD_DOUBLEBLOB = 350;
	while(1) {
		camera_update();
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y; 
		
		do{
			camera_update();
			if(cam_area(0)>THRESHOLD_DOUBLEBLOB) {
				//change x_blob to pick one of the two blobs
				x_blob = get_object_center(0,0).x - 10;
			}
			else x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}while(cam_area(0)==0);
			
		E = -y_blob+y_target;
		
		//this is a bit sketchy but it should work
		if(prev_error==0) prev_error = E;
			
		if(E*K_p<4 && E*K_p>0) E=4/K_p;
		if(E*K_p<0 && E*K_p>-4) E=-4/K_p;
			
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		int spd = -(K_p*E)+(integral*K_i)+(derivative*K_d);
		spd = (spd > 60 ? 60 : spd);
		spd = (spd < -60 ? -60 : spd);
		
		motor(MOT_LEFT, spd*3.5);
		motor(MOT_RIGHT, spd);
		msleep(1);
		
		printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		
		if(E<=EPSILON && E>=-EPSILON) {
			ao();
			break;
		}
	}
	printf("[DONE] done overall correction");
	msleep(1000);
	
	//dropping 
	servo_slow(1, 200, 5); //port, position, time
	//shaking
	forward(.1);
	msleep(100);
	backward(.2);
	msleep(100);
	forward(.1);
	msleep(500);
	set_servo_position(1, 1800);
	msleep(2000);
	printf("[DONE] finished tribble pickup");
	
	//float v = ( ( ( (float) E) * ks )/1000.);
	//move back the same amount
	if(v < 0l) 
		forward(v);
	else backward(v);
		
	float angle = ((float)turned_angle)*RADTODEG;
	printf("{{ANGLE}} %f\n", angle);
	printf("   {{TURNED ANGLE}} %f\n", turned_angle);
	if(angle < 0l) {
		right(-angle, 0);
	}
	else {
		left(angle, 0);
	}
	msleep(1000);
	turned_angle = 0;
}

void square_up_angle(){
	//P constant
	double Con = 40.0;
	int leftDistance = analog_et(2);
	int rightDistance = analog_et(3);
	
	//make returned values usable
	set_analog_pullup(2, 0);
	set_analog_pullup(3, 0);
	
	//acceptable difference between the distances
	int aDiff = .1;
	
	// distance between IR sensors
	double dia = 430;//200units = about 3.5 in they are 7.5 in apart
	
	//difference between the distances
	int diff = leftDistance-rightDistance;
	double AE = 0;
	
	leftDistance = analog_et(2);
	rightDistance = analog_et(3);
	diff = leftDistance-rightDistance;
	//squares robot
	while (abs(diff) > aDiff) {
		leftDistance = analog_et(2);
		rightDistance = analog_et(3);
		diff = leftDistance-rightDistance;
		AE = atan(diff/dia);
		//turn robot until square
		printf("left: %d\n",leftDistance);
		printf("right: %d\n",rightDistance);
		if(AE*Con<10 && AE*Con>0) AE=10/Con;
		if(AE*Con<0 && AE*Con>-10) AE=-10/Con;
		motor(MOT_LEFT,-1*Con*AE);
		motor(MOT_RIGHT,Con*AE);
		//msleep(1);
	}
	
	
}

void square_up_distance(int distance){
	//distance is not in inches do testing to find out for each case distance of 300 is about 3 inches
	//for our purposes it is a small number for a big distance but it is not a linear value so we can't just convert it into inches
	
	//motor power for straight part of the squareup
	int sqpow = 23;
	
	int leftDistance = analog_et(2);
	int rightDistance = analog_et(3);
	
	//make returned values usable
	set_analog_pullup(2, 0);
	set_analog_pullup(3, 0);
	
	//acceptable difference between the distances
	int aDiff = .1;
	
	
	//moves robot to correct distance
	while (abs((leftDistance+rightDistance)/2-distance) > aDiff){
		leftDistance = analog_et(2);
		rightDistance = analog_et(3);
		printf("leftf: %d\n",leftDistance);
		printf("rightf: %d\n",rightDistance);
		if((leftDistance+rightDistance)/2 < distance){
			//move robot forward
			motor(MOT_LEFT,-sqpow);
			motor(MOT_RIGHT,-sqpow);
			} else {
			//move robot backward
			motor(MOT_LEFT,sqpow);
			motor(MOT_RIGHT,sqpow);
		}
		msleep(1);
	}
}

//sorting without PID not working
void tsort(){
	
	
	double turned_angle; 
	int x_rob = 100;  
	int y_rob = -113; //old: 156
	int y_target = 69; //new: 68 (old = 25)
	int x_blob, y_blob;
	
	
	camera_update();
	x_blob = get_object_center(0,0).x;  
	y_blob = get_object_center(0,0).y; 
	while(cam_area(0)==0){
		camera_update();
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}
	
	printf("x : %d, y: %d\n");
		double E = atan(
			((double)(-1*(x_blob-x_rob)))
			/((double)(y_blob-y_rob))
		);
	
	
	float angle = ((float)E)*RADTODEG*0.7;
	printf("{{ANGLE}} %f\n", angle);
	printf("   {{TURNED ANGLE}} %f\n", E);
	if(angle < 0l) {
		left(-angle, 0);
	}
	else {
		right(angle, 0);
	}
	msleep(1000);
	
	//Distance//
	double D = y_blob - y_target; 
	
	float v = ( ( (float) D) / 8);//camera to cm is 23/182
		printf("v = %f\n", v);
	if(v < 0l) 
		multforward(v,-20);
	else {
		multforward(v,20);
	}
		
	printf("[DONE] done overall correction");
	msleep(1000);
	
	//dropping 
	servo_slow(1, 200, 5); //port, position, time
	//shaking
	forward(.1);
	msleep(100);
	backward(.2);
	msleep(100);
	forward(.1);
	msleep(500);
	set_servo_position(1, 1800);
	msleep(2000);
	printf("[DONE] finished tribble pickup");
	
	//move back the same amount
	v = -v;
	if(v < 0l){ 
		backward(-v);
	}
	else forward(v);
	
	angle = -angle; 
	if(angle < 0l) {
		left(-angle, 0);
	}
	else {
		right(angle, 0);
	}
	
}

#endif
