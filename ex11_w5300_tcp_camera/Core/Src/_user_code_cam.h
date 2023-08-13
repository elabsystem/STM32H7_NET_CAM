#include "ov2640.h"


#define _IMAGE_SIZE_X 640
#define _IMAGE_SIZE_Y 480

#define _UDP_TX_BUF_RATE	1


#define _FRAME_BUF_SIZE	(_IMAGE_SIZE_X*1)

volatile uint16_t FrameBuffer[_FRAME_BUF_SIZE];



volatile uint32_t gCameraFrameFlag = 0;
volatile uint32_t gCameraLineFlag = 0;

uint32_t gLineCnt = 0;
uint32_t gFrameCnt = 0;



void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{

}


void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	gCameraFrameFlag++;
}

void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	gCameraLineFlag++;
}



static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&hI2C_Cam, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 100);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    //I2Cx_Error(Addr);
  }
}


static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;

  status = HAL_I2C_Mem_Read(&hI2C_Cam, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    //I2Cx_Error(Addr);
  }
  return Value;
}

/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Camera delay
  * @param  Delay: Delay in ms
  */
void CAMERA_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

void CAMERA_IO_Init(void)
{
	HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

void _init_cam(void)
{
	volatile uint32_t idc = ov2640_ReadID(CAMERA_I2C_ADDRESS);
	printf("camera id = %x\r\n", idc);

	ov2640_Init(CAMERA_I2C_ADDRESS, CAMERA_R640x480);
}

void CameraStat(void)
{
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&FrameBuffer, _IMAGE_SIZE_X*_UDP_TX_BUF_RATE/1);
}
