# Robot Code 2014

Robot Code for the 2014 competition. 

- The LINK folder is for the Link robot
- The CREATE folder is for the Create robot

## Starting Positions
* Link robot starts at the left side of the starting box, with the back against the pipe, left wheel is 3 in. from left pipe. The arm is facing towards the rest of the table.
* Create starts at the right bottom corner, with bumper facing towards the cube rack.

## To Do

**If something's wrong, check if your servos are enabled.**

* **Remember to reset the ET sensor every run (because of the crash)**
* ~~Calibrate threshold values for the create based on light exposure.~~ **Using ET as of 4/7/2014**
* ~~Release hangers smoothly. Then square up. Create will go past while Link squares up.~~
* ~~Test camera sight files~~ **Using ET as of 4/7/2014**
* ~~Write create orange block pickup code~~
* Better byte writing functionality for Create
* ~~Write Create dumping function for the orange blobs~~
* ~~Test the Create drivepath~~
* ~~Write LINK servo code to pick up hangers~~

* ~~Tune and add possible cube count check in getCubes() (in ```/CREATE/main.c```)~~

```c
void getCubes()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog_et(ET));
	while(!(analog_et(ET)>480)) //haven't found a cube
	{ 
		printf("value: %d\n",analog_et(ET));
		create_backward(2,10); 
		tdist+=2;
		SHOW(printf("tdist is %d\n", tdist));
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 2047);
		
	if(tdist<500) getCubes();
	else {
		tdist=0;
		arm_close();
	}
}
```

* **PRIORITY 1: Write LINK place blue hangers function (in ```/LINK/main.c```)**
* ~~Check threshold/does camera code work as intended? (in ```/CREATE/main.c```)~~ **using ET sensor as of 4/7/2014**

* **low priority**: Test slowservo repeatedly (doesn't take 5 seconds to move up with this code)  

```c
#define servo_test
#ifdef servo_test
int main()
{
	enable_servos();
	servo_slow(1,1007,5000);
	msleep(10000);
	disable_servos();
	printf("Done!\n");
	return 0;
}
#endif
```

## How to Contribute
1. **Check the To Do Section**: choose a pending task that hasn't yet been completed and help us add that functionality to the schedule
2. **Fork this Repository**: fork either the main or development branches to your account (if you're not currently a contributor) and make proposed changes
3. **Send a Pull Request**: we'll review the changes and merge them if applicable
