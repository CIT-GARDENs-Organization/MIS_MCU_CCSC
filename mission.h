#ifndef MISSION_H
#define MISSION_H

#define PARAMETER_LENGTH 8

#include "./lib/smf_queue.h"
#include "./lib/flash.h"
#include "./lib/mission_tools.h"


// fundamental fnction
void execute_mission(unsigned int8 *content);

// missions
void example_00(unsigned int8 parameter[]);
void example_01(unsigned int8 parameter[]);
void example_02(unsigned int8 parameter[]);

#include "./mission.c"

#endif

// EOF
