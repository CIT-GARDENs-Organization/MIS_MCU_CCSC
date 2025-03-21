#ifndef VALUEDIFINE_H
#define VALUEDIFINE_H

// ----------------- command ------------------ //
typedef struct{
   int8 frame_id;
   unsigned int8 content[16];
   int8 size;
   int1 is_exist;
} Command;

// ----------------------Devices--------------------------- //

#define GS        0x00
#define COMPIC    0x01
#define MAINPIC   0x02
#define RESETPIC  0x03
#define FABPIC    0x04
#define BOSSPIC   0x04
#define APRSPIC   0x06
#define CAMMCU    0x07
#define ChoMCU    0x08
#define LabPIC    0x09
#define BHUPIC    0x0A


// --------------------- Frame ID ----------------------- //

#define UPLINK_COMMAND 0x00
#define STATUS_CHECK   0x01
#define IS_SMF_AVAILABLE 0x02

#define MIS_MCU_STATUS 0x01
#define ACK 0x0F



// ---------------------- Status--------------------------- //

// #define OFF       0x00
// #define BOOTING   0x01 used in BOSS PIC only
#define IDLE      0x02
#define BUSY      0x03
#define SMF_COPY_REQ 0x04
#define COPYING   0x05
#define FINISHED  0x06

// ---------------------- is SMF available --------------------------- //
#define ALLOW 0x00
#define DENY  0x01


// ---------------------- SMF data ---------------------- //
int1 smf_data_is_exist = FALSE;

#endif
