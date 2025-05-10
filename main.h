#ifndef MAIN_H
#define MAIN_H

// PIC configuration file
#include <18F67J94.h>

// pin assignment etc
#include "config.h"


#include "./lib/typedef_content.h"

#include "./lib/value_status.h"

#include "./lib/timer.h"

#include "./lib/uart.h"

// Missions
#include "mission.h"

// SerialCommunication
#include "./lib/communication_driver.h"

// Copy to SMF
#include "./lib/data_copy.h"


#endif

// EOF
