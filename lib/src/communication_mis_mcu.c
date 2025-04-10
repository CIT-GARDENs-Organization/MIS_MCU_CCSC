void transmit_ack()
{
   transmit_command(ACK, 0, 0);
}

void transmit_status()
{
   transmit_command(MIS_MCU_STATUS, &status, 1);
}
