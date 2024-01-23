#include "py/obj.h"
#include "py/runtime.h"
#include "ministm32h723_board.h"
#include "st7735/lcd.h"

STATIC mp_obj_t miniutils_init(void) {
    uint8_t res=HAL_OK;

    board_led_init();
    board_button_init();
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

STATIC mp_obj_t miniutils_board_led_set(mp_obj_t state_obj) {
    mp_int_t s = mp_obj_get_int(state_obj);
    board_led_set(s);
    return mp_const_none;
}

STATIC mp_obj_t miniutils_board_led_toggle(void) {
    board_led_toggle();
    return mp_const_none;
}

STATIC mp_obj_t miniutils_board_button_state(void) {
    return board_button_state()!=0?mp_const_true:mp_const_false;
}

STATIC mp_obj_t miniutils_lcd_test() {
    LCD_Test();
    return mp_const_none;
}

STATIC mp_obj_t miniutils_lcd_set_brightness(mp_obj_t state_obj) {
    mp_int_t s = mp_obj_get_int(state_obj);
    LCD_SetBrightness((uint32_t)s);
    return mp_const_none;
}

STATIC mp_obj_t miniutils_lcd_get_brightness(void) {
    return mp_obj_new_int(LCD_GetBrightness());
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(miniutils_init_obj, miniutils_init);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(miniutils_board_led_set_obj, miniutils_board_led_set);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(miniutils_board_led_toggle_obj, miniutils_board_led_toggle);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(miniutils_board_button_state_obj, miniutils_board_button_state);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(miniutils_lcd_test_obj, miniutils_lcd_test);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(miniutils_lcd_set_brightness_obj, miniutils_lcd_set_brightness);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(miniutils_lcd_get_brightness_obj, miniutils_lcd_get_brightness);

STATIC const mp_rom_map_elem_t miniutils_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_miniutils) },
    { MP_ROM_QSTR(MP_QSTR_init_board), MP_ROM_PTR(&miniutils_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_led_set), MP_ROM_PTR(&miniutils_board_led_set_obj) },
    { MP_ROM_QSTR(MP_QSTR_led_toggle), MP_ROM_PTR(&miniutils_board_led_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_button_state), MP_ROM_PTR(&miniutils_board_button_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_test), MP_ROM_PTR(&miniutils_lcd_test_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_set_brightness), MP_ROM_PTR(&miniutils_lcd_set_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_get_brightness), MP_ROM_PTR(&miniutils_lcd_get_brightness_obj) },
};
STATIC MP_DEFINE_CONST_DICT(miniutils_module_globals, miniutils_module_globals_table);

const mp_obj_module_t miniutils_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&miniutils_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_miniutils, miniutils_user_cmodule);