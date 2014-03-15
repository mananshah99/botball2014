#ifndef _FINALCREATE
#define _FINALCREATE
//required for buffering and scripting
#define WHEEL_DROP 1
#define CLIFF 10
#define BUMP 5
#define LEFT_BUMP 6
#define RIGHT_BUMP 7
#define BUTTON_ADVANCED 16
#define BUTTON_PLAY 17//TODO: finish all events.  p16 of create docs
#define SEN_0 18

//this is to get around kiss-c's lack of intelligence and lack of the inclusion of an ACTUAL WRITE_BYTE FUNCTION THAT WORKS ON BOTH THINGS
#ifndef __IROBOT_CREATE_H__
//int NUMBYTES;
void serial_init()
{
}
void create_write_byte(int num)
{
	//NUMBYTES++;
}
#endif
int get_high_byte2(int v)
{
    return (v >>8);
}

int get_low_byte2(int v)
{
    return (v & 255);
}
//extern int get_high_byte(int v);
//extern int get_low_byte(int v);

#define create_write_int(integer) create_write_byte(get_high_byte2(integer));create_write_byte(get_low_byte2(integer))
#endif
