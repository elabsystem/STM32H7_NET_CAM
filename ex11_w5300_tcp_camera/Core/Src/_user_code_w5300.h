#include "socket.h"
#include "wizchip_conf.h"


#define true					1
#define false					0

#define SOCK_TCPS       0
#define SOCK_UDPS       1
#define PORT_TCPS		5000
#define PORT_UDPS       3000



uint8_t wiznet_memsize[2][8] = {{8,8,8,8,8,8,8,8}, {8,8,8,8,8,8,8,8}};

#define ETH_MAX_BUF_SIZE (1024*2)

uint8_t ethBuf0[ETH_MAX_BUF_SIZE];


wiz_NetInfo gWIZNETINFO = {
		.mac = {0x00, 0x08, 0xdc, 0, 0, 0},
		.ip = {192, 168, 1, 104},
		.sn = {255, 255, 255, 0},
		.gw = {192, 168, 1, 1},
		.dns = {0, 0, 0, 0},
		.dhcp = NETINFO_STATIC
};


void Reset_W5300()
{
	HAL_GPIO_WritePin(RESET_W5300_GPIO_Port, RESET_W5300_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(RESET_W5300_GPIO_Port, RESET_W5300_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}




void W5300_write(uint32_t addr, iodata_t wd)
{
	_W5300_DATA(addr) = wd;
}

iodata_t W5300_read(uint32_t addr)
{
	return _W5300_DATA(addr);
}



void print_network_information(void)
{
    wizchip_getnetinfo(&gWIZNETINFO);
    printf("Mac address: %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
    printf("IP address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
    printf("SM Mask    : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
    printf("Gate way   : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
    printf("DNS Server : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
}

void _InitW5300(void);

void _InitW5300(void)
{
	unsigned int tmpaddr[4];

	Reset_W5300();
	reg_wizchip_bus_cbfunc(W5300_read, W5300_write);


	if (ctlwizchip(CW_INIT_WIZCHIP, (void*)wiznet_memsize) == -1)
	{
		printf("W5300 memory initialization failed\r\n");
	}

	printf("getMR() = %04X\r\n", getMR());

	ctlnetwork(CN_SET_NETINFO, (void *)&gWIZNETINFO);
	print_network_information();
}

