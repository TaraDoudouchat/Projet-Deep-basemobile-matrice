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

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}
uint32_t Roule[] = {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,};

uint32_t Bouchons[] = {COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK};

uint32_t Gauche[] = {COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};

uint32_t Droite[] = {COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,};

uint32_t Accident[] = {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_RED,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,};

uint32_t Eteint[] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};



void machineAetat(uint8_t b, uint8_t c){
	typedef enum{
			INIT,
			PILOTAGE,
			AFFICHAGE
		}etat_e;

		etat_e etat = b;
		uint8_t i;
		uint32_t pixels[MATRIX_SIZE];


		switch(etat){
			case INIT :
				TIMER_run_us(TIMER1_ID, 1000, FALSE);//PB14
					 	//La matrice LED //
				LED_MATRIX_init();
				break;

			case PILOTAGE:
				if(c==0){
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,TRUE);//PB14 N
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,FALSE);//PA10
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,FALSE);//PA9
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,TRUE);//PB15 N
					//c'est bon
				}else if(c==1){
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,TRUE);//PB14 N
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,TRUE);//PB15 N
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,250,FALSE,FALSE);//PA10
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,250,FALSE,FALSE);//PA9
				}else if(c==2){//ari�rre
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,250,FALSE,FALSE);//PA10
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3,0,FALSE,TRUE);//PB15 N
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,0,FALSE,FALSE);//PA9
					TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2,250,FALSE,TRUE);//PB14 N
				}
				break;

			case AFFICHAGE:
				if(c==0){
					while(i < MATRIX_SIZE)
						{
							pixels[i] = Eteint[i];
							i++;
						}
					LED_MATRIX_display(pixels, MATRIX_SIZE);


				}else if(c==1){
					while(i < MATRIX_SIZE)
					{
						pixels[i] = Roule[i];
						i++;
					}
					LED_MATRIX_display(pixels, MATRIX_SIZE);

				}else if(c==2){
//					while(i < MATRIX_SIZE)
//					{
//						pixels[i] = Droite[i];
//						i++;
//					}
//					LED_MATRIX_display(Droite, MATRIX_SIZE);
					LED_MATRIX_demo();
				}else if(c==3){
					for(i=0;i<MATRIX_SIZE;i++)
					{
						pixels[i] = Gauche[i];
					}
					LED_MATRIX_display(pixels, MATRIX_SIZE);

				}else if(c==4){
					for(i=0;i<MATRIX_SIZE;i++)
					{
						pixels[i] = Bouchons[i];
					}
					LED_MATRIX_display(pixels, MATRIX_SIZE);

				}else{
					for(i=0;i<MATRIX_SIZE;i++)
					{
					pixels[i] = Accident[i];
					}
					LED_MATRIX_display(pixels, MATRIX_SIZE);

				}
				break;
		}
}
int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();


	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);
//TO DO UARTs
	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);

	TIMER_run_us(TIMER1_ID, 1000, FALSE);//PB14

	//La matrice LED /
	LED_MATRIX_init();

	uint8_t b = 2;
	uint8_t c = 2;



	while(1)	//boucle de t�che de fond
	{
//
//
		//machineAetat(b,c);
//		LED_MATRIX_demo();

//		uint32_t pixels[MATRIX_SIZE];
//		for(uint8_t i=0;i<MATRIX_SIZE;i++)
//			{
//			pixels[i] = Accident[i];
//			}
//
//		LED_MATRIX_display(Roule, MATRIX_SIZE);
		if(!t)
		{
			t=100;
			HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);

		}

	}
}
