/*
 * if datawidth is set to 8bit 
 * and you transmit 8bits using 16bit function
 * your data is sent as the high byte 
 * and low byte is sent as 0
 * 
 * if datawidth is set to 16bit 
 * and ou transmit 8bits using 16bit function
 * your data is sent as the low byte
 * and high byte is 0
 *
 */

#include <stm32g4xx_ll_bus.h>
#include <stm32g4xx_ll_gpio.h>
#include <stm32g4xx_ll_spi.h>
#include <stm32g4xx_ll_dma.h>
#include <stm32g4xx_ll_dmamux.h>
#include <stm32g4xx_ll_utils.h>

//---------| INCLUDES |----------
#include "CL_CONFIG.h"
#include "CL_delay.h"
#include "CL_systemClockUpdate.h"
#include "CL_printMsg.h"
#include "string.h"
//---------| PROTOTYPES |----------
void initSPI_DMA(void);
void initLED(void);
void spi_send(uint8_t *data, uint8_t len);
void spi_send_dma(uint8_t *data, uint32_t len);
char myString[] = "Edwin Fairchild";

//uint32_t buff[] = "hello hoes";

int main(void)
{
	CL_setSysClockTo80();
	initLED();
	CL_delay_init();
	initSPI_DMA();
	CL_printMsg_init_Default(false);
	
	
	

	
	spi_send_dma(&myString, (uint32_t)strlen(myString));
	CL_printMsg("%d", strlen(myString));

	for (;;)
	{
	
		
	}
}
void spi_send(uint8_t *data, uint8_t len)
{
	while(len > 0 )
	{
		while (!(LL_SPI_IsActiveFlag_TXE(SPI1))) 
			; //inverted flag
				len--;
		LL_SPI_TransmitData8(SPI1,(uint8_t)*data++);
		while(LL_SPI_IsActiveFlag_BSY(SPI1))
			;		
	}	
}

void spi_send_dma(uint8_t *data, uint32_t len)
{
	//CL_printMsg("%d |%d | %d | %c ", &myString , data, &data, *data);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, (uint32_t)len);
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)data);
	DMA1_Channel1->CCR |= (DMA_CCR_EN);	
}

void initSPI_DMA(void) //non circular mode
{			
	//clocks	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	
	LL_GPIO_InitTypeDef myGPIO;
	LL_GPIO_StructInit(&myGPIO);
	myGPIO.Pin       = LL_GPIO_PIN_5 | LL_GPIO_PIN_7;
	myGPIO.Speed     = LL_GPIO_SPEED_FREQ_HIGH;
	myGPIO.Mode      = LL_GPIO_MODE_ALTERNATE;
	myGPIO.Alternate = LL_GPIO_AF_5;
	LL_GPIO_Init(GPIOA, &myGPIO);
	
	LL_SPI_InitTypeDef mySPI;
	LL_SPI_StructInit(&mySPI);
	mySPI.Mode				= LL_SPI_MODE_MASTER;
	mySPI.TransferDirection	= LL_SPI_HALF_DUPLEX_TX;
	mySPI.BaudRate          = LL_SPI_BAUDRATEPRESCALER_DIV64;
	mySPI.NSS				= LL_SPI_NSS_SOFT;
	mySPI.DataWidth			= LL_SPI_DATAWIDTH_8BIT;
	
	LL_SPI_Init(SPI1, &mySPI);
	LL_SPI_EnableDMAReq_TX(SPI1);
	LL_SPI_Enable(SPI1);
	
	
	
	
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_SPI1_TX);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);
	//LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1,(uint32_t)&myString);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1,(uint32_t)11);
	LL_DMA_SetPeriphAddress(DMA1,LL_DMA_CHANNEL_1,(uint32_t)&(SPI1->DR));
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void initLED(void)
{
	LL_GPIO_InitTypeDef myGPIO;
	//LL_GPIO_StructInit(&myGPIO);
	myGPIO.Pin = LL_GPIO_PIN_0;  //| LL_GPIO_PIN_7;
	myGPIO.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(GPIOA, &myGPIO);
	myGPIO.Pin =  LL_GPIO_PIN_1;
	LL_GPIO_Init(GPIOA, &myGPIO);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
}

void DMA1_Channel1_IRQHandler(void)
{
	//this be sort of like circular mode since i restart 
	//the dma once its done sending 
	DMA1_Channel1->CCR &= ~(DMA_CCR_EN); 
	DMA1->IFCR |= DMA_IFCR_CTCIF1;
	//DMA1_Channel1->CNDTR = 11;
	//DMA1_Channel1->CCR |= (DMA_CCR_EN);

}