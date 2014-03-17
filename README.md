# Robot Code 2014

Robot Code for the 2014 competition. 

- The LINK folder is for the Link robot
- The CREATE folder is for the Create robot

## To Do

* Test camera files
* **currently working**: write working orange blob pickup code
* Better byte writing functionality for Create
* Write Create dumping function for the orange blobs 
* Test the CREATE drive path
* **currently working**: Fix the LINK drive path (wheels currently break)
* Write LINK servo code to pick up hangers

* Fix the values and test the following code (in ```/CREATE/main.c```)

```c
#define SERV_ARM 1

//arm functions
void arm_close(){
	set_servo_position(SERV_ARM,2040);
}
void arm_open(){
	set_servo_position(SERV_ARM,646);
}
void arm_half(){
	set_servo_position(SERV_ARM,1800);
}
```
* Write LINK place blue hangers function (in ```/LINK/main.c```)
* Check threshold/does this code work as intended? (in ```/CREATE/main.c```)

```c
while(!(cam_area(C_ORANGE) > 3500)) //haven't found an orange blob
{
	//move right
	cam_update();
}
else
{
	//found a blob! pick it up
}
```
* **low priority**: Test slowservo (doesn't take 5 seconds to move up with this code)  

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
