#ifndef COMMUNICATION_DRIVER_H
#define COMMUNICATION_DRIVER_H

#include "define.h"
#include "communication.h"

Command make_receive_command(unsigned int8 receive_signal[], int8 receive_signal_size);
void transmit_ack();
void transmit_status();
void check_and_respond_to_boss();
int1 req_use_smf();


#include "./src/communication_driver.c"

#endif
