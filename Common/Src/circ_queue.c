#include <stdio.h>
#include "circ_queue.h"

// Function to increment head pointer
void inc_head(Queue_t *self) {
    if (++self->_head == self->_arr + BUFF_SIZE) {
        self->_head = self->_arr;
}

// Function to increment tail pointer
void inc_tail(Queue_t *self) {
    if (++self->_tail == self->_arr + BUFF_SIZE) { 
        self->_tail = self->_arr;
    }
}

// intializes and return a queue with zero length and head/tail indices
Queue_t queue_init() {
    Queue_t ret = {
        .len = 0,
        ._head = 0,
        ._tail = 0,
        ._arr = {{0}}
    };
    return ret
}

// empty queue, returns 1 if true, 0 if false
uint8_t queue_empty(Quene_t self) {
    return self.len == 0;
}

// Check if queue is full
uint8_t queue_full(Queue_t self) {
    return self.len == BUFF_SIZE;
}

// adds new CANFrame to queue
void queue_add(Queue_t* self, CAN_Frame_t frame) {
    if (!(self->len == BUFF_SIZE)) {
        *self->_tail = frame; 
        inc_tail(self); 
        if (self->len > 0) { 
            inc_tail(self); 
        }
        self->len++;
    } else { 
        *self->_head = frame;
        inc_head(self);
        inc_tail(self); 
    }
}

// removes frame from queue
CAN_Frame_t queue_get(Queue_t* self) {
    CAN_Frame_t ret;
    if (self->len == 0) {
        ret.id = 0xFFFFFFFF; // frame id init to 0xFFFFFFFF
    } else {
        ret = *self->_head;
        inc_head(self); 
        self->len--;
    }
    return ret;
}
//print
void queue_print(Queue_t* self) {
    CAN_Frame_t* current = self->_head;
    for (size_t i = 0; i < self->len; i++) {
        printf("Frame ID: %u\n", current->id); 
        if (++current == self->_arr + BUFF_SIZE) { 
            current = self->_arr; 
        }
    }
}