#include "./lib/main.h"

//____________ intrrupts ____________

#define SEC_IN_A_DAY 86400
#INT_TIMER0
void TIMER0_isr(void) 
{
   // every 0.01 sec interrupts
   set_timer0(100);

   if (++subsec >= 100)
   {
      subsec = 0;
      sec++;

      if (sec >= SEC_IN_A_DAY)
      {
         sec -= SEC_IN_A_DAY;
         day++;
      }
   }
}

#INT_RDA
void RDA_isr(void)
{
   if (!(status == EXECUTING_MISSION || status == COPYING) || is_use_smf_req_in_mission)
   {
      if (boss_receive_buffer_size < RECEIVE_BUFFER_MAX)
         boss_receive_buffer[boss_receive_buffer_size++] = fgetc(BOSS);
      else
      {
         fprintf(PC, "\r\nOverflow BOSS receive signal buffer!!!\r\n\r\n");
         boss_receive_buffer[RECEIVE_BUFFER_MAX-1] = fgetc(BOSS);
      }
   }
}

void clear_receive_signal(unsigned int8 receive_signal[], int8 *receive_signal_size)
{
   memset(receive_signal, 0x00, *receive_signal_size);
   *receive_signal_size = 0;
}


//____________ initialize ____________

void initialize(void)
{
   fprintf(PC, "Start setting\r\n");
   setup_lcd(LCD_DISABLED);
   setup_timer_0(T0_INTERNAL | T0_DIV_256 | RTCC_8_BIT);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   fprintf(PC, "End setting\r\n");
}


// ___________ command execution ___________

int1 execute_command(Command *command)
{
   fprintf(PC, "\r\nStart execute_command\r\n");
   
   switch(command->frame_id)
   {
      case UPLINK_COMMAND:
         fprintf(PC, "\t-> Uplink command\r\n");
         fprintf(PC, "\t   Transmit Acknolegde\r\n");
         transmit_ack();

         status = EXECUTING_MISSION;
         execute_mission(command->content);
         if (is_empty_smf_data())
         {
            if (duration_sec < sec)
               status = FINISHED;
            else
               status = IDLE;
         }
         else
            status = SMF_USE_REQ;
         break;
      
      case STATUS_CHECK:
         fprintf(PC, "\t-> Status check\r\n");
         fprintf(PC, "\t\t-> My status is %d\r\n", status);
         fprintf(PC, "\t   Transmit MIS MCU Status\r\n");
         transmit_status();
         if (status == FINISHED)
         {
            fprintf(PC, "finished in status_check\r\n");
            return TRUE;
         }
         break;
      
      case IS_SMF_AVAILABLE:
         fprintf(PC, "\t-> is SMF available\r\n");
         fprintf(PC, "\t   Transmit Acknolegde\r\n");
         transmit_ack();
         if (command->content[0] == ALLOW)
         {
            fprintf(PC, "\t\t-> allowd\r\n");
            status = COPYING;
            copy_data();
            status = FINISHED;
         }
         else
            fprintf(PC, "\t\t-> denyed\r\n");
   }
   return FALSE;
}


// ___________ main functoin _______________

void main()
{
   fprintf(PC, "\r\n\r\n");
   for (int8 i = 0; i < 3; i++)
   {
      for (int8 j = 0; j < 31; j++)
         fprintf(PC, "_");
      fprintf(PC, "\r\n");
   }
   fprintf(PC, "___________Start main__________\r\n\r\n");
   
   
   initialize();
   
   int1 is_finished = FALSE;

   //Start loop
   while(!is_finished)
   {
      // handle from boss commands
      if(boss_receive_buffer_size > 0)
      {
         Command command = make_receive_command(boss_receive_buffer, boss_receive_buffer_size);
         clear_receive_signal(boss_receive_buffer, &boss_receive_buffer_size);
            
         if(command.is_exist)
            is_finished = execute_command(&command); 
      }
      
      // check mis mcu duration seconds (used in mission.c \ void continue_mis_mcu(int16 duration_sec))
      if (status == IDLE)
         if (duration_sec < sec && is_empty_smf_data())
            status = FINISHED;
      
      // check `is break while loop`
      if(is_finished == TRUE)
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
