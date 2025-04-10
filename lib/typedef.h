#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef struct {
    int8 id;
    int8 length;
} FrameID;


typedef struct {
    int8 frame_id;
    unsigned int8 content[CONTENT_MAX];
    int8 size;
    int1 is_exist;
} Command;


typedef struct {
    unsigned int32 src;
    unsigned int32 dest;
    unsigned int32 size;
} SmfDataStruct;


#endif

