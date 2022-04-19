#include <enrichSkill_main.h>
#include <string.h>
#include <stdbool.h>

#include "enrichSkill_uart.h"
#include "enrichSkill_gpio.h"
#include "enrichSkill_timer.h"
#include "enrichSkill_i2c.h"
#include "enrichSkill_clock.h"
#include "enrichSkill_cmd.h"
#include "enrichSkill_shell.h"

#include "FreeRTOS.h"
#include "task.h"

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
	ENRICHSKILL_APP_INIT_OK, ENRICHSKILL_APP_INIT_FAIL,
} enrichSkillApp_Init_Stat_t;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t sWelcomeMsg[20] = "EnrichSkill22\n\r";
enrichSkillApp_State_t sEnrichSkill_App_State = ENRICHSKILL_APP_IDLE;
TaskHandle_t senrichSkill_app_main_taskHandle;
TaskHandle_t genrichSkill_uart_cmdHandle;
TaskHandle_t gEnrichSkill_shell_help_handle;
TaskHandle_t gEnrichSkill_shell_print_handle;

/* Private function prototypes -----------------------------------------------*/
static void enrichSKill_app_errorHandler(void);
static enrichSkillApp_Init_Stat_t enrichSkill_app_init(void);
static bool enrichSkill_app_register_tasks(void);
static void enrichSkill_app_main_handler(void *param);

/**
 * @brief  The application entry point.
 * @retval int
 */
int enrichSkill_main(void)
{
	/* Initialize system */
	if (enrichSkill_app_init() == ENRICHSKILL_APP_INIT_FAIL)
	{
		sEnrichSkill_App_State = ENRICHSKILL_APP_ERROR;
		enrichSKill_app_errorHandler();
	}
	/* Send welcome message */
	enrichSkill_uart_send_msg((uint8_t*) &sWelcomeMsg[0u],
			strlen((const char*) &sWelcomeMsg[0u]));
	/* Register tasks */
	if (false == enrichSkill_app_register_tasks())
	{
		sEnrichSkill_App_State = ENRICHSKILL_APP_ERROR;
		enrichSKill_app_errorHandler();
	}

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Infinite loop */
	while (1)
	{

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

	if (false == enrichSkill_cmd_init())
	{
		retVal = ENRICHSKILL_APP_INIT_FAIL;
	}

	if (false == enrichSkill_shell_init())
	{
		retVal = ENRICHSKILL_APP_INIT_FAIL;
	}

	if (enrichSkill_uart_init() == ENRICHSKILL_UART_FAIL)
	{
		retVal = ENRICHSKILL_APP_INIT_FAIL;
	}

	return retVal;
}

static bool enrichSkill_app_register_tasks(void)
{
	bool retVal = true;
	BaseType_t taskStat = pdPASS;

	TaskHandle_t ledHandle;

	/* Main application task */
	taskStat = xTaskCreate(enrichSkill_app_main_handler, "Application handler",
			200, NULL, 2, &senrichSkill_app_main_taskHandle);
	if (pdFAIL == taskStat)
	{
		retVal = false;
	}
	/* LED handler task */
	if (pdPASS == taskStat)
	{
		taskStat = xTaskCreate(enrichSkill_gpio_led_hanlder, "LED handler", 200,
		NULL, 2, &ledHandle);
		if (pdFAIL == taskStat)
		{
			retVal = false;
		}
	}

	/* cmd handler task */
	if (pdPASS == taskStat)
	{
		taskStat = xTaskCreate(enrichSkill_cmd_cmd_handle, "Cmd handler", 200,
		NULL, 2, &genrichSkill_uart_cmdHandle);
		if (pdFAIL == taskStat)
		{
			retVal = false;
		}
	}

	/* shell print task */
	if (pdPASS == taskStat)
	{
		taskStat = xTaskCreate(enrichSkill_shell_print_handle, "Shell print",
				200, NULL, 2, &gEnrichSkill_shell_print_handle);
		if (pdFAIL == taskStat)
		{
			retVal = false;
		}
	}

	/* shell help task */
	if (pdPASS == taskStat)
	{
		taskStat = xTaskCreate(enrichSkill_shell_help_handle, "Shell help", 200,
		NULL, 2, &gEnrichSkill_shell_help_handle);
		if (pdFAIL == taskStat)
		{
			retVal = false;
		}
	}

	return retVal;
}

static void enrichSkill_app_main_handler(void *param)
{
	while (1)
	{
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

