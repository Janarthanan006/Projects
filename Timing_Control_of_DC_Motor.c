#include<reg51.h>
#include<AT89S52.h>
#define RS P3_2
#define RW P3_7
#define EN P3_4
#define motor P3_5
#define swicth P3_3

void delay1(unsigned int time)
{
unsigned int i, j;
for(i=0; i<time; i++)
for(j=0; j<1275; j++);
}
void LCD_command(unsigned char command)
{
P2 = command;
RS = 0;
RW = 0;
EN = 1; delay1(1); EN = 0;
}
void LCD_data(unsigned char disp_data)
{

6

P2 = disp_data;
RS = 1; RW = 0;
EN = 1; delay1(1); EN = 0;
}
void main()
{
unsigned char message1[15] = "Motor runing:";
unsigned char message2[16] = "Seconds:";
unsigned char message3[16] = " Motor STOP...";
unsigned int i,j,l;
while(1){
LCD_command(0x38);
delay1(10);
LCD_command(0x0F);
delay1(10);
if(swicth==0){
LCD_command(0x01);
delay1(10);
LCD_command(0x81);
delay1(10);
i=0;
while(message1[i] != '\0')
{
LCD_data(message1[i]);
i++;
delay1(30);
}
LCD_command(0xC3);
i=0;
while(message2[i] != '\0')
{
LCD_data(message2[i]);
i++;
delay1(19);
}
delay1(100);
motor=0;
LCD_command(0x0C);
for(l=0x30;l<0x36;l++)
{
for(j=0x30; j<=0x39; j++)
{
LCD_data(l);
LCD_data(j);
LCD_command(0xC11);
LCD_command(0xC12);

7

if(0x35==l&&0x39==j)
{
LCD_command(0x01);
delay1(1);
LCD_command(0x81);
i=0;
while(message3[i] != '\0')
{
LCD_data(message3[i]);
i++;
delay1(30);
}
motor=1;
}
delay1(100);
}
}
delay1(150);
}
}
}
