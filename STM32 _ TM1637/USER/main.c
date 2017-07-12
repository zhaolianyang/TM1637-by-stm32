#include "led.h"
#include "delay.h"
#include "sys.h"
#include "TM1637.h"
//数字库
 unsigned char SEGData[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//1-9	
 unsigned char SEGDataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef}; //有小数点，只用于0x01
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TM1637_Init();
	while(1)
	{
		TIM1637_printf(SEGData[3],SEGDataDp[2],SEGData[1],SEGData[0]);		
	}
 }

