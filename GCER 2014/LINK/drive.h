
#ifndef _DRIVE_H_
#define _DRIVE_H_

#define gmpc(port) get_motor_position_counter(port)


//primary driving code
#define MOT_LEFT 1
#define MOT_RIGHT 2
#define PI 3.14159265358979

/**THESE ARE IMPORTANT**/
#define SPD 20//turning
#define SPDl 30.//left forward
#define SPDr 30.//right forward


#define rdistmult 1.0
#define SPDlb 50.//left backward
#define SPDrb 50.//right backward
#define rdistmultb (SPDrb/SPDlb)
#define wheeldiameter 4.2
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
