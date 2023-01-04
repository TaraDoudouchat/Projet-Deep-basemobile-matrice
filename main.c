/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "stm32f1_motorDC.h"
#include "stm32f1_timer.h"
#include "WS2812B.h"
#include <HC05/HC05.h>

void writeLED(bool_e b){
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void){
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
uint8_t j;

void process_ms(void){
	if(t)
	t--;
}

void init(void){
	TIMER_run_us(TIMER1_ID, 1000, FALSE);//PB14
//La matrice LED
	LED_MATRIX_init();

}

void pilotage(i){
	typedef enum{
		ARRET = "0",
		AVANT = "1",
		ARRIERE = "2"
}direction_e;

	direction_e dir = ARRET;

	switch(dir){

	case ARRET://ON MET TOUS A ZERO

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,TRUE);//PB14 N

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,FALSE);//PA10

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,FALSE);//PA9

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,TRUE);//PB15 N

	//	if(i == 1){
	//		dir = AVANT;
	//		break;
	//	}
	//	else if(i == 2){
	//		dir = ARRIERE;
	//	}
		break;

	case AVANT: //ON MET LES 2 FIN A QQCH et autres à 0


		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,TRUE);//PB14 N

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,TRUE);//PB15 N



		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,250,FALSE,FALSE);//PA10

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,250,FALSE,FALSE);//PA9


//		if(i == 0){
//			dir = ARRET;
//		}
//		else if(i == 2){
//			dir = ARRIERE;
//		}
		break;

	case ARRIERE: //ON MET LES 2 RIN A QQCH et autres à 0

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,FALSE);//PA10

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,FALSE);//PA9

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,250,FALSE,TRUE);//PB14 N

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,250,FALSE,TRUE);//PB15 N

//		if(i == 0){
//			dir = ARRET;
//		}
//		else if(i == 1){
//			dir = AVANT;
//		}
		break;
	}
}
void affichePano(uint8_t i){
	typedef enum{
		Eteint_e= "0",
		Roule_e = "1",
		ObstacleGauche_e = "2",
		ObstacleDroite_e = "3",
		Bouchons_e = "4",
		Accident_e = "5"
	}message_e;

	message_e message = "0";

	switch(message){
	case Eteint_e:
		LED_MATRIX_display(Eteint, MATRIX_SIZE);
		break;

	case Roule_e:
		LED_MATRIX_display(Roule, MATRIX_SIZE);
		break;

	case ObstacleGauche_e:
		LED_MATRIX_display(Gauche, MATRIX_SIZE);
		break;

	case ObstacleDroite_e:
		LED_MATRIX_display(Droite, MATRIX_SIZE);
		break;

	case Bouchons_e:
		LED_MATRIX_display(Bouchons, MATRIX_SIZE);
		break;

	case Accident_e:
		LED_MATRIX_display(Accident, MATRIX_SIZE);
		break;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
 	HAL_Init();


	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
			//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
			//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);
//TO DO UARTs
	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);

	TIMER_run_us(TIMER1_ID, 1000, FALSE);//PB14

	//La matrice LED /
	LED_MATRIX_init();

	//HC05_init();


//    TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,250,FALSE,TRUE);//CAR N
//    TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,250,FALSE,FALSE);//PA10
//    TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,600,FALSE,FALSE);//PA9
//    TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,100,FALSE,TRUE);//CAR N



	typedef enum{
		INIT = "0",
		PILOTAGE = "1",
		AFFICHAGE = "2"
	}etat_e;

	etat_e etat = INIT;

	while(1)	//boucle de tâche de fond
	{
//      DEMO_MOTOR_statemachine(FALSE, UART_get_next_byte(UART2_ID));
//
//
//		j = UART_getc(UART2_ID);
		LED_MATRIX_demo();
		HAL_Delay(1000);
//		switch(etat){
//			case INIT :
//				init();
//				break;
//			case PILOTAGE:
//				pilotage(i[1]);
//				break;
//			case AFFICHAGE:
//				affichePano(i[1]);
//				break;
//		}
//
//		if(!t){
//			t=1000;
//			HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);
//
//		}

	}
}
