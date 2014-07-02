// Created on Thu June 26 2014
#define port 1
int main()
{
	enable_servos();

	int servoend = 1500;
	int servo_space = servoend-get_servo_position;
	int wait = 1;
	
	if(servospace<0){
	increment*=-1
		}
if(increment>0){
	while(servoend< get_servo-position){
		
		//
		set_servo_position(port,get_servo_position+1);
		//
		msleep(wait);
		
	}
}else{
	while(servoend> get_servo-position){
		
		//
		set_servo_position(port,get_servo_position+1);
		//
		msleep(wait);
		
	}
	
}

	return 0;
}
}
