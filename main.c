#include "./main.h"


void initialize(void)
{
   fprintf(PC, "Start setting\r\n");
   setup_lcd(LCD_DISABLED);
   
   setup_timer();
   setup_uart_to_boss();

   enable_interrupts(GLOBAL);
   fprintf(PC, "End setting\r\n");
}


// ___________ command execution ___________

int1 execute_command(Command *command)
{
   fprintf(PC, "Start execute_command\r\n");
   
   switch(command->frame_id)
   {
      case UPLINK_COMMAND:
         fprintf(PC, "\t-> Uplink command\r\n");
         fprintf(PC, "\t   Transmit Acknolegde\r\n");
         transmit_ack();

         status[0] = EXECUTING_MISSION;
         execute_mission(command->content);
         if (is_empty_smf_data())
            status[0] = FINISHED;
         else
            status[0] = SMF_USE_REQ;
         break;
      
      case STATUS_CHECK:
         fprintf(PC, "\t-> Status check\r\n");
         fprintf(PC, "\t   Transmit MIS MCU Status\r\n");
         transmit_status();
         if (status[0] == FINISHED)
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
            status[0] = COPYING;
            copy_data();
            status[0] = FINISHED;
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
      if(boss_receive_buffer_size > 0)
      {
         Command command = make_command(boss_receive_buffer, boss_receive_buffer_size);
         
         fprintf(PC, "FrameID: %1X\r\n", command.frame_id);
         fprintf(PC, "payload: ");
         for(int8 i = 0; i < command.size; i++)
            fprintf(PC, "%X ", command.content[i]);
         fprintf(PC, "\r\n\r\n");
         
         clear_receive_signal(boss_receive_buffer, &boss_receive_buffer_size);
            
         if(command.is_exist)
            is_finished = execute_command(&command); 
      }
      
      // check `is break while loop`
      if(is_finished == TRUE)
         break;
         
      delay_ms(400); // this is meaning less number
   }
   
   fprintf(PC, "\r\n\r\n___________End main__________\r\n\r\n");
   for (int8 i = 0; i < 3; i++)
   {
      for (int8 j = 0; j < 31; j++)
         fprintf(PC, "_");
      fprintf(PC, "\r\n");
   }
   fprintf(PC, "\r\n\r\n");

   
   
   fprintf(PC, "\r\n\r\n======\r\n\r\nFinished process.\r\nWait for BOSS PIC turn off me");
   
   while (TRUE)
   {
      fprintf(PC, ".");
      delay_ms(1000);
   }
   
   fprintf(PC, "End main\r\n");
}

