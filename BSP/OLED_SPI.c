/** 
	* @brief    OLED BSP
	* @details  Main IC: ST7735S
							8080 MPU 8-bit Parallel
	* @author   Onion rain
	* @date     2019.3.29
	* @version  1.0
	* @par Copyright (c):  Onion rain
	* @par 日志	
	*			V	0.0	首次发布
*/
#include "OLED_SPI.h"
#include <stdlib.h>
#include "codetab.h"

/**
	* @param	[in] 
	* @param	[in] 
	*/
uint16_t background_color = BLACK;			//背景颜色,默认黑色
uint16_t background_color_mode = PURITY;	/*	背景颜色模式
																	*	This parameter can be one of the following values:
																	*	@arg HORIZONTAL:水平显示
																	*	@arg VERTICAL: 	垂直显示
																	*	@arg PURITY: 		纯色(默认)
																	*	@arg RAND:			随机色
																	*	@arg GRADIENT_COLOR:渐变灯效
																	*	@arg RUNNING_WATER:	流水灯效
																	*/
static void WriteCommand(uint8_t sdata)
{
	COMMAND_SEND();//命令
	CHIP_SELECTED();//片选信号
	HAL_SPI_Transmit(&hspi1, &sdata, 1, 0x05);
	CHIP_UNSELECTED();
}

static void WriteData(uint8_t sdata)
{
	DATA_SEND();//数据
	CHIP_SELECTED();//片选信号
	HAL_SPI_Transmit(&hspi1, &sdata, 1, 0x05);
	CHIP_UNSELECTED();
}

void InitST7735S(void)
{
  RESET_ON();
  HAL_Delay(100);
	RESET_OFF();
	HAL_Delay(50);
	RESET_ON();
	HAL_Delay(120);

  WriteCommand(0x11);//sleep out & Booster on

	HAL_Delay(120);

  WriteCommand(0x36);	//Memory Data Access Control内存数据访问控制
	WriteData(0x00);		//Display Data Direction Normal
											//LCD vertical refresh Top to Bottom
											//RGB color filter panel
											//LCD horizontal refresh Left to right
	
	WriteCommand(0xB1);	//Frame Rate Control (In normal mode/ Full colors)帧频控制
											//Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2)) 
	WriteData(0x05);		//RTNA
	WriteData(0x3A);		//FPA
	WriteData(0x3A);		//BPA
	
	WriteCommand(0xB2);	//Frame Rate Control (In Idle mode/ 8-colors)帧频控制
											//Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPB + BPB +2)) 
	WriteData(0x05);		//RTNA
	WriteData(0x3A);		//FPB
	WriteData(0x3A);		//BPB
	
	WriteCommand(0xB3);	//Frame Rate Control (In Partial mode/ full colors)帧频控制
											//Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPC + BPC +2)) 
	WriteData(0x05);		//RTNC
	WriteData(0x3A);		//FPC
	WriteData(0x3A);		//BPC
	WriteData(0x05);		//RTND
	WriteData(0x3A);		//FPD
	WriteData(0x3A);		//BPD

	WriteCommand(0xB4);	//Display Inversion Control
	WriteData(0x00);		//Dot Inversion(点反转) in all mode

	WriteCommand(0xC0);	//Power Control 1
	WriteData(0xAA);		//AVDD=5V;GVDD=4.2V
	WriteData(0x0A);		//GVCL=-4.2V
	WriteData(0x84);		//Mode=AUTO;VRHP=VRHN=0
	
	WriteCommand(0xC1);	//Power Control 2
	WriteData(0xC0);		//V25=2.4V;VGH=2AVDD+VGH25-0.5=11.9V;
											//VGL=-7.5V
	
	WriteCommand(0xC2);	//Power Control 3(in Normal mode/ Full colors) 
	WriteData(0x0D);		//Amount of Current in Operational Amplifier(运算放大器中的电流) = Small in Normal mode
											//Amount of Current in Operational Amplifier(运算放大器中的电流) = Large in Full colors
	WriteData(0x00);		//Set the Booster circuit Step-up cycle in Normal mode/ full colors. 
	
	WriteCommand(0xC3);	//Power Control 4
	WriteData(0x8D);
	WriteData(0x2A);
	
	WriteCommand(0xC4);	//Power Control 5
	WriteData(0x8D);
	WriteData(0xEE);

	WriteCommand(0xC5);	//VCOM setting
	WriteData(0x06);

	WriteCommand(0xE0);	//Gamma (‘+’polarity) Correction Characteristics Setting 
	WriteData(0x06);
	WriteData(0x1C);
	WriteData(0x10);	
	WriteData(0x14);
	WriteData(0x30);	
	WriteData(0x2B);
	WriteData(0x24);
	WriteData(0x29);
	WriteData(0x28);
	WriteData(0x26);
	WriteData(0x2E);
	WriteData(0x39);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x01);
	WriteData(0x10);
	
	WriteCommand(0xE1);	//Gamma ‘-’polarity Correction Characteristics Setting 
	WriteData(0x06);
	WriteData(0x1C);
	WriteData(0x10);
	WriteData(0x14);
	WriteData(0x30);
	WriteData(0x2B);
	WriteData(0x24);
	WriteData(0x29);
	WriteData(0x28);
	WriteData(0x26);
	WriteData(0x2E);
	WriteData(0x39);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x01);
	WriteData(0x10);
	
	WriteCommand(0x3A);	//Interface Pixel Format
	WriteData(0x05);		//RGB 16-bit/pixel
	
	WriteCommand(0x29);	//display on
	
	HAL_Delay(120);
}

static void WriteData16(uint16_t DATA)
{
	WriteData(DATA>>8);
	WriteData(DATA);
}

//设置ROI区域
static void ROI_address(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end)
{
	WriteCommand(0x2A);	//Column Address Set 
	WriteData(0x00);
	WriteData(y_start);
	WriteData(0x00);
	WriteData(y_end);//实测获得的数据

	WriteCommand(0x2B);	//Row Address Set 
	WriteData(0x00);
	WriteData(x_start);
	WriteData(0x00);
	WriteData(x_end);//实测获得的数据

	WriteCommand(0x2C);	//Memory Write
}

void Display_Purity_Color(uint16_t color)
{
	uint16_t i, j;
	ROI_address(0x00, X_MAX-1, 0x00, Y_MAX-1);

	for(i=0; i<X_MAX; i++)//长
		for(j=0; j<Y_MAX; j++)//宽
			WriteData16(color);
}

void gray16(void)//Display 16TH Gray
{
	uint8_t i, j;
	ROI_address(0x00, X_MAX-1, 0x00, Y_MAX-1);
	
	for(j=0; j<X_MAX; j++)
	{
		for(i=0; i<6; i++) WriteData16(0x0000);
		for(i=6; i<13; i++) WriteData16(0x1082);
		for(i=13; i<19; i++) WriteData16(0x2104);
		for(i=19; i<26; i++) WriteData16(0x3186);
		for(i=26; i<32; i++) WriteData16(0x4208);
		for(i=32; i<39; i++) WriteData16(0x528a);
		for(i=39; i<45; i++) WriteData16(0x630C);
		for(i=45; i<52; i++) WriteData16(0x738e);
		for(i=52; i<59; i++) WriteData16(0x8410);
		for(i=59; i<65; i++) WriteData16(0x9492);
		for(i=65; i<71; i++) WriteData16(0xa514);
		for(i=71; i<78; i++) WriteData16(0xb596);
		for(i=78; i<84; i++) WriteData16(0xc618);
		for(i=84; i<91; i++) WriteData16(0xd69a);
		for(i=91; i<98; i++) WriteData16(0xe71c);
		for(i=98; i<Y_MAX; i++) WriteData16(0xf79e);
	}
}

void OLED_Display_ON(void)
{
		WriteCommand(DISPLAY_ON);
}

void OLED_Display_OFF(void)
{
		WriteCommand(DISPLAY_OFF);
}

/** @brief  在指定位置显示一个字符
	* @param	[in] x x轴起始位置(0~160)
	* @param	[in] y y轴起始位置(0~105)
	* @param	[in] chr 要显示的字符
	* @param	[in] chr_size 字号(8/16/28)
	* @param	[in] chr_color 字符颜色(仅纯色模式有效)
	* @param	[in] chr_color_mode 字符颜色模式
  *					This parameter can be one of the following values:
	*         @arg HORIZONTAL:水平显示
	*         @arg VERTICAL: 	垂直显示
	*         @arg PURITY: 		纯色
	*         @arg RAND:			随机色(every char)
	*         @arg RANDRAND:	随机色(every pixel)
	*         @arg GRADIENT_COLOR:渐变灯效
	*         @arg RUNNING_WATER:	流水灯效
	*/
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr,
	uint8_t chr_size, uint16_t chr_color, uint8_t chr_color_mode)
{
	y += chr_size;
	uint8_t x_index = 0, y_index = 0;
	chr -= ' ';//得到偏移后的值
	switch(chr_color_mode)
	{
		case PURITY:break;
		case RAND:chr_color = rand()%0xffff;break;
		case GRADIENT_COLOR:break;
		case RUNNING_WATER:break;
		default:break;
	}
//	if(x >= X_MAX)//超过每行最大值则显示到下一行
//	{
//		x = 0;
//		y += chr_size+1;
//	}
	y = Y_MAX - y;
	if(chr_size == 8)
	{
		ROI_address(x, x+6-1, y, y+8-1);//设置刷新区域
		for(x_index=0; x_index<6; x_index++)//列系数
			for(y_index=0; y_index<8; y_index++)//行系数
				if((F4x8[chr][x_index]>>(7-y_index)) & 0x01)
					if(chr_color_mode == RANDRAND)
						WriteData16(chr_color = rand()%0xffff);
					else
						WriteData16(chr_color);
				else WriteData16(background_color);
	}else if(chr_size == 16)
	{
		ROI_address(x, x+8-1, y, y+16-1);//设置刷新区域
		for(x_index=0; x_index<8; x_index++)//列系数
			for(y_index=0; y_index<16; y_index++)//行系数
				if(y_index<8){
					if((F8x16[chr][(x_index*2+1)]>>y_index) & 0x01)
						if(chr_color_mode == RANDRAND)
							WriteData16(chr_color = rand()%0xffff);
						else
							WriteData16(chr_color);
					else WriteData16(background_color);}
				else{
					if((F8x16[chr][(x_index*2)]>>(y_index-8)) & 0x01)
						if(chr_color_mode == RANDRAND)
							WriteData16(chr_color = rand()%0xffff);
						else
							WriteData16(chr_color);
					else WriteData16(background_color);}
	}else if(chr_size == 28)
	{
		ROI_address(x, x+14-1, y, y+28-1);//设置刷新区域
		
		unsigned char F14x28_part[14][4];//[列数][每列用多少个字节表示]
		int8_t bit_index = 0, byte_index = 3;
		for(x_index=0; x_index<56; x_index++)//数组深拷贝
			*(&F14x28_part[0][0]+x_index) = F14x28[chr][x_index];
		x_index = 0;
		for(x_index=0; x_index<14; x_index++)//列系数
		{
			for(y_index=0; y_index<28; y_index++)//行系数
			{
				if(F14x28_part[x_index][byte_index]>>bit_index & 0x01)
					if(chr_color_mode == RANDRAND)
							WriteData16(chr_color = rand()%0xffff);
					else
						WriteData16(chr_color);
				else WriteData16(background_color);
				
				bit_index++;//遍历过一个元素，位指针后移一位
				if(bit_index > 7)//8位遍历完，指向下一字节
				{
					bit_index = 0;
					byte_index--;
				}
				if(byte_index < 0)
					while(1);//报错
			}
			bit_index = 0;
			byte_index = 3;
		}
	}else//报错
		while(1);
}

//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result = 1;
	while(n--)result *= m;
	return result;
}

/** @brief  在指定位置显示一串数字
	* @param	[in] x x轴起始位置(0~160)
	* @param	[in] y y轴起始位置(0~105)
	* @param	[in] num 要显示的数字
	* @param	[in] len 数字位数
	* @param	[in] num_size 字号(8/16)
	* @param	[in] chr_color 字符颜色(仅纯色模式有效)
	* @param	[in] chr_color_mode 字符颜色模式
  *					This parameter can be one of the following values:
	*         @arg HORIZONTAL:水平显示
	*         @arg VERTICAL: 	垂直显示
	*         @arg PURITY: 		纯色
	*         @arg RAND:			随机色(every char)
	*         @arg RANDRAND:	随机色(every pixel)
	*         @arg GRADIENT_COLOR:渐变灯效
	*         @arg RUNNING_WATER:	流水灯效
	*/
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len,
	uint8_t num_size, uint16_t chr_color, uint8_t chr_color_mode)
{
	uint8_t digit_index/*数位指针*/, remainder/*余数*/;
	uint8_t enshow = 0;//判断是否为第一位有效数字，是则为0，否则为1
	for(digit_index=0; digit_index<len; digit_index++)//遍历每一位
	{
		remainder = (num/oled_pow(10, len-digit_index-1))%10;
		if(enshow==0 && digit_index<(len-1))//首位为0则显示" "
		{
			if(remainder==0)
			{
				OLED_ShowChar(x+(num_size/2)*digit_index, y ,' ', num_size, chr_color, chr_color_mode);
				continue;
			}else enshow = 1;
		}
	 	OLED_ShowChar(x+(num_size/2)*digit_index, y, remainder+'0', num_size, chr_color, chr_color_mode);
	}
}

/** @brief  在指定位置显示一个字符串
	* @param	[in] x x轴起始位置(0~160)
	* @param	[in] y y轴起始位置(0~105)
	* @param	[in] *chr 要显示的字符串指针
	* @param	[in] chr_size 字号(8/16)
	* @param	[in] chr_color 字符颜色(仅纯色模式有效)
	* @param	[in] chr_color_mode 字符颜色模式
  *					This parameter can be one of the following values:
	*         @arg HORIZONTAL:水平显示
	*         @arg VERTICAL: 	垂直显示
	*         @arg PURITY: 		纯色
	*         @arg RAND:			随机色(every char)
	*         @arg RANDRAND:	随机色(every pixel)
	*         @arg GRADIENT_COLOR:渐变灯效
	*         @arg RUNNING_WATER:	流水灯效
	*/
void OLED_ShowString(uint8_t x, uint8_t y, char *chr,
	uint8_t chr_size, int16_t chr_color, uint8_t chr_color_mode)
{
	uint8_t j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], chr_size, chr_color, chr_color_mode);
		x += chr_size/2;
		if(x+chr_size/2 > X_MAX)
		{
			x = 0;
			y += chr_size+2;
		}
		j++;
	}
}

