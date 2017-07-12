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
#include "TM1637.h"
#include "delay.h"
/** Write multiple bits in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 */
void TM1637_Delay_us(unsigned  int Nus)
{
 for(;Nus>0;Nus--)
	{
	  __nop();
	 	__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
}
/*===================================================================================================
数字库
 unsigned char SEGData[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//1-9	
 unsigned char SEGDataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef}; //有小数点，只用于0x01
=====================================================================================================*/
void TM1637_Start(void)//起始函数
{
	TM1637_DIO_OUT(); 
  TM1637_CLK = 1;
	TM1637_DIO = 1;
	delay_us(2);
	TM1637_DIO = 0;
}
void TM1637_Ack(void)//接受应答信号
{
	TM1637_DIO_IN(); 
  TM1637_CLK = 0;
	TM1637_Delay_us(5);
	while(TM1637_READ_DIO);
	TM1637_CLK = 1;
	delay_us(2);
	TM1637_CLK = 0;
}
void TM1637_Stop(void)//停止信号
{
	TM1637_DIO_OUT(); 
	TM1637_CLK = 0;
	delay_us(2);
	TM1637_DIO = 0;
	delay_us(2);
	TM1637_CLK = 1;
	delay_us(2);
	TM1637_DIO = 1;
}
void TM1637_WriteByte(unsigned char oneByte)//写入一个字节
{
 unsigned char i;
	TM1637_DIO_OUT(); 
	for(i=0;i<8;i++)
	{
	 TM1637_CLK = 0;
		if(oneByte&0x01)
		{
			TM1637_DIO = 1;
		}
		else
		{
			TM1637_DIO = 0;
		}
		delay_us(3);
		oneByte=oneByte>>1;
		TM1637_CLK = 1;
		delay_us(3);
	}
}

unsigned char TM1637_ScanKey(void)//键盘扫描
{
	unsigned char reKey,i;
	TM1637_Start();
	TM1637_WriteByte(0x42);
	TM1637_Ack();
	TM1637_DIO = 1;
	TM1637_DIO_IN(); 
	for(i=0;i<8;i++)
	{
	  TM1637_CLK = 0;
		reKey=reKey>>1;
		delay_us(30);
		TM1637_CLK = 1;
		if(TM1637_READ_DIO)
		{
		  reKey=reKey|0x80;
		}
		else
		{
		  reKey=reKey|0x00;
		}
		delay_us(30);
	}
  TM1637_Ack();
	TM1637_Stop();
	return(reKey);
}
void TM1637_NixieTubeDisplay(void)//显示函数,固定地址模式
{
	TM1637_Start();
	TM1637_WriteByte(0x44);//固定地址
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0xC2);
	TM1637_Ack();
		

		TM1637_WriteByte(0xb0);
		TM1637_Ack();

	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0x8f);
	TM1637_Ack();
	TM1637_Stop();
}

void TM1637_Init(void)//初始化函数PC2-clk,pc3-dio
{
 
 GPIO_InitTypeDef  GPIO_InitStructure; 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;				  
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
 GPIO_Init(GPIOC, &GPIO_InitStructure);					  

}
 
void TIM1637_SHOW_ADD_DATA(u8 TM1637_add,u8 TM163_data)//某一位，显示某个数 //固定地址模式
{
	TM1637_Start();
	TM1637_WriteByte(0x44);
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(TM1637_add);
	TM1637_Ack();
		
		TM1637_WriteByte(TM163_data);
		TM1637_Ack();
	
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0x8f);
	TM1637_Ack();
	TM1637_Stop();
}
//========================================================================
//参数分别为四个数码管所显示的数字，模式为自动+1  (0x40)
//========================================================================
void TIM1637_printf(u8 TM1637_add0_data,u8 TM1637_add1_data,u8 TM1637_add2_data,u8 TM1637_add3_data)
{	
	unsigned char i;
	TM1637_Start();
	TM1637_WriteByte(0x40);
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0xC0);
	TM1637_Ack();	
	for(i=0;i<4;i++)
	{
		if(i==0){TM1637_WriteByte(TM1637_add0_data);TM1637_Ack();}
		if(i==1){TM1637_WriteByte(TM1637_add1_data);TM1637_Ack();}
		if(i==2){TM1637_WriteByte(TM1637_add2_data);TM1637_Ack();}
		if(i==3){TM1637_WriteByte(TM1637_add3_data);TM1637_Ack();}
	}
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0x8f);
	TM1637_Ack();
	TM1637_Stop();


}


