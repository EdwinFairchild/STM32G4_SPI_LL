#ifndef CL_delay_H_
#define CL_delay_H_

#include "CL_CONFIG.h"
#include <stdint.h>



/* Use this section to configure settings*/



#ifdef CL_USING_G4 //--------------------------  USING G4

#include "stm32g4xx.h"



#ifdef CL_delay_USE_LL
	#include <stm32g4xx_ll_rcc.h>
	#include <stm32g4xx_ll_system.h>
	#include <stm32g4xx_ll_bus.h>
	#include <stm32g4xx_ll_tim.h>
#endif

#endif //-------------------------------------- END of USING G4



#ifdef CL_USING_F1 //--------------------------  USING F1

#include "stm32f1xx.h"



#ifdef CL_delay_USE_LL
#include <stm32f1xx_ll_rcc.h>
#include <stm32f1xx_ll_system.h>
#include <stm32f1xx_ll_bus.h>
#include <stm32f1xx_ll_tim.h>
#endif

#endif //-------------------------------------- END of USING G4




void delayMS(uint32_t ms);
void CL_delay_init(void);

#ifdef CL_DELAY_US_ENABLE
void delayUS(uint32_t us);
#endif

#endif //End of header #if
