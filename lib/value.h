#ifndef VALUE_H
#define VALUE_H

#include "typedef.h"

//__________ Timer __________

volatile unsigned int32 subsec = 0, sec = 0; // dsec = deci sec
volatile unsigned int16 day = 0;
volatile unsigned int16 duration_sec = 0;


//__________ Receive signal __________
volatile int1 is_use_smf_req_in_mission = FALSE;
volatile unsigned int8 boss_receive_buffer[RECEIVE_BUFFER_MAX] = {0x00};
volatile int8 boss_receive_buffer_size = 0;


// _______ Frame ID ________

const FrameID frame_ids[RECEIVE_FRAME_KINDS] = {
    {UPLINK_COMMAND, UPLINK_COMMAND_LENGTH}, 
    {STATUS_CHECK, STATUS_CHECK_LENGTH}, 
    {IS_SMF_AVAILABLE, IS_SMF_AVAILABLE_LENGTH}
};

//__________ Status __________

volatile int8 status = IDLE;


// ____________ Mission _________

volatile unsigned int8 executed_mission[EXECUTED_MISSION_SIZE] = {0x00};
volatile int8 executed_mission_count = 0;


//__________ SMF Queue __________

SmfDataStruct smf_data[SMF_DATA_SIZE] = { {0x00} };
volatile int8 smf_data_head = 0;
volatile int8 smf_data_tail = 0;

#endif

