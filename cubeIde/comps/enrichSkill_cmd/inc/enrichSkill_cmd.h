/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_CMD_H
#define __ES_CMD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "stdbool.h"

/* Private includes ----------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define ENRICHSKILL_CMD_PAYLOAD_SIZE		20u
#define ENRICHSKILL_CMD_CMD_LIST_SIZE		5u
#define ENRICHSKILL_CMD_CODE_HELP 			0u
#define ENRICHSKILL_CMD_CODE_UC1 			1u
#define ENRICHSKILL_CMD_CODE_UC2 			2u
#define ENRICHSKILL_CMD_CODE_SET_SPEED 		3u
#define ENRICHSKILL_CMD_CODE_EXIT 			4u

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t payload[ENRICHSKILL_CMD_PAYLOAD_SIZE];
	uint8_t length;
	uint8_t cmdCode;
} enrichSkill_cmd_cmd_t;

/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
bool enrichSkill_cmd_init(void);
void enrichSkill_cmd_cmd_handle(void *params);

/* Exported variables ------------------------------------------------------- */
extern QueueHandle_t gEnrichSkill_cmd_queue;

/* Private defines -----------------------------------------------------------*/

#endif /* __ES_CMD_H */
