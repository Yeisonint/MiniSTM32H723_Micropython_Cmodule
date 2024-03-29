#include "py/obj.h"
#include "py/runtime.h"
#include "dcmi.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "lcd.h"
#include "camera.h"
#include "board.h"

void Error_Handler(void)
{
    mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Error Handler called"));
}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	static uint32_t count = 0,tick = 0;

	if(HAL_GetTick() - tick >= 1000)
	{
		tick = HAL_GetTick();
		Camera_FPS = count;
		count = 0;
	}
	count ++;
	
  DCMI_FrameIsReady ++;
  mp_print_str(MP_PYTHON_PRINTER, "DCMI frame event");
}

STATIC mp_obj_t init(void)
{
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_DCMI_Init();
    MX_I2C1_Init();
    MX_SPI4_Init();
    MX_TIM1_Init();
    board_button_init();
    board_led_init();
#ifdef TFT96
    Camera_Init_Device(&hi2c1, FRAMESIZE_QQVGA);
#elif TFT18
    Camera_Init_Device(&hi2c1, FRAMESIZE_QQVGA2);
#endif
    // return mp_obj_new_int(HAL_OK);
    return mp_const_none;
}

STATIC mp_obj_t lcd_test(void)
{
    LCD_Test();
    int ret = HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&pic, FrameWidth * FrameHeight * 2 / 4);
    mp_printf(MP_PYTHON_PRINTER, "Error on start dma %d", ret);
    ST7735_FillRGBRect(&st7735_pObj, 0, 0, (uint8_t *)&pic[20][0], ST7735Ctx.Width, 80);

    while (!board_button_getstate())
    {
        if (DCMI_FrameIsReady)
        {
            DCMI_FrameIsReady = 0;
#ifdef TFT96
            ST7735_FillRGBRect(&st7735_pObj, 0, 0, (uint8_t *)&pic[20][0], ST7735Ctx.Width, 80);
#elif TFT18
            ST7735_FillRGBRect(&st7735_pObj, 0, 0, (uint8_t *)&pic[0][0], ST7735Ctx.Width, ST7735Ctx.Height);
#endif
            board_led_toggle();
        }
    }
    LCD_Test();
    return mp_const_none;
}

// STATIC mp_obj_t board_board_led_set(mp_obj_t state_obj)
// {
//     mp_int_t s = mp_obj_get_int(state_obj);
//     board_led_set(s);
//     return mp_const_none;
// }

STATIC MP_DEFINE_CONST_FUN_OBJ_0(init_obj, init);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(board_lcd_test, lcd_test);
// STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_board_led_set_obj, board_board_led_set);

STATIC const mp_rom_map_elem_t board_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_board)},
    {MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&init_obj)},
    {MP_ROM_QSTR(MP_QSTR_lcd_test), MP_ROM_PTR(&board_lcd_test)},
    // { MP_ROM_QSTR(MP_QSTR_led_set), MP_ROM_PTR(&board_board_led_set_obj) },
};
STATIC MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_user_cmodule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&board_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_board, board_user_cmodule);