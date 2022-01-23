/**
 ******************************************************************************
 * @file    Templates_LL/Src/stm32f0xx.c
 * @author  MCD Application Team
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"

/** @addtogroup STM32F0xx_LL_Examples
 * @{
 */

/** @addtogroup Templates_LL
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

extern void I2C_Error_Callback(void);
extern void Master_Complete_Callback(void);
extern void Master_Reception_Callback(void);

extern void ComparatorTrigger_Callback(uint8_t, uint8_t);

extern void AdcGrpRegularOverrunError_Callback(void);
extern void AdcDmaTransferComplete_Callback(void);
extern void AdcDmaTransferError_Callback(void);
extern void FaultHandler_HardFault(uint32_t *pulFaultStackAddress);
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	/* The fault handler implementation calls a function called
	 prvGetRegistersFromStack(). */

	/* The assembly code checks which stack we are using (MSP or PSP), and then loads
	 * the offending PC position on the stack into the register R1. So R1 will contain
	 * the code address where the problem happened:
	 */
	__asm volatile (
			" movs r0,#4       \n"
			" movs r1, lr      \n"
			" tst r0, r1       \n"
			" beq _MSP         \n"
			" mrs r0, psp      \n"
			" b _HALT          \n"
			"_MSP:               \n"
			" mrs r0, msp      \n"
			"_HALT:              \n"
			" ldr r1,[r0,#20]  \n"
		    " bl FaultHandler_HardFault \n"
		    " bkpt #0          \n"
	);
//	FaultHandler_HardFault(b);
	while (1)
	{
	}
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

extern void UserButton_Callback(void);

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

void EXTI0_1_IRQHandler(void)
{
	__asm volatile ("bkpt #0 ");
	/* Manage Flags */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
	{
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);

		/* Manage code in main.c.*/

	}
}

/**
 * Brief   This function handles I2C2 (Master) interrupt request.
 * Param   None
 * Retval  None
 */
void I2C1_IRQHandler(void)
{
	__asm volatile ("bkpt #0 ");
	/* Check RXNE flag value in ISR register */
	if (LL_I2C_IsActiveFlag_RXNE(I2C1))
	{
		/* Call function Master Reception Callback */
		// TODO Master_Reception_Callback();
	}
	/* Check STOP flag value in ISR register */
	else if (LL_I2C_IsActiveFlag_STOP(I2C1))
	{
		/* End of Transfer */
		LL_I2C_ClearFlag_STOP(I2C1);

		/* Call function Master Complete Callback */
		// TODO
	}
	else
	{
		/* Call Error function */
		// TODO
	}
}

/**
 * @brief  This function handles COMP1 interrupt request.
 * @param  None
 * @retval None
 */
void ADC1_IRQHandler(void)
{
	__asm volatile ("bkpt #0 ");
//	uint8_t val;
	/* Check whether EXTI line 21 (from COMP1 output) caused the interruption */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_21) != RESET)
	{
		/* Clear flag of EXTI */
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_21);
		/* Call interruption treatment function */
	}
	/* Check whether EXTI line 21 (from COMP1 output) caused the interruption */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_22) != RESET)
	{
		/* Clear flag of EXTI */
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_22);
		/* Call interruption treatment function */
	}

	/* Check whether ADC group regular overrun caused the ADC interruption */
	if (LL_ADC_IsActiveFlag_OVR(ADC1) != 0)
	{
		/* Clear flag ADC group regular overrun */
		LL_ADC_ClearFlag_OVR(ADC1);

		/* Call interruption treatment function */
		// TODO AdcGrpRegularOverrunError_Callback();
	}
}

/**
 * @brief  This function handles DMA1 interrupt request.
 * @param  None
 * @retval None
 */
void DMA1_Channel1_IRQHandler(void)
{
	__asm volatile ("bkpt #0 ");
	/* Check whether DMA transfer complete caused the DMA interruption */
	if (LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
	{
		/* Clear flag DMA transfer complete */
		LL_DMA_ClearFlag_TC1(DMA1);

		/* Call interruption treatment function */
//		AdcDmaTransferComplete_Callback();
	}

	/* Check whether DMA half transfer caused the DMA interruption */
	if (LL_DMA_IsActiveFlag_HT1(DMA1) == 1)
	{
		/* Clear flag DMA half transfer */
		LL_DMA_ClearFlag_HT1(DMA1);

		/* Call interruption treatment function */
		// AdcDmaTransferHalf_Callback();
	}

	/* Check whether DMA transfer error caused the DMA interruption */
	if (LL_DMA_IsActiveFlag_TE1(DMA1) == 1)
	{
		/* Clear flag DMA transfer error */
		LL_DMA_ClearFlag_TE1(DMA1);

		/* Call interruption treatment function */
//		AdcDmaTransferError_Callback();
	}
}


/*
void TIM14_IRQHandler(void)
{
}   // TIM14
void TIM15_IRQHandler(void)
{
}   // TIM15
void TIM16_IRQHandler(void)
{
}   // TIM16
void TIM17_IRQHandler(void)
{
}   // TIM17
*/

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
