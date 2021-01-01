/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ds3231.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim3;
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
	//HAREKET BUTONU
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */
  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0x00;
  HAL_TIM_Base_Start_IT(&htim3);

	if(timer_durum == 1)
	{
		switch (lcd.menu)
		{
		case ANA_SAYFA:
			if(lcd.secili == ANA_SAYFA_MAX_SATIR)
			{
				lcd.secili = 1;
			}
			else
			{
				lcd.secili ++;
			}
//			menu_ac(ANA_SAYFA, lcd.secili);
			break;
		case ADIM:

			lcd.menu = ADIM;
			lcd.secili = 1;
			menu_ac(ADIM, 1);
			break;
		case NABIZ:
			lcd.menu = NABIZ;
			lcd.secili = 1;
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case TELEFON:
			if(lcd.secili == TELEFON_MAX_SATIR)
			{
				lcd.secili = 1;
			}
			else
			{
				lcd.secili ++;
			}
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case SICAKLIK:
			lcd.secili = 1;
//			menu_ac(lcd.menu, 1);
			break;
		case SAAT:
			lcd.secili = 1;
		case SAAT_AYAR:
			switch(zaman_ayarlama.saat_ayar_digit)
			{
			case SAAT_ONDALIK:
				zaman_ayarlama.saat += 10;
				if(zaman_ayarlama.saat / 10 == 6 )
				{
					zaman_ayarlama.saat -= 60;
				}
				break;
			case SAAT_BIRLIK:
				if(zaman_ayarlama.saat % 10 == 9)
				{
					zaman_ayarlama.saat = zaman_ayarlama.saat + 1 - 10;
				}
				else
				{
					zaman_ayarlama.saat = zaman_ayarlama.saat + 1 ;
				}
				break;
			case DAKIKA_ONDALIK:
				zaman_ayarlama.dakika += 10;
				if(zaman_ayarlama.dakika / 10 == 6 )
				{
					zaman_ayarlama.dakika -= 60;
				}
				break;
			case DAKIKA_BIRLIK:
				if(zaman_ayarlama.dakika % 10 == 9)
				{
					zaman_ayarlama.dakika = zaman_ayarlama.dakika + 1 - 10;
				}
				else
				{
					zaman_ayarlama.dakika = zaman_ayarlama.dakika + 1 ;
				}
				break;
			case SANIYE_ONDALIK:
				zaman_ayarlama.saniye += 10;
				if(zaman_ayarlama.saniye / 10 == 6 )
				{
					zaman_ayarlama.saniye -= 60;
				}
				break;
			case SANIYE_BIRLIK:
				if(zaman_ayarlama.saniye % 10 == 9)
				{
					zaman_ayarlama.saniye = zaman_ayarlama.saniye + 1 - 10;
				}
				else
				{
					zaman_ayarlama.saniye = zaman_ayarlama.saniye + 1 ;
				}
				break;
			case SET_SAAT:
				zaman_ayarlama.saat_ayar_digit = SAAT_ONDALIK;
				break;
			}
			break;

		default:
			break;
		}
		HAL_TIM_Base_Start_IT(&htim1);
		timer_durum = 0;
	}
	else
	{
	}
  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel6_IRQn 0 */

  /* USER CODE END DMA1_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_i2c1_tx);
  /* USER CODE BEGIN DMA1_Channel6_IRQn 1 */

  /* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
	//SECME BUTONU
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0x00;
  HAL_TIM_Base_Start_IT(&htim3);

	if(timer_durum == 1)
	{
		switch (lcd.menu)
		{
		case ANA_SAYFA:
			switch(lcd.secili)
			{
			case 1:				//nabiz
				lcd.menu = NABIZ;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			case 2:				//adim
				lcd.menu = ADIM;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			case 3:				//tel
				lcd.menu = TELEFON;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			case 4:			//sicaklik
				lcd.menu = SICAKLIK;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			case 5:			//SAAT YUZU
				lcd.menu = SAAT;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			case 6:			//saat ayar
				lcd.menu = SAAT_AYAR;
				lcd.secili = 1;
				break;
			default:
				break;
			}
			break;
		case ADIM:
			lcd.menu = ANA_SAYFA;
			lcd.secili = 1;
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case TELEFON:
			switch(lcd.secili)
			{
			case 1:	//TODO: Telefona baglan secenegi aktif degil
				break;
			case 2: //TODO: Telefon baglanti kes secenegi aktif degil
				break;
			case 3:
				lcd.menu = ANA_SAYFA;
				lcd.secili = 1;
//				menu_ac(lcd.menu, lcd.secili);
				break;
			default:
				break;
			}
			break;
		case SICAKLIK:
			lcd.menu = ANA_SAYFA;
			lcd.secili = 1;
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case NABIZ:
			lcd.menu = ANA_SAYFA;
			lcd.secili = 1;
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case SAAT:
			lcd.menu = ANA_SAYFA;
			lcd.secili = 1;
//			menu_ac(lcd.menu, lcd.secili);
			break;
		case SAAT_AYAR:
			switch(zaman_ayarlama.saat_ayar_digit)
			{
			case SAAT_ONDALIK:
				zaman_ayarlama.saat_ayar_digit = SAAT_BIRLIK;
				break;
			case SAAT_BIRLIK:
				zaman_ayarlama.saat_ayar_digit = DAKIKA_ONDALIK;
				break;
			case DAKIKA_ONDALIK:
				zaman_ayarlama.saat_ayar_digit = DAKIKA_BIRLIK;
				break;
			case DAKIKA_BIRLIK:
				zaman_ayarlama.saat_ayar_digit = SANIYE_ONDALIK;
				break;
			case SANIYE_ONDALIK:
				zaman_ayarlama.saat_ayar_digit = SANIYE_BIRLIK;
				break;
			case SANIYE_BIRLIK:
				zaman_ayarlama.saat_ayar_digit = SAAT_ONDALIK;
				ds3231_zaman_ayarla(&hi2c1, 0xD0, zaman_ayarlama);
				zaman_ayarlama.saniye = 0;
				zaman_ayarlama.saat   = 0;
				zaman_ayarlama.dakika = 0;
				lcd.menu = ANA_SAYFA;
				lcd.secili = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		HAL_TIM_Base_Start_IT(&htim1);
		timer_durum = 0;
	}
	else
	{
	}
  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break interrupt.
  */
void TIM1_BRK_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_IRQn 0 */

  /* USER CODE END TIM1_BRK_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_IRQn 1 */

  /* USER CODE END TIM1_BRK_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM1 trigger and commutation interrupts.
  */
void TIM1_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 0 */

  /* USER CODE END TIM1_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
