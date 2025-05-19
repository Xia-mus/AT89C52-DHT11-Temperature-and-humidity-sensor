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
		
		while(DHT11_DQ_OUT == 0);//�ȴ�50us�͵�ƽ��ȥ
		delay_dht11(3);					//��ʱ3us
		if(DHT11_DQ_OUT)
			dat |= 0x01;
		
		retry=0;
		while(DHT11_DQ_OUT&&retry<100)//�ȴ���Ϊ�͵�ƽ 12-14us ��ʼ
		{
			retry++;
			_nop_();
		}
	}
	return dat;
}
/****
*******��DHT11��ȡһ�����ݺ���
*******�������壺	temp:�¶�ֵ(��Χ:0~50��)
*******           humi:ʪ��ֵ(��Χ:20%~95%)
*******����ֵ��0:����; 1:��ȡʧ��
*****/
uchar Dht11_Get_Temp_Humi_Value(uint *temp,uint *humi)
{        
 	uchar buf[5];
	uchar i;
	
	DHT11_DQ_OUT=0; 									//����DQ
	Delayms(20);    						//��������18ms
	DHT11_DQ_OUT=1; 									//DQ=1 
	delay_dht11(4);
	
	if(DHT11_DQ_OUT == 0)
	{
		while(DHT11_DQ_OUT == 0);				//�ȴ�80us�ĵ͵�ƽ��ȥ
		while(DHT11_DQ_OUT == 1);				//�ȴ�80us�ĸߵ�ƽ��ȥ
		for(i=0;i<5;i++)				 				//��ȡ40λ����
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])//У���
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