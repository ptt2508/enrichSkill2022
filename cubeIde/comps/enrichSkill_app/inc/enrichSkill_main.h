/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_MAIN_H
#define __ES_MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	ENRICHSKILL_APP_IDLE,
	ENRICHSKILL_APP_CAPTURE_DATA,
	ENRICHSKILL_APP_MOTOR_OBSERVER,
	ENRICHSKILL_APP_ERROR
} enrichSkillApp_State_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void enrichSkill_app_setAppState(enrichSkillApp_State_t state);

/* Private defines -----------------------------------------------------------*/

#endif /* __ES_MAIN_H */
