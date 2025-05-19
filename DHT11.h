#ifndef _DHT11_H_
#define _DHT11_H_
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#include <REGX52.H>
#include <intrins.H>

sbit DHT11_DQ_OUT = P2^0;

void Delayms(unsigned int xms);
uchar Dht11_Get_Temp_Humi_Value(uint *temp,uint *humi);

#endif