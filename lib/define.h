#ifndef DEFINE_H
#define DEFINE_H

//__________ Timer _________
#define SEC_IN_A_DAY 86400

// __________ Receive signal buffer _______

#define RECEIVE_BUFFER_MAX 32


//__________ Start Frame Delimiter _________
#define SFD 0xAA

//_____________ Device IDs ____________
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

#define SELF_DEVICE_ID APRS_PIC

//____________ Receive Frame IDs ____________

#define UPLINK_COMMAND        0x00
#define STATUS_CHECK          0x01
#define IS_SMF_AVAILABLE      0x02

#define UPLINK_COMMAND_LENGTH     9
#define STATUS_CHECK_LENGTH       0
#define IS_SMF_AVAILABLE_LENGTH   1

#define RECEIVE_FRAME_KINDS 3

// _________________ content length _____________

#define CONTENT_MAX 32


//____________ Receive Frame IDs ____________


#define MIS_MCU_STATUS 0x01
#define ACK            0x0F


// ________________ Cotntents _______________

typedef enum {
    EXECUTING_MISSION = 0x02,
    IDLE              = 0x03,
    SMF_USE_REQ       = 0x04,
    COPYING           = 0x05,
    FINISHED          = 0x06
} MisMcuStatusContent;


typedef enum {
    ALLOW = 0x00,
    DENY  = 0x01
} IsSmfAvailableContent;


// ________ Mission ______

#define EXECUTED_MISSION_SIZE 64

#define PARAMETER_LENGTH 8


// _________________ SMF _____________

#define SMF_DATA_SIZE 16




#endif

