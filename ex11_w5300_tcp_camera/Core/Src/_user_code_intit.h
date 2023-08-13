#include "config.h"

int _write( int32_t file , uint8_t *ptr , int32_t len )
{
    /* Implement your write code here, this is used by puts and printf for example */
    for ( int16_t i = 0 ; i < len ; ++i )
    {
        HAL_UART_Transmit( &huart1, ptr++, 1, 100);
    }
    return len;
}

void init_project(void)
{
	_InitW5300();
}
