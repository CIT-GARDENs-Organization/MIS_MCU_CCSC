void enqueue_smf_data(SmfDataStruct *data)
{   
   int8 next_tail = (smf_queue.smf_data_tail + 1) % SMF_DATA_SIZE;

   if(next_tail == smf_queue.smf_data_head)
      fprintf(PC, "SMF data list is full!!!\r\n");
      
   else
   {
      smf_queue.smf_data[smf_queue.smf_data_tail].mission_type = data->mission_type;
      smf_queue.smf_data[smf_queue.smf_data_tail].src         = data->src;
      smf_queue.smf_data[smf_queue.smf_data_tail].size        = data->size;

      smf_queue.smf_data_tail = next_tail;
   }
}

SmfDataStruct *dequeue_smf_data()
{
   if (smf_queue.smf_data_head == smf_queue.smf_data_tail)
   {
      fprintf(PC, "SMF data list is empty\r\n");
      return 0x00;
   }
   else
   {
      int8 current_head = smf_queue.smf_data_head;
      smf_queue.smf_data_head = (smf_queue.smf_data_head + 1) % SMF_DATA_SIZE;
      return &smf_queue.smf_data[current_head];
   }
}

int1 is_empty_smf_data(void)
{
   return smf_queue.smf_data_head == smf_queue.smf_data_tail;
}


MissionTypeStruct getMissionTypeStruct(MissionType mis_type)
{
   MissionTypeStruct mis_struct = {0};
   
   if (mis_type == APRS_DATA)
   {
      mis_struct.start_address   = 0x02400000;
      mis_struct.end_address     = 0x02500FFF;
      mis_struct.mission_flag    = 0b10000000;
   }
   else if (mis_type == IN_VEHICLE)
   {
      mis_struct.start_address   = 0x02501000;
      mis_struct.end_address     = 0x02501FFF;
      mis_struct.mission_flag    = 0b10000001;  
   }
   else if (mis_type == ECOSYSTEM_DATA)
   {
      mis_struct.start_address   = 0x02506000;
      mis_struct.end_address     = 0x02516FFF;
      mis_struct.mission_flag    = 0b10000011;  
   }
   else if (mis_type == APRS_PIC_LOG)
   {
      mis_struct.start_address   = 0x02517000;
      mis_struct.end_address     = 0x02517FFF;
      mis_struct.mission_flag    = 0b10000100;  
   }
   else
   {
      // undefined mission type. output `ff` as default
      mis_struct.start_address   = 0xFFFFFFFF;
      mis_struct.end_address     = 0xFFFFFFFF;
      mis_struct.mission_flag    = 0b11111111; 
   }
   
   return mis_struct;
}

