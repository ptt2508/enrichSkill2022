/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES_UART_H
#define __ES_UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	ENRICHSKILL_UART_OK,
	ENRICHSKILL_UART_FAIL
} enrichSkill_uart_status_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval UART initialization status
 */
enrichSkill_uart_status_t enrichSkill_uart_init();

/**
 * @brief Send message via UART
 * @param msg Pointer to message array
 * @param size message length
 * @retval None
 */
void enrichSkill_uart_send_msg(uint8_t *msg, uint16_t size);

/* Private defines -----------------------------------------------------------*/
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

#endif /* __ES_UART_H */
