void servo_slow(int port, int end, float time)
{
	float increment = 1;
	float curr = get_servo_position(port);
	float start = get_servo_position(port);
	float i = ((end-start)/time)*(increment/100);
	
	if (start > end)
	{
		while(curr > end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment);
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			sleep(increment);
		}
	}
	set_servo_position(port,end);
}
