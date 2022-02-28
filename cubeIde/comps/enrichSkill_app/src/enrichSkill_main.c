#include <enrichSkill_main.h>
#include "string.h"

#include "enrichSkill_uart.h"
#include "enrichSkill_gpio.h"
#include "enrichSkill_timer.h"
#include "enrichSkill_clock.h"
#include "FreeRTOS.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
	ENRICHSKILL_APP_IDLE,
	ENRICHSKILL_APP_CAPTURE_DATA,
	ENRICHSKILL_APP_MOTOR_OBSERVER,
	ENRICHSKILL_APP_ERROR
} enrichSkillApp_State_t;

typedef enum
{
	ENRICHSKILL_APP_INIT_OK,
	ENRICHSKILL_APP_INIT_FAIL,
} enrichSkillApp_Init_Stat_t;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t sWelcomeMsg[10] = "welcome\n\r";
enrichSkillApp_State_t sEnrichSkill_App_State = ENRICHSKILL_APP_IDLE;

/* Private function prototypes -----------------------------------------------*/
static void enrichSKill_app_errorHandler(void);
static enrichSkillApp_Init_Stat_t enrichSkill_app_init(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
int enrichSkill_main(void)
{
	BaseType_t taskStat = pdPASS;
	/* Initialize system */
	if (enrichSkill_app_init() == ENRICHSKILL_APP_INIT_FAIL)
	{
		sEnrichSkill_App_State = ENRICHSKILL_APP_ERROR;
	}
	/* Send welcome message */
	enrichSkill_uart_send_msg((uint8_t*) &sWelcomeMsg[0u],
			strlen((const char*) &sWelcomeMsg[0u]));
	/* Register tasks */
//	taskStat = xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
//	if (pdFAIL == taskStat)
//	{
//		enrichSKill_app_errorHandler();
//	}
	/* Infinite loop */
	while (1)
	{
		HAL_GPIO_TogglePin(GPIOA, 1 << 5);
		HAL_Delay(500);
		switch (sEnrichSkill_App_State)
		{
		case ENRICHSKILL_APP_IDLE:
			break;
		case ENRICHSKILL_APP_CAPTURE_DATA:
			break;
		case ENRICHSKILL_APP_MOTOR_OBSERVER:
			break;
		case ENRICHSKILL_APP_ERROR:
			enrichSKill_app_errorHandler();
			break;
		default:
			break;
		}
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void enrichSKill_app_errorHandler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

/**
 * @brief  Application initialization.
 * @retval None
 */
static enrichSkillApp_Init_Stat_t enrichSkill_app_init(void)
{
	enrichSkillApp_Init_Stat_t retVal = ENRICHSKILL_APP_INIT_OK;

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	(void) HAL_Init();

	/* Configure the system clock */
	if (enrichSkill_clock_init() == ENRICHSKILL_CLOCK_FAIL)
	{
		retVal = ENRICHSKILL_APP_INIT_FAIL;
	}

	/* Initialize all configured peripherals */
	enrichSkill_gpio_init();
	enrichSkill_timer_init();
	if (enrichSkill_uart_init() == ENRICHSKILL_UART_FAIL)
	{
		retVal = ENRICHSKILL_APP_INIT_FAIL;
	}

	return retVal;
}


