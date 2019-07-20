/**
 * \file        SteerController.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        6 Tem 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdlib.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
int32_t position;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void steer_init ( )
{
    position = 0;

    //call configure
}

void steer_set_value (int val)
{
    if (val < STEERING_MIN_VALUE || val > STEERING_MAX_VALUE || position == val)
    {
        return;
    }
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Base_Stop(&htim3);
    if (position > val)
    {
        HAL_GPIO_WritePin(STEER_DIR_PIN_GPIO_Port, STEER_DIR_PIN_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(STEER_DIR_PIN_GPIO_Port, STEER_DIR_PIN_Pin, GPIO_PIN_RESET);
    }

    uint32_t abs_val = abs(position - val);

    TIM3->ARR = 2 * abs_val - 1;
    htim3.Init.Period = 2 * abs_val - 1;
    position = val;

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim3);
    //enable pwm and timer
}

int steer_get_value ( )
{
    return position;
}

void steer_test ( )
{

    steer_set_value(1500);
    osDelay(5000);
    steer_set_value(2500);
    osDelay(5000);

    steer_set_value(3500);
    osDelay(5000);

    steer_set_value(-3500);
    osDelay(5000);

    steer_set_value(-7000);
    osDelay(5000);
}
