#ifdef TEST1
#include "./template.h"
int main() {
	enable_servo(1);
	camera_open();
	int x;
	int y;
	//while(1) {

		printf("area: %d\n",cam_area(0));

		x = -get_object_center(0,0).x;  // get image center x data
		y = get_object_center(0,0).y;  //    and y data
		if (get_object_count(0) > 0) { // there is a blob
			display_printf(0,1,"Center of largest blob: (%d,%d)   ",x,y);
		}
		else display_printf(0,1,"No object in sight                ");
		camera_update();   // get new image data before repeating

	//}
	
	//triangle math, much simpler way. test this.
	int xDif = abs(115-x);
	int yDif = abs(91-y);
	right(aTan(xDif/yDif)+90);
	forward(sqrt(xDif*xDif+yDif*yDif));

	set_servo_color(1,0);
	//118, 9[0-9]
}
#endif
