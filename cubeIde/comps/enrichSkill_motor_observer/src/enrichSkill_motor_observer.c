#include "enrichSkill_motor_observer.h"
#include "enrichSkill_shell.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static bool sEnrichSkill_motor_observer_isFunctionRunning;

/* Private function prototypes -----------------------------------------------*/

void enrichSkill_motor_observer_init()
{
	sEnrichSkill_motor_observer_isFunctionRunning = false;
}

void enrichSkill_motor_observer_main_handle(void *params)
{
	char *ucWelcomMsg = "<INF> Motor observer use case is running\n"
								"<INF> enter set_speed to set motor speed\n"
								"<INF> enter exit to exit use case\n";

	while (1)
	{
		if (!sEnrichSkill_motor_observer_isFunctionRunning)
		{
			/* Print help use case welcome message */
			enrichSkill_shell_send_to_print_queue((uint8_t *) ucWelcomMsg, strlen((char*) ucWelcomMsg));
		}
		/* Use case handle here */
	}
}

void enrichSkill_motor_observer_setUcRunningStat(bool runStat)
{
	sEnrichSkill_motor_observer_isFunctionRunning = runStat;
}

bool enrichSkill_motor_observer_isUcRunning()
{
	return sEnrichSkill_motor_observer_isFunctionRunning;
}
