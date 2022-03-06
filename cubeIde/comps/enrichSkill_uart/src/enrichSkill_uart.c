#include <enrichSkill_uart.h>
#include "FreeRTOS.h"
#include "queue.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ENRICHSKILL_UART_QUEUE_DATA_SIZE 20u
#define ENRICHSKILL_UART_QUEUE_PRINT_SIZE 20u

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t sEnrichSkill_uart_recv_data;
static QueueHandle_t sEnrichSkill_uart_queue_data;
static QueueHandle_t sEnrichSkill_uart_queue_print;

/* Private function prototypes -----------------------------------------------*/
static void enrichSkill_uart_recv_callback(void);

enrichSkill_uart_status_t enrichSkill_uart_init()
{
	enrichSkill_uart_status_t retVal = ENRICHSKILL_UART_OK;
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	sEnrichSkill_uart_recv_data = 0u;
	sEnrichSkill_uart_queue_data = NULL;
	sEnrichSkill_uart_queue_print = NULL;

	if (HAL_OK != HAL_UART_Init(&huart2))
	{
		retVal = ENRICHSKILL_UART_FAIL;
	}

	/* Register callback function for complete receiving */
	if (HAL_OK
			!= HAL_UART_RegisterCallback(&huart2, HAL_UART_RX_COMPLETE_CB_ID,
					(pUART_CallbackTypeDef) &enrichSkill_uart_recv_callback))
	{
		retVal = ENRICHSKILL_UART_FAIL;
	}

	/* Create data queue */
	if (ENRICHSKILL_UART_OK == retVal)
	{
		sEnrichSkill_uart_queue_data = xQueueCreate(
				ENRICHSKILL_UART_QUEUE_DATA_SIZE, sizeof(uint8_t));
		if (NULL != sEnrichSkill_uart_queue_data)
		{
			sEnrichSkill_uart_queue_print = xQueueCreate(
					ENRICHSKILL_UART_QUEUE_PRINT_SIZE, sizeof(uint8_t));
			if (NULL == sEnrichSkill_uart_queue_print)
			{
				retVal = ENRICHSKILL_UART_FAIL;
			}
		}
		else
		{
			retVal = ENRICHSKILL_UART_FAIL;
		}
	}

	/* Wait for user to enter data */
	if (ENRICHSKILL_UART_OK == retVal)
	{
		HAL_UART_Receive_IT(&huart2, &sEnrichSkill_uart_recv_data, 1u);
	}

	return retVal;
}

void enrichSkill_uart_send_msg(uint8_t *msg, uint16_t size)
{
	HAL_UART_Transmit(&huart2, msg, size, 100);
}

static void enrichSkill_uart_recv_callback(void)
{
	uint8_t dummy;
	if (!xQueueIsQueueFullFromISR(sEnrichSkill_uart_queue_data))
	{
		/* Enqueue data byte */
		xQueueSendFromISR(sEnrichSkill_uart_queue_data,
				(void* ) &sEnrichSkill_uart_recv_data, NULL);
	}
	else
	{
		if ('\n' == sEnrichSkill_uart_recv_data)
		{
			/* Make sure that last data byte of queue is '\n' */
			xQueueCRReceiveFromISR(sEnrichSkill_uart_queue_data, (void*) &dummy,
					NULL);
			xQueueSendFromISR(sEnrichSkill_uart_queue_data,
					(void* ) &sEnrichSkill_uart_recv_data, NULL);
		}
	}

	/* Send notification to command handling task if user enter '\n' */
	if ('\n' == sEnrichSkill_uart_recv_data)
	{
//		xTaskNotifyFromISR()
	}

	HAL_UART_Receive_IT(&huart2, &sEnrichSkill_uart_recv_data, 1u);
}
