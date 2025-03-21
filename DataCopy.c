typedef struct{
   unsigned int32 src;
   unsigned int32 dest;
   unsigned int32 size;
}SmfDataStruct;
#define SMF_DATA_SIZE 16
volatile int8 smf_data_head = 0;
volatile int8 smf_data_tail = 0;

SmfDataStruct smf_data[SMF_DATA_SIZE] = { {0x00} };

void enqueue_smf_data(unsigned int32 src, unsigned int32 dest, unsigned int32 size)
{
   if((smf_data_tail + 1) % SMF_DATA_SIZE == smf_data_head)
      fprintf(PC, "SMF data list is full!!!\r\n");
   else
   {
      smf_data_tail = ++smf_data_tail % SMF_DATA_SIZE;
      smf_data[smf_data_tail].src = src;
      smf_data[smf_data_tail].dest = dest;
      smf_data[smf_data_tail].size = size;
   }
}

SmfDataStruct dequeue_smf_data(void)
{
   if (smf_data_head == smf_data_tail)
      fprintf(PC, "SMF data list is empty\r\n");
   else
   {
      smf_data_head = ++smf_data_head % SMF_DATA_SIZE;
      return smf_data[smf_data_head];
   }
}

int1 is_empty_smf_data(void)
{
   return smf_data_head == smf_data_tail;
}
void copy_data()
{
   fprintf(PC, "\r\nStart copy_data\r\n");
   fprintf(PC, "Copying.");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");
   delay_ms(1000);
   fprintf(PC, ".");   
   delay_ms(1000);
   fprintf(PC, ".\r\n");   
   delay_ms(1000);
   fprintf(PC, "End copy_data\r\n");
}
