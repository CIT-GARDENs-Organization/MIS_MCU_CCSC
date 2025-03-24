#include "Mission.h"

//____________ main mission function _______________

void execute_mission(unsigned int8 *content)
{
//!   // timer update
//!   update_time(content);
//!   fprintf(PC, "\r\nUpdate the time setting\r\n");
//!   fprintf(PC, "\t-> Day: \t%lu\r\n", day);
//!   fprintf(PC, "\t-> Hour: \t%lu\r\n", sec / 3600);
//!   fprintf(PC, "\t-> Minute: \t%lu\r\n", (sec / 60) % 60);
//!   fprintf(PC, "\t-> Second: \t%lu\r\n", sec % 60);
//!   
   // record to executed mission list
   unsigned int8 command_id = content[0];
   unsigned int8 *parameter = &content[1];
   for (int i = 0; i < executed_mission_count; i++)
      if (command_id == executed_mission[i])
      {
         fprintf(PC, "\r\nThis  mission is executed\r\n\t-> 0x%d\r\n", command_id);
         return;
      }
   if (executed_mission_count != EXECUTED_MISSION_SIZE)
      executed_mission[executed_mission_count++] = command_id;
   else
      fprintf(PC, "[WARN]  overflow executed_mission list");
   
   
   // execution mission
   fprintf(PC, "\r\n______________________________\r\n_____Start execute_mission_____\r\n\r\n");
   fprintf(PC, "Command ID: %X\r\n\r\n", command_id);
   switch(command_id)
   {
      case 0x00:
         example_00(parameter);
         break;
      case 0x01:
         example_01(parameter);
         break;
      default:
         fprintf(PC, "\t\t-> Invalid CMD ID!\r\n");
   }
   fprintf(PC, "\r\n______End execute_mission______\r\n_______________________________\r\n");
}

// _________________ missions ______________________

void example_00(unsigned int8 parameter[])
{
   fprintf(PC, "Start example_00\r\n");
   
   // accept continuous execute
   executed_mission_pop();
   fprintf(PC, "(This mission can execute many time as you want)\r\n");
    
   // anything do
   fprintf(PC, "executing");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".\r\n");
   
   // order Copy to SMF data
   fprintf(PC, "order Copy smf_data\r\n");
   unsigned int32 smf_data_source_address = 0x00005000; // (in self Flash memory)
   unsigned int32 smf_data_destination_address = 0x00103D00; // (in SMF)
   unsigned int32 data_size = 0x00000080;
   enqueue_smf_data(smf_data_source_address, smf_data_destination_address, data_size);
   
   fprintf(PC, "End example_00\r\n");
   
}

void example_01(unsigned int8 parameter[])
{
   fprintf(PC, "Start example_01\r\n");
   fprintf(PC, "executing");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".\r\n");
   fprintf(PC, "End example_01\r\n");
}


//___________ others ________________

void executed_mission_pop(void)
{
   executed_mission[executed_mission_count--] = 0x00;
}

void enqueue_smf_data(unsigned int32 src, unsigned int32 dest, unsigned int32 size)
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

void update_time(unsigned int8 raw_time[])
{  
   unsigned int32 time;
   memcpy(&time, raw_time, 4);
   
   day = (time >> 22) & 0x000003FF;
   sec = time & 0x0001FFFF;
   //unsigned int8  subsec = (time >> 18) & 0x0000000F;
   // int1 absolute_flag = time >> 17 & 0x00000001
}
