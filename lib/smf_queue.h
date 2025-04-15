#ifndef SMF_QUEUE_H
#define SMF_QUEUE_H

typedef struct {
    unsigned int32 src;
    unsigned int32 dest;
    unsigned int32 size;
} SmfDataStruct;

#define SMF_DATA_SIZE 16
typedef struct {
   SmfDataStruct smf_data[SMF_DATA_SIZE];
   int8 smf_data_head;
   int8 smf_data_tail;
} SmfQueueStruct;

volatile SmfQueueStruct smf_queue = {0};

// I actually wanted to implement something like a singleton class, 
// but for some reason it didn't work so I used a global variable.
//!SmfQueueStruct get_smf_queue();

void enqueue_smf_data(SmfDataStruct *data);

SmfDataStruct *dequeue_smf_data();

int1 is_empty_smf_data(void);


#include "./src/smf_queue.c"

#endif
