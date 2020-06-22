/*
	printMsg_config_Type printer;
	printer.TX_pinNumber = 9;
	printer.Uart_instance = USART1;
	printer.tx_port = GPIOA;
	printMsg_init(printer);

	
	printMsg("Hello world");
	
*/
#ifndef CL_printMsg_H_
#define CL_printMsg_H_

#include "CL_CONFIG.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"


#ifdef CL_USING_F1
#include "stm32f1xx.h"
//	#include "stm32f10x.h"
	#include <stdint.h>
	#include "string.h"
	#include "stdlib.h"
	#include "stdio.h"
	#include "stdarg.h"
	#include "stdbool.h"


	#define MODE_BIT_0_CRL	(4*config.TX_pin)
	#define MODE_BIT_1_CRL 	((4*config.TX_pin)+1)
	#define MODE_BIT_0_CRH	(4*(config.TX_pin-8))
	#define MODE_BIT_1_CRH 	((4*(config.TX_pin-8))+1)


	#define CNF_BIT_0_CRL 	((4*config.TX_pin)+2)
	#define CNF_BIT_1_CRL	((4*config.TX_pin)+3)
	#define CNF_BIT_0_CRH 	((4*(config.TX_pin-8))+2)
	#define CNF_BIT_1_CRH	((4*(config.TX_pin-8))+3)

#endif

#ifdef CL_USING_G4

	#include "stm32g431xx.h"


#endif

typedef struct //user structure to set custom uart
{
USART_TypeDef*  Uart_instance;
	GPIO_TypeDef*   tx_port;
	uint8_t 		TX_pin;
	uint8_t			RX_pin;
	uint16_t 		baud;
	bool			FullDuplex;

}printMsg_config_Type;



void CL_printMsg_init_Default(bool fullDuplex); //defaults to USART1 TX only on PA9 @9600
void CL_printMsg_init(printMsg_config_Type config);
void CL_printMsg(char *msg, ...);




#endif

