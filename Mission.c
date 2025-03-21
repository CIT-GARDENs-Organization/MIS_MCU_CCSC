void example_00()
{
   fprintf(PC, "Start example_00\r\n");
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
   fprintf(PC, "make smf_data\r\n");
   smf_data_is_exist = TRUE;
   fprintf(PC, "End example_00\r\n");
   
}

void example_01()
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

void execute_mission(unsigned int8 *content)
{
   fprintf(PC, "Start execute_mission\r\n");
   fprintf(PC, "\t-> CMD ID: %X\r\n\r\n", content[0]);
   switch(content[0])
   {
      case 0x00:
         example_00();
         break;
      case 0x01:
         example_01();
         break;
      default:
         fprintf(PC, "\t\t-> Invalid CMD ID!\r\n");
   }
   return;
}
