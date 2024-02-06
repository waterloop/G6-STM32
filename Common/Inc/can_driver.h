#pragma once

#include <stdint.h>

#include <stddef.h>
#include "config.h"

typedef struct {
    uint32_t can_id; // ID of the message 
    uint8_t start; // starting byte 
    uint8_t end;  // ending byte


} Field;

