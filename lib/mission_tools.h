#ifndef MISSION_TOOLS_H
#define MISSION_TOOLS_H

#include "communication.h"

// Check and reply to messages received from BOSS PIC
void check_and_respond_to_boss();

// Store the data you want to copy in SMF.
void enqueue_smf_data(unsigned int32 dest, unsigned int32 src, unsigned int32 size);


// Request using SMF to BOSS PIC
// !!!After use, you must call `void finished_use_smf()`
int1 req_use_smf();

// Call after using SMF
void finished_use_smf();


// Use in missions you want to execute consecutively
void executed_mission_pop(void);

// MIS MCU will be up and running duration_second seconds after mission completion
void continue_mis_mcu(int16 duration_second);

// TODO: development
//!void update_time(unsigned int8 raw_time[]);

#include "./src/mission_tools.c"

#endif
