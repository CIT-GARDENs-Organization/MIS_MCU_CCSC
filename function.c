//#include "function.h"

//initialize setup about timer, interrupt
void initialize(void)
{
   fprintf(PC, "Start setting\r\n");
   setup_lcd(LCD_DISABLED);
   setup_timer_0(T0_INTERNAL | T0_DIV_64);
   set_timer0(0);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   fprintf(PC, "End setting\r\n");
}


#define SELF_DEVICE_ID 0x07
#define SFD 0xAA

int8 make_frame(unsigned int8 receive_signal[], int8 receive_signal_size)
{
   int8 i = 0;
   for(i = 0; i < receive_signal_size-1; i++) // if SFD find 
      if(receive_signal[i] == SFD)
         return i+1;
   if (receive_signal[i] == SFD)
   {
      fprintf(PC, "signal end with SFD\r\n");
      return -1;
   }
   else
   {
      fprintf(PC, "don't find SFD\r\n");
      return -1;
   }
   
}

int8 get_content_size(unsigned int8 frame_id)
{
   switch(frame_id)
   {
      case 0x00: //UPLINK_COMMAND
         return 9;
      case 0x01: //STATUS_CHECK
         return 1;
      case 0x02:
         return 0;
      default:
         fprintf(PC, "\t-> Invalid frame ID is recived: 0x%1X\r\n", frame_id);
         return -1;
   }
}


unsigned int8 calc_crc(unsigned int8 frame[], int8 payload_size)
{
   unsigned int8 crc = frame[0], i = 1;
   while(i < payload_size)
      crc ^= frame[i++];
   return crc;
}

int1 check_crc(unsigned int8 frame[], int8 receive_frame_size)
{
   unsigned int8 received_crc = frame[receive_frame_size-1]; // '1' is for crc
   unsigned int8 collect_crc = calc_crc(frame, receive_frame_size-1);
   if (received_crc == collect_crc)
      return TRUE;
   else
   {
      fprintf(PC, "\t-> CRC error!\r\n");
      fprintf(PC, "\t\t-> received CRC: %X\r\n", received_crc);
      fprintf(PC, "\t\t   collect CRC : %X\r\n", collect_crc);
      return FALSE;
   }
}

int1 check_device_id(unsigned int8 device_id)
{
   if (SELF_DEVICE_ID == device_id)
      return TRUE;
   else
   {
      fprintf(PC, "\t-> device ID received");
      fprintf(PC, "\t\t-> received:     %X", device_id);
      fprintf(PC, "\t\t   My device ID: %X", SELF_DEVICE_ID);
      return FALSE;  
   }
}

//Format Rx signal to frame
Command make_receive_command(unsigned int8 receive_signal[], int8 receive_signal_size)
{
   Command command = {0, 0, 0, FALSE};
   fprintf(PC, "Start make_receive_command\r\n");

   int8 frame_start_position = make_frame(receive_signal, receive_signal_size);
   if (frame_start_position == -1)
      return command;
      
   unsigned int8 *frame = &receive_signal[frame_start_position];
   
   int8 frame_id = frame[0] & 0x0F;
   int8 content_size = get_content_size(frame_id);
   if (content_size == -1)
      return command;
      
   int8 receive_frame_size = receive_signal_size - frame_start_position;
   
      
   if (!check_crc(frame, receive_frame_size))
      return command;
   
   if(!check_device_id((frame[0] & 0xF0) >> 4))
      return command;

   command.frame_id = frame_id;
   memcpy(command.content, &frame[1], receive_frame_size-2); // '2' is for Decive ID, Frame ID and CRC
   command.size = receive_frame_size-2;
   command.is_exist = TRUE;
   
   fprintf(PC, "Made receive command\r\n");
   fprintf(PC, "\t-> Frame ID: %X\r\n", command.frame_id);
   fprintf(PC, "\t-> Content : ");
   for(int i = 0; i < command.size; i++)
      fprintf(PC, "%X ", command.content[i]);
   fprintf(PC, "\r\n");
   fprintf(PC, "End make_recive_command\r\n");
   return command;
}

void transmit(unsigned int8 data[], int8 data_size)
{
   for(int i = 0; i < data_size; i++)
      fputc(data[i], BOSS);
   #ifdef DEBUG_PRINT
   fprintf(PC, "Transit command\r\n\t-> ");
   for(int i = 0; i < data_size; i++)
      fprintf(PC, "%X ", data[i]);
   fprintf(PC, "\r\n");
   #endif
}

void transmit_command(int8 frame_id, unsigned int8 content[], int8 size)
{
   unsigned int8 data[16];
   data[0] = SFD;
   data[1] = (BOSSPIC << 4) | frame_id;
   fprintf(PC, "content[0] : %X", content[0]);
   memcpy(&data[2], content, size);
   int8 payload_size = 2 + size; // '2' is for Device ID and Frame ID plus CRC
   data[payload_size] = calc_crc(&data[1], payload_size-1); // '1' is for CRC
   int8 data_size = payload_size + 1; // '1' is for CRC
   
   transmit(data, data_size);
}
