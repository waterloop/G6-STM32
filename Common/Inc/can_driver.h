#pragma once
#include <stdint.h>

#define MAX_BYTES 8

typedef struct {
    uint32_t id;
    uint8_t start;
    uint8_t end;
} DataSegment;

typedef struct {
    CAN_HandleTypeDef* hcan;
    uint32_t id;
    uint8_t data[MAX_BYTES];
} CANFrame;

CANFrame CANFrame_init(CAN_HandleTypeDef* handler, uint32_t id);
HAL_StatusTypeDef send_message(CANFrame self, uint32_t rtr);
HAL_StatusTypeDef get_message(CANFrame* self, uint32_t fifo_number);
uint32_t get_segment(CANFrame self, DataSegment segment);
uint8_t set_segment(CANFrame* self, DataSegment segment, uint32_t bytes);
