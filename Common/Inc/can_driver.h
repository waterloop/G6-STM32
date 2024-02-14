#pragma once
#include <stdint.h>

#define MAX_BYTES 8
uint32_t tx_mailbox;

typedef struct {
    uint32_t id;
    uint8_t start;
    uint8_t end;
} Data_Segment_t;

typedef struct {
    CAN_HandleTypeDef* hcan;
    CAN_TxHeaderTypeDef header;
    uint32_t id;
    uint8_t data[MAX_BYTES];
} CAN_Frame_t;

CAN_Frame_t CAN_frame_init(CAN_HandleTypeDef* handler, uint32_t id);
void send_message(CAN_Frame_t self);
void get_message(CAN_Frame_t* self, uint32_t fifo_number);
uint32_t get_segment(CAN_Frame_t self, Data_Segment_t segment);
uint8_t set_segment(CAN_Frame_t* self, Data_Segment_t segment, uint32_t bytes);
