
#ifndef _DRIVE_H_
#define _DRIVE_H_

#define gmpc(port) get_motor_position_counter(port)


//primary driving code
#define MOT_LEFT 2
#define MOT_RIGHT 1
#define PI 3.14159265358979

/**THESE ARE IMPORTANT**/
#define SPD 50//turning
#define SPDl 92.//right forward
#define SPDr 90.//left forward

#define rdistmult 1.0
#define SPDlb 92.//right backward
#define SPDrb 90.//left backward
#define rdistmultb (SPDrb/SPDlb)
#define wheeldiameter 5.5
#define ks 17.5
#define CMtoBEMF (850/(PI*wheeldiameter))

void drive_off();
void clear_all_drive();
void drive(int mL,int mR);


void right(float degrees, float radius);
void left(float degrees, float radius);
void forward(float distance);
void multforward(float distance, float speedmult);
void backward(float distance);

#endif
