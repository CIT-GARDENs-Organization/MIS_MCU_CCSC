#ifndef MISSION_H
#define MISSION_H


#define EXECUTED_MISSION_SIZE 8
#define PARAMETER_LENGTH 8
volatile unsigned int8 executed_mission[EXECUTED_MISSION_SIZE] = {0x00};
volatile int8 executed_mission_count = 0;


#include "./smf_queue.h"
#include "./flash.h"
#include "./mission_tools.h"


// fundamental fnction
void execute_mission(unsigned int8 *content);

// missions
void example_00(unsigned int8 parameter[]);
void example_01(unsigned int8 parameter[]);
void example_02(unsigned int8 parameter[]);

#include "./src/mission.c"

#endif
