#include "py/obj.h"
#include "py/runtime.h"
#include "board_tft.h"
#include "lib/lcd.h"

STATIC mp_obj_t st7735_init(void) {
    uint8_t res=HAL_OK;

    res=TFT_SPI_init();
    if (res!=HAL_OK){
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Can't init LCD SPI"));
        return mp_obj_new_int(HAL_ERROR);
    }
    res=TFT_backlight_init();
    if (res!=HAL_OK){
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Can't init LCD Backlight (TIM1)"));
        return mp_obj_new_int(HAL_ERROR);
    }
    return mp_obj_new_int(HAL_OK);
}

STATIC mp_obj_t st7735_lcd_test() {
    LCD_Test();
    LCD_SetBrightness(100);
    return mp_const_none;
}

STATIC mp_obj_t st7735_lcd_set_brightness(mp_obj_t state_obj) {
    mp_int_t s = mp_obj_get_int(state_obj);
    LCD_SetBrightness((uint32_t)s);
    return mp_const_none;
}

STATIC mp_obj_t st7735_lcd_get_brightness(void) {
    return mp_obj_new_int(LCD_GetBrightness());
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(st7735_init_obj, st7735_init);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(st7735_lcd_test_obj, st7735_lcd_test);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(st7735_lcd_set_brightness_obj, st7735_lcd_set_brightness);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(st7735_lcd_get_brightness_obj, st7735_lcd_get_brightness);

STATIC const mp_rom_map_elem_t st7735_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_st7735) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&st7735_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_test), MP_ROM_PTR(&st7735_lcd_test_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_set_brightness), MP_ROM_PTR(&st7735_lcd_set_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_get_brightness), MP_ROM_PTR(&st7735_lcd_get_brightness_obj) },
};
STATIC MP_DEFINE_CONST_DICT(st7735_module_globals, st7735_module_globals_table);

const mp_obj_module_t st7735_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&st7735_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_st7735, st7735_user_cmodule);