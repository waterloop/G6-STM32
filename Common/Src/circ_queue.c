#include <stdio.h>
#include "config.h"
#include "can_driver.h"
#include "circ_queue.h"

// intializes and return a queue with zero length and head/tail indices
Queue_t Queue_init() {
    Queue_t ret = {
        .len = 0,
        ._head = 0,
        ._tail = 0,
        ._arr = {{0}}
    };
    return ret
}

// empty queue, returns 1 if true, 0 if false
uint8_t Queue_empty(Quene_t* self) {
    return self->len == 0;
}

// adds new CANFrame to queue
void Queue_add(Queue_t* self, CAN_Frame_t frame) {
    if ( !(self->len == BUFF_SIZE) ) {
        if (Queue_empty(self)) {
            self->_arr[self->_head] = frame;
        }
        else {
            _INC_TAIL(self);
            self->_arr[self->_tail] = frame;
        }
        self->len += 1;
    }
    else {
        self->_arr[self->_head] = val;
        _INC_HEAD(self);
        _INC_TAIL(self);
    }
}

// removes frame from queue
CAN_Frame_t Queue_get(Queue_t* self) {
    if (self->len == 0) {
        CAN_Frame_t ret = {

        }
    }
    else { 
        CAN_Frame_t ret = self->_arr[self->_head];
        _INC_HEAD(self);
        self->len -= 1;
        return ret
    }
}

//print
void Queue_print(Queue_t* self) {
    for (size_t i = 0; i < (BUFF_SIZE - 1); i++) {
        printf(self->_arr[i])
    }
}