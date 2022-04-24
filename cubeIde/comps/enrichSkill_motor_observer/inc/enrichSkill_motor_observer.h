/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_MOTOR_OBSERVER_H
#define __ES_MOTOR_OBSERVER_H

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void enrichSkill_motor_observer_init(void);
void enrichSkill_motor_observer_setUcRunningStat(bool runStat);
void enrichSkill_motor_observer_main_handle(void *params);
bool enrichSkill_motor_observer_isUcRunning(void);



#endif /* __ES_MOTOR_OBSERVER_H */
