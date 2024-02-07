#pragma once

#include <stdint.h>

#include <stddef.h>
#include "config.h"
#define MAX_BYTES 8

typedef struct {
    uint32_t id;
    uint8_t start;
    uint8_t end;
} DataSegment;

typedef struct {
   // CAN_HandleTypeDef* hcan;
    uint32_t id;
    uint8_t data[MAX_BYTES];
} CANFrame;