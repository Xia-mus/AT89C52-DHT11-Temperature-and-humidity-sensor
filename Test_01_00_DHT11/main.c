#include <REGX52.H>
#include "DHT11.H"
#include "LCD1602.H"

unsigned int temp,humi;

void main ()
{
	LCD_Init();
	while(1)
	{
		Dht11_Get_Temp_Humi_Value(&temp,&humi);
		LCD_ShowString(1,1,"Humi:");
		LCD_ShowNum(1,6,humi,2);
		LCD_ShowString(2,1,"Temp:");
		LCD_ShowNum(2,6,temp,2);
		Delayms(500);
	}
}
