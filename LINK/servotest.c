// Created on Sun March 16 2014

#define servo_test
#ifdef servo_test
int main()
{
	enable_servos();
	servo_slow(1,1007,5);
	msleep(10000);
	disable_servos();
	printf("Done!\n");
	return 0;
}
#endif
