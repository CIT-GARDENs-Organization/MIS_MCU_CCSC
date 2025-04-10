void check_and_respond_to_boss()
{
   if (kbhit())
   {
      fgetc(BOSS);
      transmit_status();
   }
}

void enqueue_smf_data(unsigned int32 dest, unsigned int32 src, unsigned int32 size)
{
   int8 next_tail = (smf_data_tail + 1) % SMF_DATA_SIZE;

   if(next_tail == smf_data_head)
      fprintf(PC, "SMF data list is full!!!\r\n");
      
   else
   {
      smf_data[smf_data_tail].src = src;
      smf_data[smf_data_tail].dest = dest;
      smf_data[smf_data_tail].size = size;

      smf_data_tail = next_tail;
   }
}


int1 req_use_smf()
{
   fprintf(PC, "Start SMF using reqest seaquence\r\n");
   status = SMF_USE_REQ;
   is_use_smf_req_in_mission = TRUE;
   
   while (TRUE)
   {
      for (int16 i = 0; i < 1200; i++) // 10 min
      {
         if (boss_receive_buffer_size > 0)
         {
            Command command = make_receive_command(boss_receive_buffer, boss_receive_buffer_size);
            clear_receive_signal(boss_receive_buffer, &boss_receive_buffer_size);
            if (command.frame_id == STATUS_CHECK)
            {
               transmit_status();
               break;
            }
            else
            {
               fprintf(PC, "Error! Receiving command inconsistent with the design\r\n");
            }
         }
         delay_ms(500);
      }
      
      for (int16 i = 0; i < 1200; i++) // 10 min
      {
         if (boss_receive_buffer_size > 0)
         {
            Command command = make_receive_command(boss_receive_buffer, boss_receive_buffer_size); 
            clear_receive_signal(boss_receive_buffer, &boss_receive_buffer_size);
            if (command.frame_id == IS_SMF_AVAILABLE)
            {
               if (command.content[0] == ALLOW)
               {
                  fprintf(PC, "SMF use request allowed\r\n");
                  transmit_ack();
                  goto NEXT;
               }
               else
               {
                  fprintf(PC, "SMF use request denyed\r\n");
                  fprintf(PC, "Retry request to BOSS PIC\r\n");
                  transmit_ack();
                  break;
               }
            }
            else
            {
               fprintf(PC, "Error! Receiving command inconsistent with the design\r\n");
            }
         }
         delay_ms(500);
      }
   }
   
NEXT:
   is_use_smf_req_in_mission = FALSE;
   status = COPYING;
   return TRUE;
   fprintf(PC, "End SMF using reqest seaquence\r\n");
}

void finished_use_smf()
{
   status = EXECUTING_MISSION;
}

void executed_mission_pop(void)
{
   executed_mission[executed_mission_count--] = 0x00;
}

void continue_mis_mcu(int16 duration_second)
{  
   duration_sec = duration_second + sec;
}


//!void update_time(unsigned int8 raw_time[])
//!{  
//!   unsigned int32 time;
//!   memcpy(&time, raw_time, 4);
//!   
//!   day = (time >> 22) & 0x000003FF;
//!   sec = time & 0x0001FFFF;
//!   //unsigned int8  subsec = (time >> 18) & 0x0000000F;
//!   // int1 absolute_flag = time >> 17 & 0x00000001
//!}
