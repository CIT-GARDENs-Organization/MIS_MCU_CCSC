#define DEBUG_PRINT
#include <main.h>
 

// -----------------------intrrupts-------------------- //
volatile int8 sec = 0, min = 0;
#INT_TIMER0
void  TIMER0_isr(void) 
{
   if(++sec == 60)
   {
      sec = 0;
      min++;
   }
}

volatile unsigned int8 receive_signal[16] = {0x00};
volatile int8 receive_signal_size = 0;
#INT_RDA
void RDA_isr(void)
{
   if (receive_signal_size < 16)
      receive_signal[receive_signal_size++] = fgetc(BOSS);
   else
      fgetc(BOSS);
}

// -------------------------------------------------- //
void clear_receive_signal(unsigned int8 receive_signal[], int8 *receive_signal_size)
{
   memset(receive_signal, 0x00, *receive_signal_size);
   *receive_signal_size = 0;
}

void printf_byte(unsigned int8 data[], int8 data_size, unsigned int8 stream)
{
   for(int8 i = 0; i < data_size; i++)
      fprintf(BOSS, "%X ", data[i]);
   fprintf(BOSS, "\r\n");
}

// ------------------------------------------------- //
int1 execute_command(Command *command)
{
   fprintf(PC, "\r\nStart execute_command\r\n");
   
   static unsigned int8 status = IDLE;
   
   switch(command->frame_id)
   {
      case UPLINK_COMMAND:
         fprintf(PC, "\t-> Uplink command\r\n");
         fprintf(PC, "\t   Transmit Acknolegde\r\n");
         transmit_command(ACK, 0, 0);
         if (status == IDLE)
         {
            status = BUSY;
            execute_mission(command->content);
            if(smf_data_is_exist)
               status = SMF_COPY_REQ;
            else
               status = FINISHED;
         }
         else
            fprintf(PC, "\t\t-> MIS MCU is busy. command append to queue\r\n");
         return FALSE;
      
      case STATUS_CHECK:
         fprintf(PC, "\t-> Status check\r\n");
         fprintf(PC, "\t\t-> My status is %d\r\n", status);
         fprintf(PC, "\t   Transmit MIS MCU Status\r\n");
         transmit_command(MIS_MCU_STATUS, &status, 1);
         if (status == FINISHED)
            return TRUE;
      
      case IS_SMF_AVAILABLE:
         fprintf(PC, "\t-> is SMF available\r\n");
         fprintf(PC, "\t   Transmit Acknolegde\r\n");
         transmit_command(ACK, 0, 0);
         if (command->content[0] == ALLOW)
         {
            fprintf(PC, "\t\t-> allowd\r\n");
            status = COPYING;
            copy_data();
            status = FINISHED;
         }
         else
            fprintf(PC, "\t\t-> denyed\r\n");
         return FALSE;
   }
}

// -----------------------main-------------------- //
void main()
{
   #ifdef DEBUG_PRINT
   fprintf(PC, "\r\n\r\n");
   for(int8 i = 0; i < 10; i++)
      fprintf(PC, "=");
   fprintf(PC, "\r\nStart main\r\n");
   for(int8 i = 0; i < 10; i++)
      fprintf(PC, "=");
   fprintf(PC, "\r\n\r\n");
   #endif
   
   initialize();
   
   int1 is_finished = FALSE;

   //Start loop
   while(!is_finished)
   {
      //receive anything signal
      if(receive_signal_size > 0)
      {
         printf_byte(receive_signal, receive_signal_size, BOSS);
      
         Command receive_command = make_receive_command(receive_signal, receive_signal_size);
         clear_receive_signal(receive_signal, &receive_signal_size);
         
         if(receive_command.is_exist)
            is_finished = execute_command(&receive_command); 
      }
      
      if(is_finished == 1)
         break;
         
      delay_ms(400);
   }
   fprintf(PC, "\r\n\r\n======\r\n\r\nFinished process.\r\nWait for BOSS PIC turn off me");
   
   while (TRUE)
   {
      fprintf(PC, ".");
      delay_ms(1000);
   }
   
   fprintf(PC, "End main\r\n");
}
