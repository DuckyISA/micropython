#include <stdio.h>

#include "lib/utils/pyhelp.h"

STATIC const char *help_text =
"Welcome to MicroPython!\n"
"\n"
"For online docs please visit http://docs.micropython.org/ .\n"
"\n"
"Control commands:\n"
"  CTRL-C        -- if running on VM, quit\n"
"\n"
"For further help on a specific object, type help(obj)\n"
;

STATIC mp_obj_t builtin_help(uint n_args, const mp_obj_t *args)
{
  if (n_args == 0) {
    printf("%s", help_text);
  } else {
    pyhelp_print_obj(args[0]);
  }

  return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_builtin_help_obj, 0, 1, builtin_help);
