#pragma once
#include <stdint.h>

#define MAX_BYTES 8

typedef struct {
    uint32_t id;
    uint8_t start;
    uint8_t end;
} Data_Segment_t;

typedef struct {
    CAN_HandleTypeDef* hcan;
    uint32_t id_type;
    uint32_t rtr;
    uint32_t data_length;
    uint32_t time_stamp;
    uint32_t id;
    uint8_t data[MAX_BYTES];
} CAN_Frame_t;

CAN_Frame_t CAN_frame_init(CAN_HandleTypeDef* handler, uint32_t id);
void CAN_send_frame(CAN_Frame_t self);
CAN_Frame_t CAN_get_frame(CAN_HandleTypeDef* handler, uint32_t fifo_number);
uint32_t CAN_get_segment(CAN_Frame_t self, Data_Segment_t segment);
uint8_t CAN_set_segment(CAN_Frame_t* self, Data_Segment_t segment, uint32_t bytes);
