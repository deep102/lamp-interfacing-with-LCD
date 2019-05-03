#include<reg51.h>
sbit rs=P3^5;
sbit rw=P3^6;
sbit en=P3^7;
sbit sw=P2^0;
sfr ldat=0x90;

void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay(int);
void main()
{
	int i;
	char x,o,f;
	char stat1[10]="lamp on";
	char stat2[10]="lamp off";
	
	lcdcmd(0x38);
	delay(10);
	lcdcmd(0x0E);
	delay(10);
	lcdcmd(0x01);
	delay(10);
	lcdcmd(0x06);
	delay(10);
	lcdcmd(0x80);
	delay(10);
	
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;

	while(1)
	{
		while(RI==0);
		x=SBUF;
		if(x=='o')
		{
				sw=1;
			for(i=0;i<10;i++)
			{
				lcddat(stat1[i]);
			}
			lcdcmd(0x01);
		}
		if(x=='f')
		{
			sw=0;
			for(i=0;i<10;i++)
			{
				lcddat (stat2[i]);
			}
			lcdcmd(0x01);
		
		lcddat(x);
		RI=0;
	}
 }
}
void lcdcmd(char cmd)
{
	ldat=cmd;
	rs=0;
	rw=0;
	en=1;
	delay(10);
	en=0;
}
void lcddat(char dat)
{
	ldat=dat;
	rs=1;
	rw=0;
	en=1;
	delay(10);
	en=0;
}
void delay(int itime)
{
	int i,j;
	for(i=0;i<1000;i++)
	  for(j=0;j<itime;j++);
}