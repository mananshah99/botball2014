#include "./createDrive.h"
#include "./createSlow.h"
#define FULL 100
//bump functions
void forward_bump(bool both)
{
	do{ create_drive_direct(300,300); }
	while(get_create_lbump()==0);
}
void backward_bump()
{ 
	do{ create_drive_direct(-300,-300); }
	while(get_create_lbump()==0);
}

int main()
{
	create_connect();
	
	create_wait_time(20); //20 deciseconds for the link to pass
	create_drive_direct_dist(FULL,FULL,50); //50 centimeters
	
	//block here, square up, and get to the next box area
	forward_bump();
	create_block(); //finish the bump
	create_drive_direct_dist(-FULL,-FULL,50);
	
	/*
	 Angle is 87 because 90 degrees never works
	 Radius is 0 
	 Speed is 60 (too fast?)
	*/
	create_right(87,0,60);
	//drive to the other end of the 
	forward_bump();
	
	//next box area after squaring up
	printf("finished");
	create_disconnect();
	return 0;
}
