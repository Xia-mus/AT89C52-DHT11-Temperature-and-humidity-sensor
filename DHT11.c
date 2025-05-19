#include "dht11.h"
//#include "Delay.h"

void delay_dht11(uint t)
{
	while(t--);
}

void Delayms(unsigned int xms)	//@11.0592MHz
{
	int k;
	for(k=0;k<xms;k++)
	{
		unsigned char data i, j;
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

uchar DHT11_Read_Byte(void)    
{        
  uchar i,retry,dat=0;
	for (i=0;i<8;i++) 
	{
		dat<<=1;
		
		while(DHT11_DQ_OUT == 0);//等待50us低电平过去
		delay_dht11(3);					//延时3us
		if(DHT11_DQ_OUT)
			dat |= 0x01;
		
		retry=0;
		while(DHT11_DQ_OUT&&retry<100)//等待变为低电平 12-14us 开始
		{
			retry++;
			_nop_();
		}
	}
	return dat;
}
/****
*******从DHT11读取一次数据函数
*******参量定义：	temp:温度值(范围:0~50°)
*******           humi:湿度值(范围:20%~95%)
*******返回值：0:正常; 1:读取失败
*****/
uchar Dht11_Get_Temp_Humi_Value(uint *temp,uint *humi)
{        
 	uchar buf[5];
	uchar i;
	
	DHT11_DQ_OUT=0; 									//拉低DQ
	Delayms(20);    						//拉低至少18ms
	DHT11_DQ_OUT=1; 									//DQ=1 
	delay_dht11(4);
	
	if(DHT11_DQ_OUT == 0)
	{
		while(DHT11_DQ_OUT == 0);				//等待80us的低电平过去
		while(DHT11_DQ_OUT == 1);				//等待80us的高电平过去
		for(i=0;i<5;i++)				 				//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])//校验和
		{
			*humi=buf[0]+buf[1];
			*temp=buf[2]+buf[3];
		}
		else
			return 1;
	}
	else
		return 1;
	return 0;	    
}