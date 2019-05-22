/*
 * Display_LCD.c
 *
 *  Created on: 11 apr 2019
 *      Author: user
 */


#include "stm32f4xx_hal.h"
#include "Display_LCD.h"


void init_LCD(void)
	{
	init_pin_LCD();  //settaggio delle linee di IO
	init_modo_4bit();//lavorerò con solo 4 bit dati
	SetLCD ();       // pulizia iniziale
	}

void init_pin_LCD(void)
	{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* il display è controllato da 6 PIN :
     * 2 di controllo RS e EN   con clock
     * 4 di dati D4,D5,D6,D7
     *
     */

	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 __HAL_RCC_GPIOC_CLK_ENABLE();



  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PIN_D4_GPIO_Port, PIN_D4_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PIN_D5_GPIO_Port, PIN_D5_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PIN_D6_GPIO_Port, PIN_D6_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PIN_D7_GPIO_Port, PIN_D7_Pin,GPIO_PIN_RESET);

  HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PIN_EN_GPIO_Port,PIN_EN_Pin,GPIO_PIN_RESET);




  GPIO_InitStruct.Pin =PIN_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_D4_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =PIN_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_D5_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =PIN_D6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_D6_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =PIN_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_D7_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =PIN_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_RS_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =PIN_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PIN_EN_GPIO_Port, &GPIO_InitStruct);

}


void init_modo_4bit(void)
	{

	HAL_Delay(50);  //perchè alla partenza a volte non aggancia bene

    //0011xxxx
	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);



    //spedizione del dato 0x33 attraveso 2 nibble 0x03 e 0x03
	LcdStrobe();
	HAL_Delay(10);          //questi ritardi possono diminuire
	LcdStrobe();
	HAL_Delay(10);

	//spedizione del dato 0x32 attraveso 2 nibble 0x03 e 0x02
	LcdStrobe();
	HAL_Delay(10);
    //0010xxxx
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);
	LcdStrobe();
	HAL_Delay(10);

	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);

	//il display ha acquisito la modalità 4 bit;

	}

void SetLCD (void)
 {
	//Initializza LCD
	HAL_Delay(10);
	lcd_cmd(0x28); // 0x0010 1000 Function Set
	HAL_Delay(10);

	lcd_cmd(0xF); // 0x0000 1111  Display On, Cursor On, Cursor Blink
	HAL_Delay(10);

	lcd_cmd(0x6); //Entry Mode
	HAL_Delay(10);
	lcd_cmd(0x80); //Initialize DDRAM address to zero

	lcd_cmd(0x1); //Display Clear
	//HAL_Delay(10);
	HAL_Delay(20); //perchè sia chiaro che sto partendo/ripartendo
 }




void LcdStrobe(void)
	{
	uint8_t i;
	HAL_GPIO_WritePin(PIN_EN_GPIO_Port,PIN_EN_Pin,GPIO_PIN_SET);
	for (i=0;i < CICLI_ATTESA_PER_LCD;i++);
	HAL_GPIO_WritePin(PIN_EN_GPIO_Port,PIN_EN_Pin,GPIO_PIN_RESET);
	}

void lcd_cmd(uint8_t c)
	{

	HAL_Delay(2);
	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_RESET);
	CodeOut(c);
	}

void CodeOut(uint8_t c)
	{
	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);

	if(c&0x80)
		HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_SET);
	if(c&0x40)
		HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_SET);
	if(c&0x20)
		HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
	if(c&0x10)
		HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);
	LcdStrobe();

	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);

	if(c&0x8)
		HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_SET);
	if(c&0x4)
		HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_SET);
	if(c&0x2)
		HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
	if(c&0x1)
		HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);
	LcdStrobe();

	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);
	}


void PulisciSchermo(void)   //testata
  	{
   	lcd_cmd(0x1);
  	}

void StampaInteroSuLCD(unsigned char Riga,unsigned char Colonna,uint16_t valore)
	{
	char str[10];
	Uint16ToStr(str,valore);
	StampaStringaSuLCD(Riga,Colonna,str);
	}


void go_xy(char x,char y)
	{
	unsigned char base=0;
	switch(y)
    	{
    	case 0:
    		base=MIN_PRIMA_RIGA;
    	break;
    	case 1:
    		base=MIN_SECONDA_RIGA;
    	break;
    	}
  x+=base;
  lcd_cmd(x|0X80);
}


unsigned char Uint16ToStr(char *str,uint16_t dato)
	{
	unsigned char iniziato=0,quoz=0,index=0;
	unsigned int base,rest;
	for (base=10000;base;base/=10)
		{
		quoz=dato/base;
		rest=dato%base;
		if(!iniziato)
			{
			if(quoz)
				{
				str[index++]=quoz+'0';
				iniziato=1;
				}
			}
		else
			{
			str[index++]=quoz+'0';
			}
		dato=rest;
		}
	if(!iniziato)
		str[index++]=quoz+'0';
	str[index++]=' ';
	str[index]=0;  //terminatore per la stringa
	return index;
	}


void StampaStringaSuLCD(uint8_t riga,uint8_t colonna, char *p)   //riga e colonna poi stringa
  	{
   	go_xy(colonna,riga) ;
   	lcd_puts(p);
   	NascondiCursore();
  	}


void lcd_puts(char * s)
	{
	while(*s)
		lcd_data(*s++);
	}

/* Invia un carattere all'LCD */
void lcd_data(unsigned char c)
	{
	HAL_Delay(2);

	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_SET);
	CodeOut(c);
	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_RESET);
	}

void NascondiCursore(void)
	{
	lcd_cmd(CELLA_NASCOSTA|0X80);
	}
