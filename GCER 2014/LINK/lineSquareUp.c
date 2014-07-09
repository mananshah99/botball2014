
void line_squareup(double srad, double lrad, double sensor_angle){
	//srad is distance from wheel to close sensor lrad is distance to far sensor
	//angle is angle between sensors
	
	int lsens = analog(1);
	int rsens = analog(0);
	
	double turn_angle = 0
	double extra_turn = 0
	
	int dark = 800;//test this and change it to be correct
	
	while(lsens >  dark && rsens > dark ) {
		//move forward
		lsens = analog(1);
		rsens = analog(0);
		clear_motor_position_counter(port);//put in port right
		clear_motor_position_counter(port);//put in port left
		if (lsens > dark){
			while(rsens > dark ) {
				lsens = analog(1);
				rsens = analog(0);
				//turn left by moving left forward
				turn_angle = sensor_angle - (CMtoBEMF * get_motor_position_counter(port))/ks
				extra_turn = turn_angle + (-2 * atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle)))
			}
			//turn left extra turn
		}
		if (rsens > dark){
			while(lsens > dark ) {
				lsens = analog(1);
				rsens = analog(0);
				//turn right by moving left forward
				turn_angle = sensor_angle - (CMtoBEMF * get_motor_position_counter(port))/ks
				extra_turn = turn_angle + (-2 * atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle)))
			}
			//turn right extra turn
			
		}
	}
	while(lsens <  dark && rsens < dark ) {
		lsens = analog(1);
		rsens = analog(0);
		//move backward
	}
}
