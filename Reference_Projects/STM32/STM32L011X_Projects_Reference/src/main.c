#include "GPIO_Driver_Cfg.h"
#include "TCNT_Driver_Cfg.h"
#include "PWM_Driver_Cfg.h"

int main()
{
	GPIO_Driver_Init();
	TCNT_Driver_Init();
	PWM_Driver_Init();
	PWM_Driver_SetDutyCylce(PWM_DRIVER_0,50);
	TCNT_Driver_Start(TCNT_DRIVER_TIM2);

	while(1)
	{

	}
	return 0;
}
