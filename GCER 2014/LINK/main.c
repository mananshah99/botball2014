//#define MAIN
#include "./template.h"

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

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

int basket_open = 1300;
int basket_closed = 171;
int basket_up = 400;
int basket_down = 75;

int main() {
	#define DEBUG // comment this out when in actual competition 
	/*
	#define SPDl	90
	#define SPDr	90
	#define SPDlb	90
	#define SPDrb	90
	#define SPD 	90
	*/
	//fixed these in drive.c because stuff
	
	set_servo_position(1, 1300);	
	set_servo_position(2, basket_down);
	set_servo_position(3, basket_closed);
	
	//enabling everything
	enable_servos();
	camera_open();
	camera_update();
	
	///---Drive 1---///
	
	forward(48);
	
	set_servo_position(3, basket_open);
	
	msleep(100);
	left(90, 0);
	forward(10);
	printf("sortteding stuffs\n");
	sleep(3);
	set_servo_position(3, basket_closed);
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, -60);
	sleep(2);
	servo_slow(2, basket_up, 4);
	forward(150);
	set_servo_position(2, basket_down);
	left(90,0);
	backward(25);
	square_up_angle();
	square_up_distance(240);
	square_up_angle();
	msleep(50);
	right(90,0);
	backward(10);
	servo_slow(3, basket_open, 10);
	sleep(1);
	forward(25);
	printf("sortteding stuffs\n");
	sleep(3);
	set_servo_position(3, basket_closed);
	backward(50);
	right(90,0);
	
	
	//will add this back in later
	/*
	#define SPDlb	50
	#define SPDrb	50
	#define SPD	20
	*/
	/**PICK UP 1*/
	/*
	correct_angle();
	correct_distance();
	ao();
	
	msleep(1500);
	
	correct_angle();
	correct_distance();
	ao();*/
	//done with backing up 
	disable_servos();
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
	double EPSILON = 0.02;
	
	//init
	set_servo_position(1, 1584);
	while(1/*!in_range(E, 0, EPSILON) || !in_range(E, 0, -EPSILON)*/) {
		//x_blob = get_object_center(0,0).x;  
		//y_blob = get_object_center(0,0).y;  
		do{
			camera_update();
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}while(cam_area(0)==0);
			
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
		
		motor(MOT_LEFT, -1*((K_p*E)+(integral*K_i)+(derivative*K_d)));
		motor(MOT_RIGHT, (K_p*E)+(integral*K_i)+(derivative*K_d));
		
		msleep(1);
		printf("[log] E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		
		if(E<=EPSILON && E>=-EPSILON) 
		{
			ao();
			break;
		}
		
	}
	printf("[log] done with angle correction");
	beep();
	msleep(1000);
}

void correct_distance() {
	float x_blob, y_blob, E = 0;
	camera_update();
	do{
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);
	
	//E = max(-y_blob + y_target, y_blob + y_target);
	E = y_blob - y_target;
	
	//11 used to be 10.4 here
	float v = ( ( ( (float) E) * ks * 3)/1000.);
		printf("=============>  %f\n", v);
	if(v < 0l) 
		forward(v);
	else {
		backward(v);
		printf("forward`~~!!!!!!!");
	}
		
	printf("[log] done overall");
	msleep(1000);
	
	//dropping 
	servo_slow(1, 200, 5); //port, position, time
	//set_servo_position(1, 200);
	//msleep(1500);
	//shaking
	forward(.1);
	msleep(100);
	backward(.2);
	msleep(100);
	forward(.1);
	msleep(500);
	set_servo_position(1, 1800);
	msleep(2000);
	printf("[log] finished tribble pickup");
	
	//move back the same amount
	if(v < 0l) 
		backward(v);
	else forward(v);
		
	float angle = ((float)turned_angle)*RADTODEG;
	if(angle < 0) {
		left(angle, 0);
	}
	else {
		right(angle, 0);
	}
	msleep(1000);
}

	/*
	camera_update();
	
	double x_blob, y_blob;
	
	//fix this!
	do{
		camera_update();
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);
	
	double E = -y_blob + y_target;
	
	//11 used to be 10.4 here
	if(E < 0) {
		backward((((double)E)*ks)/1000.);
	}
	else {	
		forward((((double)E)*ks)/1000.);
	}
	msleep(1000);
	
	//dropping 
	set_servo_position(1, 200);
	msleep(1500);
	//shaking
	backward(.1);
	msleep(100);
	forward(.2);
	msleep(100);
	backward(.1);
	msleep(500);
	set_servo_position(1, 1600);
	msleep(2000);
	printf("[log] finished tribble pickup");
	
	//move back the same amount
	forward(-(((double)E)*(ks/2))/1000.);
		
	double angle = turned_angle*RADTODEG;
	if(angle < 0) {
		left(angle, 0);
	}
	else {
		right(angle, 0);
	}
	msleep(1000);*/
	
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
			if(AE*Con<15 && AE*Con>0) AE=15/Con;
			if(AE*Con<0 && AE*Con>-15) AE=-15/Con;
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
