// Created on Fri February 14 2014
#include "./drive.h"

void forward_bump()
{ while(create_wait_event(LEFT_BUMP) == 0) create_drive_direct(300,300); }
void backward_bump()
{ while(create_wait_event(LEFT_BUMP) == 0) create_drive_direct(-300,-300); }

int main()
{
	create_connect();
	
	create_wait_time(20); //20 deciseconds for the link
	create_drive_direct_dist(50); //50 centimeters
	
	//block here, square up, and get to the next box area
	forward_bump();
	//next box area after squaring up
	
	printf("finished");
	create_disconnect();
	return 0;
}
