#include "enrichSkill_shell.h"
#include "queue.h"
#include "enrichSkill_uart.h"
#include "enrichSkill_util.h"
#include "enrichSkill_motor_observer.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ENRICHSKILL_SHELL_QUEUE_SIZE 10u

/* Private macro -------------------------------------------------------------*/
#define ENRICHSKILL_SHELL_BUFF_SIZE 150

/* Private variables ---------------------------------------------------------*/
static uint8_t sEnrichSkill_shell_msg_buffer[ENRICHSKILL_SHELL_BUFF_SIZE];

/* Export variables */
QueueHandle_t gEnrichSkill_shell_queue;
TaskHandle_t gEnrichSkill_shell_help_handle;
TaskHandle_t gEnrichSkill_shell_print_handle;

/* Private function prototypes -----------------------------------------------*/

bool enrichSkill_shell_init(void)
{
	bool retVal = true;

	gEnrichSkill_shell_queue = xQueueCreate(ENRICHSKILL_SHELL_QUEUE_SIZE,
			sizeof(uint8_t));
	if (NULL == gEnrichSkill_shell_queue)
	{
		retVal = false;
	}

	enrichSKill_util_memSet(sEnrichSkill_shell_msg_buffer,
	ENRICHSKILL_SHELL_BUFF_SIZE, 0u);

	return retVal;
}

void enrichSkill_shell_print_handle(void *params)
{
	char temp = 0u;
	BaseType_t recStat = pdTRUE;
	while (1)
	{
		recStat = uxQueueMessagesWaiting(gEnrichSkill_shell_queue);
		if (recStat)
		{
			recStat = xQueueReceive(gEnrichSkill_shell_queue, &temp,
			portMAX_DELAY);
			if (pdTRUE == recStat)
			{
				enrichSkill_uart_send_msg((uint8_t*) &temp, 1u);
			}
		}
	}
}

void enrichSkill_shell_help()
{
	const char *genericHelpMsg = "<INF> Supported commands:\n"
			"<INF> uc1: capture data use case\n"
			"<INF> uc2: motor observer use case\n"
			"<INF> exit: exit use case\n";
	const char *uc1HelpMsg = "<INF> enter set_speed to set motor speed\n"
								"<INF> enter exit to exit use case\n";
	if (enrichSkill_motor_observer_isUcRunning())
	{
		enrichSkill_shell_send_to_print_queue((uint8_t *) uc1HelpMsg, strlen((char*) uc1HelpMsg));
	}
	else
	{
		enrichSkill_shell_send_to_print_queue((uint8_t *) genericHelpMsg, strlen((char*) genericHelpMsg));
	}
}

void enrichSkill_shell_exit_uc()
{
	const char *exitMsg = "<INF> use case is terminated!\n";
	enrichSkill_shell_send_to_print_queue((uint8_t *) exitMsg, strlen((char*) exitMsg));
}

void enrichSkill_shell_unsupported_cmd()
{
	const char *exitMsg = "<INF> Unsupported command!\n";
	enrichSkill_shell_send_to_print_queue((uint8_t *) exitMsg, strlen((char*) exitMsg));
}

void enrichSkill_shell_send_to_print_queue(uint8_t msg[], uint16_t len)
{
	uint16_t idx = 0u;

	enrichSkill_util_memcpy((uint8_t*) msg,
			(uint8_t*) &sEnrichSkill_shell_msg_buffer[0u], len);

	for (idx = 0u; idx < len; idx++)
	{
		xQueueSend(gEnrichSkill_shell_queue,
				&sEnrichSkill_shell_msg_buffer[idx], portMAX_DELAY);
	}
}
