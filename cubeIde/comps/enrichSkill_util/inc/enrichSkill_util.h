/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_UTIL_H
#define __ES_UTIL_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief
 * @param
 * @retval
 */
void enrichSKill_util_memSet(uint8_t *buff, uint8_t size, uint8_t data);
void enrichSkill_util_memcpy(uint8_t *src, uint8_t *dst, uint16_t size);


/* Exported variables --------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#endif /* __ES_UTIL_H */
