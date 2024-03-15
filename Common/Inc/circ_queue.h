#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "can_driver.h"

// define Queue structure
typedef struct {
    size_t len;
    CAN_Frame_t _arr[BUFF_SIZE];
    size_t _head;
    size_t _tail;
} Queue_t;

Queue_t queue_init(); // intialize new and empty queue structure
uint8_t queue_empty (Queue_t self); // check if queue is empty
uint8_t queue_full(Queue_t self);
void queue_add(Queue_t* self, CAN_Frame_t val); // add a frame to queue
CAN_Frame_t queue_get(Queue_t* self); // remove and return head frame
void queue_print(Queue_t* self); // print queue
