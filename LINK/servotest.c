// Created on Sun March 16 2014

//#include "./generic.h"
//#include "./slowservo.h"
//#include "./drive.h"

#define servo_test
#ifdef servo_test
int main()
{
	enable_servos();
	servo_slow(1,1007,5);
	msleep(1000);
	printf("Done!\n");
	return 0;
}
#endif
