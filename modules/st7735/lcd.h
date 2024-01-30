#ifndef __LCD_H
#define __LCD_H		

#include "lib/st7735.h"
#include <stdio.h>

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C  
#define GRAYBLUE       	 0X5458

// #define LCD_BACKLIGHT_PIN    pin_E10
// #define LCD_RS_PIN           pin_E13
// #define LCD_CS_PIN           pin_E11
// #define LCD_BACKLIGHT_ON     mp_hal_pin_low(LCD_BACKLIGHT_PIN)
// #define LCD_BACKLIGHT_OFF    mp_hal_pin_high(LCD_BACKLIGHT_PIN)
// #define LCD_RS_SET           mp_hal_pin_high(LCD_BACKLIGHT_PIN);
// #define LCD_RS_RESET         mp_hal_pin_low(LCD_BACKLIGHT_PIN);
// #define LCD_CS_SET           mp_hal_pin_high(LCD_BACKLIGHT_PIN);
// #define LCD_CS_RESET         mp_hal_pin_low(LCD_BACKLIGHT_PIN);

extern ST7735_Object_t st7735_pObj;
extern uint32_t st7735_id;
extern uint16_t POINT_COLOR;
extern uint16_t BACK_COLOR; 
extern ST7735_Ctx_t ST7735Ctx;

int32_t lcd_init(void);
void LCD_Test(void);
// static int32_t lcd_gettick(void);
// static int32_t lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length);
// static int32_t lcd_readreg(uint8_t reg,uint8_t* pdata);
// static int32_t lcd_senddata(uint8_t* pdata,uint32_t length);
// static int32_t lcd_recvdata(uint8_t* pdata,uint32_t length);

#endif 