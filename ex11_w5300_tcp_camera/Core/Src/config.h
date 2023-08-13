#include "main.h"

//------------------------------------------------------------------------------
#define LED_PORT1 GPIOC
#define LED_BIT1 GPIO_PIN_2
#define Led1On() HAL_GPIO_WritePin(LED_PORT1, LED_BIT1, GPIO_PIN_SET);
#define Led1Off() HAL_GPIO_WritePin(LED_PORT1, LED_BIT1, GPIO_PIN_RESET);


#define LED_PORT2 GPIOB
#define LED_BIT2 GPIO_PIN_1
#define Led2On() HAL_GPIO_WritePin(LED_PORT2, LED_BIT2, GPIO_PIN_SET);
#define Led2Off() HAL_GPIO_WritePin(LED_PORT2, LED_BIT2, GPIO_PIN_RESET);
//------------------------------------------------------------------------------






//-----------------------------------------------------------------------------
#define _USE_W5300_OPTIMIZE				0

#define W5300_BANK_ADDR                 ((uint32_t)0x64000000)
#define _W5300_DATA(p)                  (*(volatile uint16_t*) (W5300_BANK_ADDR + (p<<1)))


#define RESET_W5300_GPIO_Port			GPIOH
#define RESET_W5300_Pin					GPIO_PIN_15


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define hI2C_Cam hi2c1

#define  OV2640_ID						0x26
#define CAMERA_I2C_ADDRESS              0x60


#define DCMI_XCLX_Pin GPIO_PIN_8
#define DCMI_XCLX_GPIO_Port GPIOA

//#define CAMERA_RESET_Pin GPIO_PIN_2
//#define CAMERA_RESET_GPIO_Port GPIOE

#define CAMERA_RESET_Pin GPIO_PIN_3
#define CAMERA_RESET_GPIO_Port GPIOE
//-----------------------------------------------------------------------------
                                        
