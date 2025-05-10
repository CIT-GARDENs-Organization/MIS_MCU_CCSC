//____________ main mission function _______________

void execute_mission(unsigned int8 *content)
{
   // record to executed mission list
   unsigned int8 command_id = content[0];
   unsigned int8 *parameter = &content[1];
   
   if (is_executed_mission(command_id))
   {
      fprintf(PC, "\r\nThis  mission is executed\r\n\t-> 0x%d\r\n", command_id);
      return;
   }
   
   add_executed_mission(command_id);
   
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
      case 0x02:
         example_02(parameter);
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
   
   fprintf(PC, "parameter : ");
   for(int8 i = 0; i < PARAMETER_LENGTH; i++)
      fprintf(PC, "%X ", parameter[i]);
   fprintf(PC, "\r\n");
   
   // accept continuous execute
   executed_mission_pop();
   fprintf(PC, "(This mission can execute many time as you want)\r\n");
    
   // anything do
   fprintf(PC, "executing");
   delay_ms(1000);
   for (int8 i = 0; i < 5; i++)
   {
      fprintf(PC, ".");
      delay_ms(1000);
   }
   fprintf(PC, ".\r\n");
   
   // order Copy to SMF data
   fprintf(PC, "order Copy smf_data\r\n");
   unsigned int32 smf_data_destination_address = 0x00103D00; // (in SMF)
   unsigned int32 fm_data_source_address = 0x00005000; // (in self Flash memory)
   unsigned int32 data_size = 0x00000080;
   SmfDataStruct data;
   data.dest = smf_data_destination_address;
   data.src = fm_data_source_address;
   data.size = data_size;
   enqueue_smf_data(&data);
   
   fprintf(PC, "End example_00\r\n");
   
}

void example_01(unsigned int8 parameter[])
{
   fprintf(PC, "Start example_01\r\n");
   
   fprintf(PC, "parameter : ");
   for(int8 i = 0; i < PARAMETER_LENGTH; i++)
      fprintf(PC, "%X ", parameter[i]);
   fprintf(PC, "\r\n");
   
   fprintf(PC, "This mission wait for 5 seconds\r\n");
   fprintf(PC, "executing");
   for (int8 i = 0; i < 5; i++)
   {
      delay_ms(1000);
      fprintf(PC, ".");
   }
   fprintf(PC, "\r\n");
   fprintf(PC, "End example_01\r\n");
}

void example_02(unsigned int8 parameter[])
{
   fprintf(PC, "Start example_02\r\n");
   
   fprintf(PC, "parameter : ");
   for(int8 i = 0; i < PARAMETER_LENGTH; i++)
      fprintf(PC, "%X ", parameter[i]);
   fprintf(PC, "\r\n");
   
   fprintf(PC, "This mission will first access smf and then wait for 5 seconds\r\n");
   if (req_use_smf())
   {
      fprintf(PC, "Access to SMF");
      for (int8 i = 0; i < 5; i++)
      {
         fprintf(PC, ".");
         delay_ms(1000);
      }
      fprintf(PC, "\r\n");
      fprintf(PC, "End use SMF\r\n");
      
      finished_use_smf();
      
      fprintf(PC, "wait for 10 seconods (exec mission sim)\r\n");
      for (int8 i = 0; i < 30; i++)
      {
         check_and_respond_to_boss();
         fprintf(PC, ".");
         delay_ms(1000);
      }
   }
   else
      fprintf(PC, "Failure to Access to SMF");
      
   fprintf(PC, "End example_02\r\n");
}

// EOF
