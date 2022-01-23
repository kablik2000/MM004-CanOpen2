/*! @file dbg_fnc.c
 *
 * @brief
 *
 * @par Documentation
 *
 * @author
 *      Ing. Michal Zahalka \n
 * 
 * $Revision: 1113 $ 
 * $Date: 2019-02-18 20:19:41 +0100 (Mon, 18 Feb 2019) $   \n
 */

/* Includes ------------------------------------------------------------------*/
#include "dbg_fnc.h"
#include "boards/board.h"

//#include "tmdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile unsigned long ulHighFrequencyTimerTicks;
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
 * prvGetRegistersFromStack() copies the register values from the stack into the
 * C variables, then sits in a loop. The variables are named to indicate the register
 * value that they hold. Other registers will not have changed since the fault
 * occurred, and can be viewed directly in the debugger's CPU register window
 * @param pulFaultStackAddress
 */
void FaultHandler_HardFault(uint32_t *pulFaultStackAddress)
{
	/* These are volatile to try and prevent the compiler/linker optimising them
	 away as the variables never actually get used.  If the debugger won't show the
	 values of the variables, make them global my moving their declaration outside
	 of this function. */
	struct
	{
		volatile uint32_t r0;
		volatile uint32_t r1;
		volatile uint32_t r2;
		volatile uint32_t r3;
		volatile uint32_t r12;
		volatile uint32_t lr; /* Link register. */
		volatile uint32_t pc; /* Program counter. */
		volatile uint32_t psr;/* Program status register. */

#if (configDEBUG == 1)
		volatile uint32_t _CFSR;
		volatile uint32_t _HFSR;
		volatile uint32_t _DFSR;
		volatile uint32_t _AFSR;
		volatile uint32_t _BFAR;
		volatile uint32_t _MMAR;
#endif /*configDEBUG*/
	} xStack;

	xStack.r0 = pulFaultStackAddress[0];
	xStack.r1 = pulFaultStackAddress[1];
	xStack.r2 = pulFaultStackAddress[2];
	xStack.r3 = pulFaultStackAddress[3];

	xStack.r12 = pulFaultStackAddress[4];
	xStack.lr = pulFaultStackAddress[5];   // It stores the return information for subroutines, function calls, and exceptions.
	xStack.pc = pulFaultStackAddress[6];	// It contains the current program address.
	xStack.psr = pulFaultStackAddress[7];	// Program Status Register (PSR) combines:
											//Application Program Status Register (APSR)
											//Interrupt Program Status Register (IPSR)
											//Execution Program Status Register (EPSR).
#if (configDEBUG == 1)
	// Configurable Fault Status Register
	// Consists of MMSR, BFSR and UFSR
	xStack._CFSR = (*((volatile unsigned long *) (0xE000ED28)));
	// Hard Fault Status Register
	xStack._HFSR = (*((volatile unsigned long *) (0xE000ED2C)));
	// Debug Fault Status Register
	xStack._DFSR = (*((volatile unsigned long *) (0xE000ED30)));
	// Auxiliary Fault Status Register
	xStack._AFSR = (*((volatile unsigned long *) (0xE000ED3C)));
	// Read the Fault Address Registers. These may not contain valid values.
	// Check BFARVALID/MMARVALID to see if they are valid values
	// MemManage Fault Address Register
	xStack._MMAR = (*((volatile unsigned long *) (0xE000ED34)));
	// Bus Fault Address Register
	xStack._BFAR = (*((volatile unsigned long *) (0xE000ED38)));

	__asm("BKPT #0\n");
	// Break into the debugger x is an expression evaluating to an integer in the range 0-255 (8-bit value).
//	printf("LR [R14] = %x  subroutine call return address\n", stacked_lr);
//	printf("PC [R15] = %x  program counter\n", stacked_pc);
//	printf("PSR = %x\n", stacked_psr);
//	printf("BFAR = %x\n", (*((volatile unsigned long *) (0xE000ED38))));
//	printf("CFSR = %x\n", (*((volatile unsigned long *) (0xE000ED28))));
//	printf("HFSR = %x\n", (*((volatile unsigned long *) (0xE000ED2C))));
//	printf("DFSR = %x\n", (*((volatile unsigned long *) (0xE000ED30))));
//	printf("AFSR = %x\n", (*((volatile unsigned long *) (0xE000ED3C))));
//	printf("SCB_SHCSR = %x\n", SCB->SHCSR);
	/* When the following line is hit, the variables contain the register values. */
#endif /*configDEBUG*/

//	syslog_Add(SyslogCategory_FreeRTOS, SyslogType_Error, "HardFault Error!");

//	uint8_t errText[50];
//	tmsprint(errText, "HardFault: PC0x%x; LR0x%x", xStack.pc, xStack.lr);	//FIXME!!!!!

//	syslog_Add(SyslogCategory_FreeRTOS, SyslogType_Error, errText);
//	system_Reset(0);

	for (;;)
		;
}

#if 1
/**
 * ----------------------------------
 * Do hard fault
 * ----------------------------------
 */
void (*f)(void);
/**
 * Branch to an address where no code is located
 */
void call_null_pointer_function(void)
{
	f(); /* will execute code at address zero */
}

/**
 * Accessing an invalid address
 */
void write_to_rom(void)
{
	*((int*) 0x0) = 10; /* tries to write to address zero */
//	int b = *((int*) 0xFEEDABBA);
}
#endif	/*Do hard fault*/


/**
 * Ošetření vstupů
 * @param pcFileName: Název souboru
 * @param ulLine: Číslo řádky
 */
void vAssertCalled(const char * const pcFileName, unsigned long ulLine)
{
//	static portBASE_TYPE xPrinted = pdFALSE;
	volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

	/* Parameters are not used. */
	(void) ulLine;
	(void) pcFileName;

	taskENTER_CRITICAL();
	{
		/* You can step out of this function to debug the assertion by using
		 the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
		 value. */
#if (configDEBUG == 1)
		__asm("BKPT #0\n");
		// Break into the debugger x is an expression evaluating to an integer in the range 0-255 (8-bit value).
#endif /*configDEBUG*/

		while (ulSetToNonZeroInDebuggerToContinue == 0)
		{
			// I set a breakpoint on this line, while I am in debugger.
		}
	}
	taskEXIT_CRITICAL();
}

/* Defined in main.c. */
/**
 * @brief
 * Freq = 100kHz
 */
void vConfigureTimerForRunTimeStats(void)
{
	LL_RCC_ClocksTypeDef xClkFreq;
	LL_RCC_GetSystemClocksFreq(&xClkFreq);   //
	/*
	 - TIMx_Period = (SystemCoreClock / frq) - 1
	 The Timer pulse is calculated as follows:
	 */
	uint32_t ulBusFreq = xClkFreq.PCLK1_Frequency;   // PCLK1 * 1 or PCLK1 * 2
	uint16_t usPeriod = (uint16_t) ((ulBusFreq / 100000) - 1) / 6;   //	  TimerPeriod = (SystemCoreClock / needFreq ) - 1;

	LL_TIM_InitTypeDef TIM_InitStruct;
	/* Peripheral clock enable */

	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM17);
	TIM_InitStruct.Prescaler = 5;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_InitStruct.Autoreload = (uint32_t) usPeriod;   // TimerPeriod = (SystemCoreClock / needFreq ) - 1;;
	LL_TIM_Init(TIM17, &TIM_InitStruct);
	LL_TIM_DisableMasterSlaveMode(TIM17);
	LL_TIM_EnableIT_UPDATE(TIM17);

	LL_TIM_EnableCounter(TIM17);
	NVIC_SetPriority(TIM17_IRQn, 0x05);
//	NVIC_EnableIRQ(TIM17);

	ulHighFrequencyTimerTicks = 0;

#if 0
	/* TIM7 counter enable */
	TIM_Cmd(TIM17, ENABLE);
#endif
}

/**
 *  TIM7
 */
void TIM7_IRQHandler(void)
{
	/* Check if interrupt has occured */
	if (LL_TIM_IsActiveFlag_UPDATE(TIM17))
	{
		/* Clear interrupt pending bit */
		LL_TIM_ClearFlag_UPDATE(TIM17);
		ulHighFrequencyTimerTicks++;   //counter incrementing at 100kHz
	}
}

/*************** (C) COPYRIGHT 2015 *****END OF FILE****/
