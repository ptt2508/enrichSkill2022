/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_CLOCK_H
#define __ES_CLOCK_H

/* Includes ------------------------------------------------------------------*/


/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	ENRICHSKILL_CLOCK_OK,
	ENRICHSKILL_CLOCK_FAIL
} enrichSKill_clock_status_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief System Clock Configuration
 * @retval System clock initialization status
 */
enrichSKill_clock_status_t enrichSkill_clock_init();

/* Private defines -----------------------------------------------------------*/

#endif /* __ES_CLOCK_H */
