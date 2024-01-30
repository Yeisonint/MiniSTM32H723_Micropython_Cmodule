#include "py/obj.h"
#include "py/runtime.h"
#include "lcd.h"

STATIC mp_obj_t st7735_init(void) {
    // mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Can't init LCD SPI"));
    const char text[] = "Hello world!\n";
    mp_print_str(MP_PYTHON_PRINTER, text);
    return mp_obj_new_int(lcd_init());
}

STATIC mp_obj_t st7735_lcd_test(void) {
    LCD_Test();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(st7735_init_obj, st7735_init);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(st7735_lcd_test_obj, st7735_lcd_test);

STATIC const mp_rom_map_elem_t st7735_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_st7735) },
    { MP_ROM_QSTR(MP_QSTR_init_board), MP_ROM_PTR(&st7735_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_lcd_test), MP_ROM_PTR(&st7735_lcd_test_obj) },
};
STATIC MP_DEFINE_CONST_DICT(st7735_module_globals, st7735_module_globals_table);

const mp_obj_module_t st7735_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&st7735_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_st7735, st7735_cmodule);