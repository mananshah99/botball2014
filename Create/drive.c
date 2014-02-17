// Created on Fri February 14 2014

#include "./drive.h"
int main()
{
	create_connect();
	
	create_wait_time(20); //20 deciseconds
	create_drive_direct_dist(50); //50 centimeters
	//block here, square up, and get to the next box area
	create_block();
	create_forward(80, 50);
	//idk what the speeds are so i just put in a random number
	
	create_disconnect()
	return 0;
}
