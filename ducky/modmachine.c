#include <stdint.h>
#include <stdio.h>

#include "py/obj.h"
#include "py/runtime.h"

#include "mpducky.h"

#if MICROPY_PY_MACHINE


STATIC mp_obj_t machine_shutdown(size_t n_args, const mp_obj_t *args)
{
  u32_t exit_code = (n_args == 0 ? 0 : mp_obj_get_int(args[0]));

  halt(exit_code);
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(machine_shutdown_obj, 0, 1, machine_shutdown);


STATIC const mp_rom_map_elem_t machine_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_shutdown), MP_ROM_PTR(&machine_shutdown_obj) }
};

STATIC MP_DEFINE_CONST_DICT(machine_module_globals, machine_module_globals_table);

const mp_obj_module_t mp_module_machine = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&machine_module_globals,
};

#endif // MICROPY_PY_MACHINE
