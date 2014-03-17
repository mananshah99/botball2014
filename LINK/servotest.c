// Created on Sun March 16 2014

#include ./generic.h
#include ./menu.h
#include ./slowservo.h
#include ./drive.h
#include ./camera.h

#define servo_test
#ifdef servo_test
int main()
{
	servo_slow(1,1000,5)
	printf("Done!\n");
	return 0;
}
