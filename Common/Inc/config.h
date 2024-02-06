#pragma once

#include "can_driver.h"
#define MAX_CAN_PAYLOAD_BTYES    8
#define BUFF_SIZE 32

#define MC1     0x10F8109A
#define MC2     0x10F8108D
// CAN ARBITRATIONS FOR OTHER ENTITIES

#define BMS_TEMP 0x10
#define BMS_WARN_OVERTEMP 0x06




// MC1 DEFS 
const Field DRIVING_DIRECTION = {MC1, 0, 1};
const Field MOTOR_SPEED = {MC1, 1, 3};
const Field MOTOR_ERROR_CODE = {MC1, 3, 4}; 


//END MC1 DEFS 

// MC2 DEFS 
const Field BATTERY_VOLTAGE = {MC2, 0, 2};
const Field BATTERY_CURRENT = {MC2, 2, 4};
const Field MOTOR_TEMP = {MC2, 4, 6};
const Field MOTOR_CONTROLLER_TEMP = {MC2, 6, 8};


//END MC2 DEFS 

// BMS BOARD DEFS
    // BEGIN DEFS FOR THERMISTOR MESSAGE 




    // END DEFS FOR THERMISTOR MESSAGE

    // BEGIN DEFS FOR ERROR STATES



    // END DEFS FOR ERROR STATES


// 