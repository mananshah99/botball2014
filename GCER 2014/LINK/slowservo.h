void servo_slow(int port, int end, float time)
{
	printf("servo_slow");
	float increment = 1;
	float curr = get_servo_position(port);
	float start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	
	if (start > end)
	{
		printf("if1");
		while(curr > end)
		{
			printf("%f\n",curr);
			printf("test, 1");
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment);
		}
	}
	else if (start < end)
	{
		printf("if2");
		while(curr < end)
		{
			printf("%f\n",curr);
			printf("test, 2");
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment);
		}
	}
	
}
