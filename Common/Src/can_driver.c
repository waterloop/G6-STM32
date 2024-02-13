#include "can_driver.h"

uint32_t tx_mailbox;
CAN_TxHeaderTypeDef tx_header = {
	.IDE = CAN_ID_STD, //only using Standard IDs
	.RTR = CAN_RTR_DATA, //only sending data frames
	.DLC = 8, //data length is always the same
	.TransmitGlobalTime = DISABLE //don't send time-stamp
};

CAN_Frame_t CAN_Frame_t_init(CAN_HandleTypeDef* handler, uint32_t id) {
    CAN_Frame_t ret = {
        .hcan = handler,
        .id = id,
        .data = {0}
        };

    return ret;
}

HAL_StatusTypeDef send_message(CAN_Frame_t self) {
	tx_header.StdId = self.id;
    return HAL_CAN_AddTxMessage(self.hcan, &tx_header, self.data, &tx_mailbox);
}

HAL_StatusTypeDef get_message(CAN_Frame_t* self, uint32_t fifo_number) {
    CAN_RxHeaderTypeDef rx_header;
    HAL_StatusTypeDef ret = HAL_CAN_GetRxMessage(self -> hcan, fifo_number, &rx_header, self -> data);
    if (ret != HAL_OK) {return ret;}

    self -> id = rx_header.StdId;
    return ret;
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
