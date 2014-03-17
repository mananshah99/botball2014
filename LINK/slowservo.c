void servo_off(int servo)
{ set_servo_position(servo,-1); }
void servo_slow(int port, int end, float time)
{
	float increment = .01;
	float curr,start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	curr = start;
	
	if (start > end)
	{
		while(curr > end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment*1000);
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep(increment*1000);
		}
	}
	set_servo_position(port,end);
}
