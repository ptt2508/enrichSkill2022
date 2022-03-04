#include <enrichSkill_uart.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

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

	return retVal;
}

void enrichSkill_uart_send_msg(uint8_t *msg, uint16_t size)
{
	HAL_UART_Transmit_IT(&huart2, msg, size);
}

static void enrichSkill_uart_recv_callback(void)
{

}
