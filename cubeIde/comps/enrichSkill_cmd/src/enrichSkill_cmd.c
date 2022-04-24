#include "enrichSkill_cmd.h"
#include "enrichSkill_main.h"
#include "enrichSkill_util.h"
#include "enrichSkill_shell.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ENRICHSKILL_CMD_QUEUE_SIZE 20u

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
enrichSkill_cmd_cmd_t sEnrichSkill_cmd_cmdList[ENRICHSKILL_CMD_CMD_LIST_SIZE] =
{
{ .payload = "help", .cmdCode = ENRICHSKILL_CMD_CODE_HELP },
{ .payload = "uc1", .cmdCode = ENRICHSKILL_CMD_CODE_UC1 },
{ .payload = "uc2", .cmdCode = ENRICHSKILL_CMD_CODE_UC2 },
{ .payload = "set_speed", .cmdCode = ENRICHSKILL_CMD_CODE_SET_SPEED },
{ .payload = "exit", .cmdCode = ENRICHSKILL_CMD_CODE_EXIT } };

/* Export variables */
QueueHandle_t gEnrichSkill_cmd_queue;
TaskHandle_t gEnrichSkill_shell_help_handle;

/* Private function prototypes -----------------------------------------------*/
static void enrichSkill_cmd_process(enrichSkill_cmd_cmd_t *cmd);

bool enrichSkill_cmd_init(void)
{
	bool retVal = true;

	gEnrichSkill_cmd_queue = xQueueCreate(ENRICHSKILL_CMD_QUEUE_SIZE,
			sizeof(uint8_t));
	if (NULL == gEnrichSkill_cmd_queue)
	{
		retVal = false;
	}

	return retVal;
}

void enrichSkill_cmd_cmd_handle(void *params)
{
	BaseType_t ret;
	enrichSkill_cmd_cmd_t cmd;

	while (1)
	{
		/* Waits for notification */
		ret = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
		if (pdTRUE == ret)
		{
			enrichSKill_util_memSet(cmd.payload, ENRICHSKILL_CMD_PAYLOAD_SIZE,
					0u);
			cmd.length = 0u;
			/* Process command */
			enrichSkill_cmd_process(&cmd);
			if (cmd.length != 0u)
			{
				switch (cmd.cmdCode)
				{
				case ENRICHSKILL_CMD_CODE_HELP:
					enrichSkill_shell_help();
					break;
				case ENRICHSKILL_CMD_CODE_UC1:
					enrichSkill_app_setAppState(ENRICHSKILL_APP_MOTOR_OBSERVER);
					break;
				case ENRICHSKILL_CMD_CODE_UC2:
					break;
				case ENRICHSKILL_CMD_CODE_SET_SPEED:
					break;
				case ENRICHSKILL_CMD_CODE_EXIT:
					enrichSkill_app_setAppState(ENRICHSKILL_APP_IDLE);
					break;
				default:
					enrichSkill_shell_unsupported_cmd();
					break;
				}
			}
		}
	}
}

static void enrichSkill_cmd_process(enrichSkill_cmd_cmd_t *cmd)
{
	uint8_t queueElement = 0u;
	BaseType_t status;
	uint8_t i = 0;

	status = uxQueueMessagesWaiting(gEnrichSkill_cmd_queue);
	if (status)
	{
		do
		{
			status = xQueueReceive(gEnrichSkill_cmd_queue, &queueElement, 0);
			if (pdTRUE == status)
			{
				if ('\n' != queueElement)
				{
					cmd->payload[i++] = queueElement;
				}
			}
		} while (queueElement != '\n');

		if (i > 0u)
		{
			cmd->length = i;

			for (i = 0u; i < ENRICHSKILL_CMD_CMD_LIST_SIZE; i++)
			{
				if (strcmp((const char *) &cmd->payload[0u], (const char*) &sEnrichSkill_cmd_cmdList[i].payload[0u]) == 0)
				{
					cmd->cmdCode = sEnrichSkill_cmd_cmdList[i].cmdCode;
					break;
				}
			}

			if (i == ENRICHSKILL_CMD_CMD_LIST_SIZE)
			{
				cmd->cmdCode = ENRICHSKILL_CMD_CODE_NOT_SUPPORT;
			}
		}
	}
}
