#ifdef X

#include "./template.h"
int main() {
	enable_servo(1);
	camera_open();
	while(1) {
		
		//printf("area: %d\n",cam_area(0));
		
		int x = get_object_center(0,0).x;  // get image center x data
		int y = get_object_center(0,0).y;  //    and y data
		if (get_object_count(0) > 0) { // there is a blob
			display_printf(0,1,"Center of largest blob: (%d,%d)   ",x,y);
		}
		else display_printf(0,1,"No object in sight                ");
		camera_update();   // get new image data before repeating
	}
	set_servo_color(1,0);
	//118, 9[0-9]
}
#endif
