/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_SHELL_H
#define __ES_SHELL_H

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "queue.h"
#include "stdbool.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
bool enrichSkill_shell_init(void);
void enrichSkill_shell_print_handle(void *params);
void enrichSkill_shell_help_handle(void *params);
void enrichSkill_shell_capture_data_hanle(void *params);
void enrichSkill_shell_motor_observer_handle(void *params);

/* Exported variables -----------------------------------------------------------*/
extern QueueHandle_t gEnrichSkill_shell_queue;
extern TaskHandle_t gEnrichSkill_shell_help_handle;
extern TaskHandle_t gEnrichSkill_shell_print_handle;

#endif /* __ES_SHELL_H */
