#define MAIN

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#ifdef MAIN
#include "./template.h"

double turned_angle = 0.0;
int x_rob = 100;  
int y_rob = -113; //old: 156
int y_target = 69; //new: 68 (old = 25)

double MAX_HEIGHT = 18.7; 
double MAX_WIDTH = 18.7;
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
int basket_tilt = 200;

int main() {
	//#define DEBUG // comment this out when in actual competition 
	
	//enabling everything
	enable_servos();
	camera_open();
	camera_update();
	
	set_servo_position(1, 1300);	
	set_servo_position(2, basket_down); 
	set_servo_position(3, basket_closed);
	
	
	
	///---Drive 1---///
	
	forward(48);
	
	set_servo_position(3, basket_open);
	
	msleep(100);
	left(90, 0);
	forward(5);
	
	correct_angle();
	correct_distance();
	correct_angle();
	correct_distance();
	
	forward(2);
	set_servo_position(3, basket_closed);
	set_servo_position(1, 1300);
	motor(MOT_LEFT, -38);
	motor(MOT_RIGHT, -40);
	msleep(2500);
	servo_slow(2, basket_tilt, 4);
	forward(153);
	set_servo_position(2, basket_down);
	left(88,0);
	backward(20);
	
	square_up_angle();
	square_up_distance(260);
	square_up_angle();
	
	msleep(50);
	right(70,0);
	backward(10);
	servo_slow(3, basket_open, 10);
	sleep(1);
	forward(18);
	
	correct_angle();
	correct_distance();
	correct_angle();
	correct_distance();
	
	set_servo_position(3, basket_closed);
	left(90,0);
	
	square_up_angle();
	square_up_distance(250);
	square_up_angle();
	
	left(85,0);
	servo_slow(2, basket_tilt, 4);
	forward(53);
	left(85,0);
	forward(15);
	line_squareup(0.6435);
	
	
	//other side//
	forward(40);

	right(90,0);
	servo_slow(2, basket_down, 4); 
	servo_slow(3, basket_open, 10);
	forward(55);
	
	correct_angle();
	correct_distance();
	correct_angle();
	correct_distance();
	
	servo_slow(3, basket_closed, 10);
	left(90,0);
	
	
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
	
	int dark = 740; // dark > 740
	
	while(lsens <  dark && rsens < dark ) {
		printf("forward\n");
		motor(MOT_LEFT,30);
		motor(MOT_RIGHT,22);
		//move forward
		lsens = analog(1);
		rsens = analog(0);
		clear_motor_position_counter(MOT_RIGHT);
		clear_motor_position_counter(MOT_LEFT);
		if (lsens > dark){
			ao();
			turn_motor = MOT_LEFT;
			while(rsens < dark ) {
				printf("extra turn right:%f\n",extra_turn);
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_LEFT,30);
				//mav(MOT_RIGHT,0);
				//turn left by moving right forward
				turn_angle = sensor_angle - (gmpc(MOT_LEFT)/CMtoBEMF)/ks;
				extra_turn =(-2*atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle))));
				//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
				//srad is 12, lrad is 15
			}  
		}
		else if (rsens > dark){
			ao();
			
			turn_motor = MOT_RIGHT;
			while(lsens < dark ) {
				printf("extra turn left:%f\n",extra_turn);
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_RIGHT,30);
				//mav(MOT_LEFT,0);
				//turn right by moving left forward
				turn_angle = sensor_angle - (gmpc(MOT_RIGHT)/CMtoBEMF)/ks;
				extra_turn =(-2*atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle))));
				//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
				//srad is 12, lrad is 15
				//for new values equation is(srad/lrad)*cos(a)=cos(a+turn_angle) a=extra_turn
				
				
			}
		}
	}
	ao();
	//turn extra
	printf("motor:%d\n",turn_motor);
	
	if(turn_motor == 2) {
		right(extra_turn*180/3.14,0);
	}
	else if(turn_motor ==1) {
		left(extra_turn*180/3.14,0);
	}
	
	//clear_motor_position_counter(turn_motor);
	//mtp(turn_motor,60,(extra_turn * ks)*CMtoBEMF);
	while(lsens >  dark || rsens > dark ) {
		printf("backward\n");
		lsens = analog(1);
		rsens = analog(0);
		motor(MOT_LEFT,-36);
		motor(MOT_RIGHT,-30);
		//move backward
		//we could change this to forward to have it square up on the far side of the line.
	}
	ao();
}


int x_blob;
int y_blob;

void correct_angle() {
	camera_update();
	update_wait();
	clear_motor_position_counter(MOT_RIGHT);
	clear_motor_position_counter(MOT_LEFT);
	
	//constants
	double K_p = 27.0;	/***USED TO BE 26***/
	double K_i = 0.00;
	double K_d = 0.04;	
	
	//values (rob is robot) 
	int x_target = x_rob; //new: 100
	
	//for PID
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	double spd = 0.0;
	
	
	//threshold value
	double EPSILON = 0.04;
	double last_x = -1000, last_y = -1000; // unreasonable at beginning
	
	//init
	set_servo_position(1, 1584);
	prev_error = 0;
	
	while(1/*!in_range(E, 0, EPSILON) || !in_range(E, 0, -EPSILON)*/) {
		camera_update(); 
		
		do{
			camera_update();
			
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y; 
			
			//if(cam_area(0)==0) return;
			if(cam_area(0) == 0) continue;
			
			/**checking for two blobs mushed together**/
			
			rectangle nx = get_object_bbox(0, 0);
			if(nx.height > MAX_HEIGHT || nx.width > MAX_WIDTH) {
				if(nx.height > MAX_HEIGHT) {
					y_blob = get_object_center(0, 0).y - 5;
				}
				
				if(nx.width > MAX_WIDTH) {
					x_blob = get_object_center(0, 0).x - 5; 
				}
				break;
			}
			
			/**they weren't mushed together, so checking for nearest one closest to prev position**/
			if (get_object_count(0)>1){
				if(last_x == -1000 && last_y == -1000) {
					last_x = x_blob;
					last_y = y_blob;
					break;
				}
				else {
					int c2_x = get_object_center(0, 1).x; 
					int c2_y = get_object_center(0, 1).y; 
					
					if(c2_x == -1 || c2_y == -1) break;
					
					double c2diff_x = (c2_x - last_x) > 0    ? 	(c2_x - last_x)     :   -(c2_x - last_x);
					double c2diff_y = (c2_y - last_y) > 0    ? 	(c2_y - last_y)     :   -(c2_y - last_y);
					double c1diff_x = (x_blob - last_x) > 0  ? 	(x_blob - last_x)   :   -(x_blob - last_x);
					double c1diff_y = (y_blob - last_y) > 0  ? 	(y_blob - last_y)   :   -(y_blob - last_y);
					
					if(c2diff_x < c1diff_x) {
						x_blob = c2_x;
					}
					if(c2diff_y < c1diff_y) {
						y_blob = c2_y;
					}
					break;
				}
			}
		}while(cam_area(0)==0);
		
		// printf("x : %d, y: %d\n");
		double E = atan(
		((double)(-1*(x_blob-x_rob)))
		/((double)(y_blob-y_rob))
		);
		
		// this is a bit sketchy but it should work
		if(prev_error==0) {
			prev_error = E;
			//turned_angle = E;
		}
		
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		
		printf("****ERROR****  ==== %f\n", E);
		
		spd = (K_p*E)+(integral*K_i)+(derivative*K_d);
		
		if(spd<6 && spd>=0) spd=6;
		if(spd<0 && spd>-6) spd=-6;
		
		motor(MOT_LEFT, -1*spd);
		motor(MOT_RIGHT, spd);
		
		msleep(1);
		//printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		turned_angle = (abs(gmpc(MOT_RIGHT)-gmpc(MOT_LEFT)))/(2*CMtoBEMF*ks);
		
		if(E<=EPSILON && E>=-EPSILON) 
		{
			ao();
			break;
		}
		
	}
	printf("[DONE] done with angle correction");
	msleep(100);
}

void correct_distance() {
	clear_motor_position_counter(MOT_RIGHT);
	clear_motor_position_counter(MOT_LEFT);
	
	double K_p = 0.1;	/****USED TO BE 0.18****/
	double K_i = 0;
	double K_d = 0;
	
	//double x_blob, y_blob;
	double E = 0;	
	
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	double EPSILON = 2;
	
	
	//from other code updates v so that it can correct distance 
	
	/*camera_update();
	do{
	x_blob = get_object_center(0,0).x;  
	y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);*/
	
	//E = max(-y_blob + y_target, y_blob + y_target);
	E = y_blob - y_target;
	
	//11 used to be 10.4 here
	float v = ( ( (float) E) /8);
	
	/*********Threshold Camera Blob Issue*********/
	while(1) {
		camera_update();
		
		//x_blob = get_object_center(0,0).x;  
		//y_blob = get_object_center(0,0).y; 
		
		do{
			camera_update();
			//x_blob = get_object_center(0,0).x;  
			//y_blob = get_object_center(0,0).y; 
			
			int c1_x = get_object_center(0, 0).x; 
			int c1_y = get_object_center(0, 0).y;
			
			if(cam_area(0)==0) return;
			
			int c2_x = get_object_center(0, 1).x; 
			int c2_y = get_object_center(0, 1).y; 
			
			if(c2_x == -1 || c2_y == -1) {
				x_blob = c1_x;
				y_blob = c1_y;
				break;
			}
			else {
				int f_diff = (c1_y - y_blob) > 0 ? (c1_y - y_blob) : -(c1_y - y_blob);
				int s_diff = (c2_y - y_blob) > 0 ? (c2_y - y_blob) : -(c2_y - y_blob);
				if(f_diff < s_diff) {
					x_blob = c1_x;
					y_blob = c1_y;
					break;
				}
				else {
					x_blob = c2_x;
					y_blob = c2_y;
					break;
				}
			}
			/*rectangle nx = get_object_bbox(0, 0);
			
			if(nx.height > MAX_HEIGHT) {
			y_blob = get_object_center(0, 0).y - 10;
			}
			
			if(nx.width > MAX_WIDTH) {
			x_blob = get_object_center(0, 0).x - 10; 
			
			}*/
			
		}while(cam_area(0)==0);
		
		E = -y_blob+y_target;
		
		//this is a bit sketchy but it should work
		if(prev_error==0) prev_error = E;
		
		//if(E*K_p<4 && E*K_p>0) K_p=4/E;
		//if(E*K_p<0 && E*K_p>-4) K_p=-4/E;
		
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		double spd = -(K_p*E)+(integral*K_i)+(derivative*K_d);
		double spdl = 0.0;
		double spdr = 0.0;
		
		//limit speed 
		
		//spd = (spd > 60 ? 60 : spd);
		//spd = (spd < -60 ? -60 : spd);
		
		//if(spd<6 && spd>=0) spd=6;
		//if(spd<0 && spd>-6) spd=-6;
		
		if (spd>0){
			spdr=36; 
			spdl=6;
		}
		else if (spd<0){
			spdr=-14;
			spdl=-7;
		}
		
		//printf("spd (right) : %f\n",spdr);
		//printf("spd (left) %f\n: ",spdl);
		motor(MOT_LEFT, spdr);
		motor(MOT_RIGHT, spdl);
		msleep(1);
		
		// printf("E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		v =(gmpc(MOT_RIGHT)+gmpc(MOT_LEFT))/(2*CMtoBEMF);
		
		if(E<=EPSILON && E>=-EPSILON) {
			ao();
			break;
		}
	}
	
	printf("[DONE] done overall correction");
	msleep(100);
	
	//dropping 
	servo_slow(1, 100, 8); //port, position, time
	//shaking
	forward(.2);
	//msleep(100);
	backward(.4);
	//msleep(100);
	forward(.2);
	//msleep(500);
	right(3,0);
	left(6,0);
	right(3,0);
	set_servo_position(1, 1800);
	msleep(100);
	printf("[DONE] finished tribble pickup");
	
	//float v = ( ( ( (float) E) * ks )/1000.);
	//move back the same amount
	if(v < 0l) 
	forward(v);
	else backward(v);
	
	float angle = ((float)turned_angle)*RADTODEG;
	// printf("{{ANGLE}} %f\n", angle);
	// printf("   {{TURNED ANGLE}} %f\n", turned_angle);
	if(angle < 0l) {
		right(-angle, 0);
	}
	else {
		left(angle, 0);
	}
	msleep(500);
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
		//printf("left: %d\n",leftDistance); 
		//printf("right: %d\n",rightDistance);
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
		//printf("leftf: %d\n",leftDistance);
		//printf("rightf: %d\n",rightDistance);
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
