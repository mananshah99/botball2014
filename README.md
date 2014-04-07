# Robot Code 2014

Robot Code for the 2014 competition. 

- The LINK folder is for the Link robot
- The CREATE folder is for the Create robot


## To Do
**If something's wrong, check if your servos are enabled.**
**Calibrate threshold values for the create based on light exposure**

###**PRIORITY 1: GET HANGERS SMOOTHLY ON LINK**
###**PRIORITY 2: FIX GETCUBES FOR CREATE**
* Test camera files
* **currently working**: write create orange blob pickup code
* Better byte writing functionality for Create
* Write Create dumping function for the orange blobs 
* Test the Create drive path
* Write LINK servo code to pick up hangers

* Calibrate threshold and fix cube pickup for getCubes() (in ```/CREATE/main.c```)

```c
void getCubes()
{
	printf("-----RESTART RUN-----\n init: %d\n",analog(TOPHAT));
	while(!(analog(TOPHAT)<780)) //haven't found an orange blob
	{ 
		printf("value: %d\n",analog(TOPHAT));
		create_backward(2,10); 
	}
	
	closeHandle();
	msleep(1000);
	set_servo_position(GRABBER, 2047);
	//arm_close();
	//arm_half(); //should move and close the arm around the block
	
	cCount++;
	if(cCount!=2) getCubes();
	else {
		resetcount(); //no recursive call, function ends
		arm_close();
	}
}
```

* Write LINK place blue hangers function (in ```/LINK/main.c```)
* ~~Check threshold/does camera code work as intended? (in ```/CREATE/main.c```)~~ **using top hat sensor as of 3/16/2014**

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
