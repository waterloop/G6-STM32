#include <stdio.h>
#include "circ_queue.h"

static void inc_head(Queue_t *self) {
    if (++self->_head == self->_arr+self->BUFF_SIZE) {
        self->_head = self->_arr;
    }
}

static void inc_tail(Queue_t *self) {
    if (++self->_tail == self->_arr+self->BUFF_SIZE) {
        self->_tail = self->_arr;
    }
}

Queue_t queue_init() {
    Queue_t ret;
    ret.len = 0;
    ret._head = ret._arr;
    ret._tail = ret._arr;
    for(int i = 0; i < BUFF_SIZE; i++) {
        ret._arr[i] = (CAN_Frame_t){0}; // Assuming CAN_Frame_t can be zero-initialized
    }
    return ret;
}

// empty queue, returns 1 if true, 0 if false
uint8_t queue_empty(Queue_t self) {
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
