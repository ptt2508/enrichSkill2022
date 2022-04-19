#include "enrichSkill_shell.h"
#include "queue.h"
#include "enrichSkill_uart.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ENRICHSKILL_SHELL_QUEUE_SIZE 50u

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
QueueHandle_t gEnrichSkill_shell_queue;
TaskHandle_t gEnrichSkill_shell_help_handle;
TaskHandle_t gEnrichSkill_shell_print_handle;

/* Private function prototypes -----------------------------------------------*/


bool enrichSkill_shell_init(void)
{
	bool retVal = true;

	gEnrichSkill_shell_queue = xQueueCreate(
			ENRICHSKILL_SHELL_QUEUE_SIZE, sizeof(uint8_t));
	if (NULL == gEnrichSkill_shell_queue)
	{
		retVal = false;
	}

	return retVal;
}

void enrichSkill_shell_print_handle(void *params)
{
	uint32_t *msg;
	BaseType_t recStat = pdTRUE;
	while (1)
	{
		recStat = xQueueReceive(gEnrichSkill_shell_queue, &msg, portMAX_DELAY);
		if (pdTRUE == recStat)
		{
			enrichSkill_uart_send_msg((uint8_t *) &msg, strlen((char *)msg));
		}
	}
}

void enrichSkill_shell_help_handle(void *params)
{
	const char *helpMsg = "Supported commands:\n"
							"uc1: capture data use case\n"
							"uc2: motor observer use case\n"
							"exit: exit use case\n";
//	const char *testMsg = "test\n";
	const char testMsg = 'a';

	while(1)
	{
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
//		xQueueSendToBack(gEnrichSkill_shell_queue, (void *) &testMsg, portMAX_DELAY);
		xQueueSend(gEnrichSkill_shell_queue, (void *) &helpMsg, portMAX_DELAY);
	}
}
