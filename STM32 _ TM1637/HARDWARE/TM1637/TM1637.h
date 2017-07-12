/******************************Copyright (c)***********************************
*                Jiangsu Zhihai Electronic Technology Co., Ltd.
*                      Research & Development Department
*
*													www.smarthealth-tech.com
*
-------------------------------------------------------------------------------
* @file    TM1637.h
* @author  GU DONGDONG
* @date    2015-11-25  
*******************************************************************************/
#ifndef TM1637_H
#define TM1637_H

#include "sys.h"

#define TM1637_CLK           PCout(2)  
#define TM1637_DIO           PCout(3)  
#define TM1637_READ_DIO      PCin(3) 
  
//IO·½ÏòÉèÖÃ
#define TM1637_DIO_IN()     {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=8<<12;}
#define TM1637_DIO_OUT()    {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=3<<12;}

 
void TM1637_Delay_us(unsigned  int Nus); 
void TM1637_Start(void);
void TM1637_Ack(void);
void TM1637_Stop(void);
void TM1637_WriteByte(unsigned char oneByte);
unsigned char TM1637_ScanKey(void);
void TM1637_NixieTubeDisplay(void);

void TM1637_Init(void);
void TM1637LED_Init(void);
void TIM1637_SHOW_ADD_DATA(u8 TM1637_add,u8 TM163_data);
void TIM1637_printf(u8 TM1637_add0_data,u8 TM1637_add1_data,u8 TM1637_add2_data,u8 TM1637_add3_data);
 
#endif
