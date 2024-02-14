#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "can_driver.h"

// define Queue structure
typedef struct {
    size_t len;
    CANFrames_t _arr[BUFF_SIZE];
    size_t _head;
    size_t _tail;
} Queue_t;

// macro _INC_HEAD for _head increment
#define _INC_HEAD(self) {                   \
    if (self->_head == (BUFF_SIZE - 1)){   \
        self->_head = 0                     \
    } else {                                \
        self->_head += 1;                   \
    }                                       \
}

// macro _INC_TAIL for _tail indexing
#define _INC_TAIL(self) {                   \
    if (self->_tail == (BUFF_SIZE - 1)) {  \
        self->_tail = 0;                    \
    } else {                                \
        self->_tail += 1;                   \
    }                                       \
}

Queue_t Queue_init() // intialize new and empty queue structure
uint8_t Queue_empty (Queue_t* self); // check if queue is empty
void Queue_add(Queue_t* self, CAN_Frame_t val); // add a frame to queue
CAN_Frame_t Queue_get(Queue* self); // remove and return head frame
void Queue_print(Queue_t* self); // print queue
