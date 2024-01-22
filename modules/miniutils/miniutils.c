#include "py/obj.h"
#include "py/runtime.h"
#include "st7735/lcd.h"
#include "st7735/tim.h"

STATIC mp_obj_t miniutils_stt7735_init() {
    MX_TIM1_Init();
    LCD_Test();
    return MP_OBJ_NULL;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(miniutils_stt7735_init_obj, miniutils_stt7735_init);

STATIC const mp_rom_map_elem_t miniutils_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_miniutils) },
    { MP_ROM_QSTR(MP_QSTR_add_ints), MP_ROM_PTR(&miniutils_stt7735_init_obj) },
};
STATIC MP_DEFINE_CONST_DICT(miniutils_module_globals, miniutils_module_globals_table);

const mp_obj_module_t miniutils_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&miniutils_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_miniutils, miniutils_user_cmodule);