#ifndef CL_CONFIG_H_
#define CL_CONFIG_H_


/********************|        MICROCONTROLER  SELECTION      |***********************
 *                                                                                  *
 *          CL_CONFIG.h                                                             *
 *          This is the only file that should bbe modified to configure anything    *
 *          in the dependant libraries "Common Libs" CL                             *
 *          Every C and H file depends on the proper microcontroller slection.      *
 *          Uncomment to select the mcu in use.                                     *
 *          EdwinFairchild.com 2020 during quarantine                               *
 ************************************************************************************/ 
//*******************************/ Select Target MCU /*******************************/
/******************************/ //#define CL_USING_F1  /****************************/
/******************************/ //#define CL_USING_L0  /****************************/
/******************************/ //#define CL_USING_G0  /****************************/
/******************************/  #define CL_USING_G4 /****************************/

	
	
	

/*********************| CL_systemClockUpdate.h SETTINGS |**************************************
 *                                                                                            *
 *          if CL_systemClockUpdate_USE_LL is not defined the Code will use register access   *
 *          3 different Systm clock speed are currently supported SLOW MEDIUM and MAX         *
 *          all of which use the HIGH SPEED EXTERNAL and PLL .                                *
 *          The function and prescaler values can be adjusted to suite application needs      *
 *                                                                                            *
 **********************************************************************************************/
/***********  Select to use LL or not */
//#define CL_SYSTEMCLOCKUPDATE_USE_LL







/*********************|      CL_delay.h SETTINGS        |************************
 *                                                                              *
 *                  Select the timer to use by uncommenting it                  *
 *                  currently only supports General Purpose timers              *
 *                  Option to include micro second delay                        *
 *                                                                              *
 ********************************************************************************/
/*
 *
 *	Simply call CL_delay_init() and use delayMS(uint32_t) or delayUS(uint32_t)
 *
 **/
/***********  Select which timer to use by uncommenting it */
//#define CL_DELAY_USE_TIM2
#define CL_DELAY_USE_TIM3
//#define CL_DELAY_USE_TIM4

/*********** Select uses LL to init timer */
//#define CL_delay_USE_LL

/*********** Select to add micro second support */
//#define CL_DELAY_US_ENABLE




#endif
