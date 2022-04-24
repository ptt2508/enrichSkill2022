/* Private includes */
#include "enrichSkill_util.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void enrichSKill_util_memSet(uint8_t *buff, uint8_t size, uint8_t data)
{
	uint8_t idx = 0u;

	for (idx = 0u; idx < size; idx++)
	{
		buff[idx] = data;
	}
}

void enrichSkill_util_memcpy(uint8_t *src, uint8_t *dst, uint16_t size)
{
	uint16_t idx = 0u;

	for (idx = 0u; idx < size; idx++)
	{
		dst[idx] = src[idx];
	}
}
