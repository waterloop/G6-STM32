#include "can_driver.h"

CAN_Frame_t CAN_Frame_t_init(CAN_HandleTypeDef* handler, uint32_t id) {
    CAN_Frame_t ret = {
        .hcan = handler,
        .header.IDE = CAN_ID_STD,
        .header.RTR = CAN_RTR_DATA,
        .header.DLC = 8,
        .header.TransmitGlobalTime = DISABLE,
        .id = id,
        .data = {0}
        };

    return ret;
}

void send_message(CAN_Frame_t self) {
	self.header.StdId = self.id;
    if (HAL_CAN_AddTxMessage(self.hcan, &(self.header), self.data, &tx_mailbox) != HAL_OK) {
        Error_Handler();
    }
}

void get_message(CAN_Frame_t* self, uint32_t fifo_number) {
    CAN_RxHeaderTypeDef rx_header;
    if (HAL_CAN_GetRxMessage(self -> hcan, fifo_number, &rx_header, self -> data) != HAL_OK) {
        Error_Handler();
    }

    self -> id = rx_header.StdId;
}

uint32_t get_segment(CAN_Frame_t self, Data_Segment_t segment) {
    if (self.id != segment.id) {
        return 0xFFFFFFFF;
    }

    uint32_t ret = 0;
    uint8_t length = segment.end - segment.start;
    for(uint8_t i = 0; i <= length; i++) {
        ret |= (self.data[(segment.start - 1) + i] << (8 * i));
    }

    return ret;
}

uint8_t set_segment(CAN_Frame_t* self, Data_Segment_t segment, uint32_t data) {
    if ((self -> id) != segment.id) {
        return 1;
    }

    uint8_t length = segment.end - segment.start;
    for(uint8_t i = 0; i <= length; i++) {
        self -> data[(segment.start - 1) + i] = ((data >> (8 * i)) & 0xFF);
    }
    
    return 0;
}
