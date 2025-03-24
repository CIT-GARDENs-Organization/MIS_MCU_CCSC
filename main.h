#ifndef MAIN_H
#define MAIN_H

// PIC configuration file
#include <18F67J94.h>

// pin assignment etc
#include "config.h"

// values based on IICD 
#include "define.h"

// global value
#include "value.h"

// SerialCommunication
#include "communication.h"
#include "communication.c"

// Missions
#include "Mission.h"
#include "Mission.c"

// Copy to SMF
#include "DataCopy.h"
#include "DataCopy.c"

#endif
