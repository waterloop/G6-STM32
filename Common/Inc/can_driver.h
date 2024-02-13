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
    uint32_t id;
    uint8_t data[MAX_BYTES];
} CAN_Frame_t;

CAN_Frame_t CAN_frame_init(CAN_HandleTypeDef* handler, uint32_t id);
HAL_StatusTypeDef send_message(CAN_Frame_t self);
HAL_StatusTypeDef get_message(CAN_Frame_t* self, uint32_t fifo_number);
uint32_t get_segment(CAN_Frame_t self, Data_Segment_t segment);
uint8_t set_segment(CAN_Frame_t* self, Data_Segment_t segment, uint32_t bytes);
