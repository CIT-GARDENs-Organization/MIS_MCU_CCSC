#ifndef COMMUNICATION_H
#define COMMUNICATION_H

// __________ define ______________

#define MAIN_PIC  0x00
#define COM_PIC   0x01
#define RESET_PIC 0x02
#define FAB_PIC   0x03
#define BOSS_PIC  0x04
#define APRS_PIC  0x05
#define CAM_MCU   0x06
#define CHO_MCU   0x07
#define NAKA_PIC  0x08
#define SATO_PIC  0x09
#define BHU_MCU   0x0A
#define CIGS_PIC  0x0B

#define SELF_DEVICE_ID APRS_PIC // <- change to your device name



#define SFD 0xAA

#define UPLINK_COMMAND        0x00
#define STATUS_CHECK          0x01
#define IS_SMF_AVAILABLE      0x02

#define UPLINK_COMMAND_LENGTH     9
#define STATUS_CHECK_LENGTH       0
#define IS_SMF_AVAILABLE_LENGTH   1

// __________ typedefs _____________

typedef enum {
   MIS_MCU_STATUS = 0x01,
   ACK = 0x0F
} TransmitFrameId;

typedef struct {
    int8 id;
    int8 length;
} FrameID;

#define CONTENT_MAX 32
typedef struct {
    int8 frame_id;
    unsigned int8 content[CONTENT_MAX];
    int8 size;
    int1 is_exist;
} Command;

// ____________ Receive Frame ID _________

volatile FrameID frame_ids[] = {
   {UPLINK_COMMAND, UPLINK_COMMAND_LENGTH}, 
   {STATUS_CHECK, STATUS_CHECK_LENGTH}, 
   {IS_SMF_AVAILABLE, IS_SMF_AVAILABLE_LENGTH}
};


// ______ Receive _______

Command make_receive_command(unsigned int8 receive_signal[], int8 receive_signal_size);

static int8 trim_receive_signal_header(unsigned int8 receive_signal[], int8 receive_signal_size);

static int8 get_content_size(unsigned int8 frame_id);

static int1 check_crc(unsigned int8 frame[], int8 receive_frame_size);

static int1 check_device_id(unsigned int8 device_id);


// ______ Transmit _______

void transmit_command(TransmitFrameId frame_id, unsigned int8 content[], int8 size);

static void transmit(unsigned int8 data[], int8 data_size);

// ______ Common _________

static unsigned int8 calc_crc8(unsigned int8 frame[], int8 payload_size);

#include "./src/communication.c"

#endif
