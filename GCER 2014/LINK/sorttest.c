// Created on Fri March 28 2014
#include "./template.h"

#define GRABBER 1
#define GRABBER_DOWN 500
#define GRABBER_MID 1032
#define GRABBER_UP 1543

#define COL_GREEN 0 
#define COL_PINK 1

#define S_GATE 3 
#define S_CATCHER 2

int main()
{
	/**INIT VARIABLES**/
	int x, y;  // set up for color channel 0 (green)
	int xvalue, yvalue;
	int isGreenCentered = 0;
	int loop = 0;
	/*****************/
	
	/**ENTER THESE NUMBERS MANUALLY**/
	int centerx=106; 
	int centery=88;
	/********************************/
	
	int margin=8;
	int deltax = 0, deltay = 0;
	int stepsizex, stepsizey;
	int currpos;	
	int s_time;
	
	camera_open();
	s_time = curr_time();
	enable_servos();
	while((curr_time()-s_time) < 14) {
		while (isGreenCentered == 0) {
			camera_update(); // process the most recent image
			loop +=1;
			printf("Update camera, loop %d\n", loop);

			if (get_object_count(COL_GREEN) > 0) 
			{
				xvalue = get_object_center(COL_GREEN,0).x;
				yvalue = get_object_center(COL_GREEN,0).y;
				
				deltax = abs(xvalue-centerx);
				deltay = abs(yvalue-centery);
				
				stepsizex = (deltax>10) ? 20: 10;
				stepsizey = (deltay>10) ? 20: 10;
				
				printf("x is %d, y is %d\n", xvalue, yvalue);
				
				isGreenCentered = ((xvalue >= centerx-margin) && (xvalue <= centerx+margin))
					&& ((yvalue >= centery-margin) && (yvalue <= centery+margin));
				
				if(isGreenCentered == 1) //get x, y for the biggest blob the channel sees		
				{	
					printf("Biggest blob at (%d,%d)\n",xvalue,yvalue);
					msleep(600);
					//set_servo_position(GRABBER, GRABBER_MID);
					//msleep(600);
					set_servo_position(GRABBER, GRABBER_DOWN);
					msleep(600);
					set_servo_position(GRABBER,GRABBER_UP);
					msleep(600);
				}
				else
				{
					if(xvalue <= centerx+margin){
						//move right
						motor(MOT_RIGHT,70);
						motor(MOT_LEFT,-70);
						msleep(stepsizex);
						motor(MOT_RIGHT,0);
						motor(MOT_LEFT,0);
						printf("blob is too right\n");
					}	
					if(xvalue >= centerx-margin){
						//move left 
						motor(MOT_LEFT,70);
						motor(MOT_RIGHT,-70);
						msleep(stepsizex);	
						motor(MOT_LEFT,0);
						motor(MOT_RIGHT,0);
						printf("blob is too left\n");
					}

					if ((centerx-margin/*xvalue > 67*/) && (centerx+margin /*xvalue < 87*/))
					{
						if(yvalue > centery+margin) {
							//move forward
							motor(MOT_LEFT,-50);
							motor(MOT_RIGHT,-50);
							msleep(stepsizey);
							motor(MOT_LEFT,0);
							motor(MOT_RIGHT,0);
							//msleep(10);
							printf("blob is too close\n");
						}

						if(yvalue < centery-margin) {
							//move backward
							motor(MOT_LEFT,50);
							motor(MOT_RIGHT,50);
							msleep(stepsizey);
							motor(MOT_LEFT,0);
							motor(MOT_RIGHT,0);
							//msleep(10);
							printf("blob is too far\n");
						}
					}
				}
			}
		}
	}
	
	ao();
	disable_servos();
	printf("done!");
}
