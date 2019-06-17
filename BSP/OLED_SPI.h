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
#ifndef  __OLED_SPI_H
#define  __OLED_SPI_H
#include "spi.h"

#define CHIP_UNSELECTED()	HAL_GPIO_WritePin(OLED_nCS_GPIO_Port, OLED_nCS_Pin, GPIO_PIN_SET)
#define CHIP_SELECTED()		HAL_GPIO_WritePin(OLED_nCS_GPIO_Port, OLED_nCS_Pin, GPIO_PIN_RESET)
#define BIAS_LIGHT_ON()		HAL_GPIO_WritePin(OLED_BLK_GPIO_Port, OLED_BLK_Pin, GPIO_PIN_SET)
#define BIAS_LIGHT_OFF()	HAL_GPIO_WritePin(OLED_BLK_GPIO_Port, OLED_BLK_Pin, GPIO_PIN_RESET)
#define DATA_SEND()				HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)//data
#define COMMAND_SEND()		HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)//cmd
#define RESET_ON()				HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_SET)
#define RESET_OFF()				HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_RESET)

//减色法(物体色)三原色
#define   YELLOW  0xF800	//黄色
#define   MAGENTA 0x07E0	//品红
#define   CYAN    0x001F	//青绿色
#define   WHITE   0x0000	//白色
#define   BLACK   0xFFFF	//黑色

//color_size
#define PURITY 0x00
#define RAND 0x01
#define RANDRAND 0x02
#define GRADIENT_COLOR 0x03
#define RUNNING_WATER 0x04
#define HORIZONTAL 0x00 //水平方向
#define VERTICAL 0x01 //垂直方向

//cmd
#define DISPLAY_OFF 0x28
#define DISPLAY_ON 	0x29

#define X_MAX	0xa1 //最大列长(长边)
#define Y_MAX	0x6a //最大行长(短边)

extern uint16_t background_color, background_color_mode;

extern void InitST7735S(void);
extern void Display_Purity_Color(uint16_t color);
extern void gray16(void);
extern void OLED_Display_ON(void);
extern void OLED_Display_OFF(void);
extern void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr,
	uint8_t chr_size, uint16_t chr_color, uint8_t chr_color_mode);
extern void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len,
	uint8_t num_size, uint16_t chr_color, uint8_t chr_color_mode);
extern void OLED_ShowString(uint8_t x, uint8_t y, char *chr,
	uint8_t Char_Size, int16_t chr_color, uint8_t chr_color_mode);

#endif  /* __OLED_SPI_H */
