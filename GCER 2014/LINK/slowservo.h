void servo_slow(int port, int end, float time)
{
	printf("servo_slow");
	float increment = 1;
	float curr = get_servo_position(port);
	float start = get_servo_position(port);
	float i = ((end-start)/time)*(increment/100);
	
	if (start > end)
	{
		printf("if1\n");
		while(curr > end)
		{
			printf("%f\n",curr);
			printf("test1 \n");
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment);
		}
	}
	else if (start < end)
	{
		printf("if2\n");
		while(curr < end)
		{
			printf("%f\n",curr);
			printf("test2\n");
			set_servo_position(port,curr);
			curr+=i;
			sleep(increment);
		}
	}
	set_servo_position(port,end);
}
