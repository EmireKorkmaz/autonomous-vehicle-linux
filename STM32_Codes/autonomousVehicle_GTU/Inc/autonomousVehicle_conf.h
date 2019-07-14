/**
 * \file        autonomousVehicle_conf.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

#ifndef AUTONOMOUSVEHICLE_CONF_H_
#define AUTONOMOUSVEHICLE_CONF_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include "stm32f4xx_hal.h"
/*------------------------------< Defines >-----------------------------------*/
//Throttle Voltage Values
#define SPEED_0                     (600)
#define SPEED_5                     (900)
#define SPEED_10                    (1300)
#define SPEED_15                    (1700)
#define SPEED_20                    (2100)
#define SPEED_25                    (2700)
#define THROTTLE_VOLTAGE_MIN_VAL    SPEED_0
#define THROTTLE_VOLTAGE_MAX_VAL    SPEED_25
//TODO fix values @ahmet.alperen.bulut
//Steering pulse values
#define STEERING_MAX_VALUE (7500)
/*------------------------------< Typedefs >----------------------------------*/

enum BRAKE_POSITION
{
    BRAKE_RELEASE = 0,
    BRAKE_HALF = 1,
    BRAKE_LOCK = 2,
    BRAKE_STOP = 3
};

typedef enum BRAKE_POSITION BrakePosition;

enum THROTTLE_LOCK_POSITION
{
    THROTTLE_LOCK = 0, //dont apply voltage to motor
    THROTTLE_RELEASE = 1 //apply voltage to motor
};

typedef enum THROTTLE_LOCK_POSITION ThrottleLockPosition;

struct s_PinSettings
{
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
};

typedef struct s_PinSettings pinSettings;
/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* AUTONOMOUSVEHICLE_CONF_H_ */
