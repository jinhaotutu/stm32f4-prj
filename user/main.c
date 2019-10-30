/**
  ******************************************************************************
  * @file    main.c 
  * @author  jinhao
  * @version V1.0.0
  * @date    22-April-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Includes -------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "sys_cfg.h"
#include "sys_delay.h"

/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/

				
/* Functions ------------------------------------------------------------------*/			



/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	/* stm32系统配置 */
	Sys_Config();

	while(1)
	{
		LED1_ON;
		delay_ms(500);

		LED1_OFF;
		delay_ms(500);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
