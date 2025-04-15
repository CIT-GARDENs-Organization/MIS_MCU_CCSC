#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "define.h"


typedef struct {
    int8 id;
    int8 length;
} FrameID;


#define CONTENT_MAX 32
typedef struct {
    int8 frame_id;
    unsigned int8 content[CONTENT_MAX];
    int8 size;
    int1 is_exist;
} Command;


const FrameID frame_ids[RECEIVE_FRAME_KINDS] = {
    {UPLINK_COMMAND, UPLINK_COMMAND_LENGTH}, 
    {STATUS_CHECK, STATUS_CHECK_LENGTH}, 
    {IS_SMF_AVAILABLE, IS_SMF_AVAILABLE_LENGTH}
};

// ______ Receive _______

Command make_receive_command(unsigned int8 receive_signal[], int8 receive_signal_size);

void clear_receive_signal(unsigned int8 receive_signal[], int8 *receive_signal_size);

static int8 trim_receive_signal_header(unsigned int8 receive_signal[], int8 receive_signal_size);

static int8 get_content_size(unsigned int8 frame_id);

static int1 check_crc(unsigned int8 frame[], int8 receive_frame_size);

static int1 check_device_id(unsigned int8 device_id);


// ______ Transmit _______

void transmit_command(unsigned int8 frame_id, unsigned int8 content[], int8 size);

static void transmit(unsigned int8 data[], int8 data_size);

// ______ Common _________

static unsigned int8 calc_crc8(unsigned int8 frame[], int8 payload_size);

#include "./src/communication.c"

#endif
