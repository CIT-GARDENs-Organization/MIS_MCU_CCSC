#ifndef VALUE_H
#define VALUE_H

//__________ Timer __________

volatile unsigned int32 subsec = 0, sec = 0; // dsec = deci sec
volatile unsigned int16 day = 0;
volatile unsigned int16 duration_sec = 0;


//__________ Receive signal __________

#define RECEIVE_BUFFER_MAX 32
volatile int1 is_use_smf_req_in_mission = FALSE;
volatile unsigned int8 boss_receive_buffer[RECEIVE_BUFFER_MAX] = {0x00};
volatile int8 boss_receive_buffer_size = 0;

//__________ Status __________

volatile int8 status = IDLE;

#endif

