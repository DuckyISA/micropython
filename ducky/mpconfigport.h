/**
 * Options to control how Micro Python for Ducky is built.
 */

#ifndef __MIPY_DUCKY_H__
#define __MIPY_DUCKY_H__

// Include from libducky
#include <types.h>


// Define these for lowlevel.s
#define DUCKY_STACK_START           0x00090000
#define DUCKY_STACK_SIZE            0x00008000 // 32kB
//#define DUCKY_STACK_SIZE_LO         0x8000
//#define DUCKY_STACK_SIZE_HI         0x0000

//#define DUCKY_HEAP_START            0x00098000
#define DUCKY_HEAP_SIZE             0x00100000 // 1MB

// Debug enabled pretty much everywhere...
#define MICROPY_DEBUG_MALLOC        (0)
#define MICROPY_DEBUG_GC            (0)
#define MICROPY_DEBUG_BC            (0)
#define MICROPY_DEBUG_QSTR          (0)
#define MICROPY_DEBUG_RUNTIME       (0)
#define MICROPY_DEBUG_GLUE          (0)
#define MICROPY_DEBUG_VM            (0)
#define MICROPY_DEBUG_OBJTYPE       (0)
#define MICROPY_DEBUG_OBJFUN        (0)
#define MICROPY_DEBUG_PRINTERS      (0)

#define MICROPY_STACK_CHECK         (1)

#define MICROPY_WARNINGS            (1)
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_DETAILED)
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (0)
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE (0)

#define MICROPY_STACKLESS           (0)

#define MICROPY_ENABLE_COMPILER     (1)

#define MICROPY_QSTR_BYTES_IN_HASH  (1)
//#define MICROPY_QSTR_EXTRA_POOL     mp_qstr_frozen_const_pool
#define MICROPY_ALLOC_PATH_MAX      (256)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT (16)
#define MICROPY_EMIT_X64            (0)
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_COMP_MODULE_CONST   (0)
#define MICROPY_COMP_CONST          (0)
#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (0)
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (0)
#define MICROPY_OPT_COMPUTED_GOTO   (0)
#define MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE (1)
#define MICROPY_OPT_MPZ_BITWISE     (0)
#define MICROPY_MEM_STATS           (0)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_GC_ALLOC_THRESHOLD  (0)
#define MICROPY_REPL_EVENT_DRIVEN   (0)
#define MICROPY_HELPER_REPL         (1)
#define MICROPY_HELPER_LEXER_UNIX   (0)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_ENABLE_DOC_STRING   (0)
#define MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG (0)
#define MICROPY_PY_ASYNC_AWAIT      (0)
#define MICROPY_PY_BUILTINS_BYTEARRAY (0)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (0)
#define MICROPY_PY_BUILTINS_ENUMERATE (0)
#define MICROPY_PY_BUILTINS_FILTER  (0)
#define MICROPY_PY_BUILTINS_FROZENSET (0)
#define MICROPY_PY_BUILTINS_REVERSED (0)
#define MICROPY_PY_BUILTINS_SET     (0)
#define MICROPY_PY_BUILTINS_SLICE   (0)
#define MICROPY_PY_BUILTINS_PROPERTY (0)
#define MICROPY_PY_BUILTINS_MIN_MAX (0)
#define MICROPY_PY___FILE__         (0)
#define MICROPY_PY_GC               (1)
#define MICROPY_PY_ARRAY            (0)
#define MICROPY_PY_ATTRTUPLE        (0)
#define MICROPY_PY_COLLECTIONS      (0)
#define MICROPY_PY_MATH             (0)
#define MICROPY_PY_CMATH            (0)
#define MICROPY_PY_IO               (0)
#define MICROPY_PY_STRUCT           (0)
#define MICROPY_PY_SYS              (1)
#define MICROPY_PY_SYS_EXIT         (1)
#define MICROPY_PY_MACHINE          (1)
#define MICROPY_MODULE_FROZEN_MPY   (0)
#define MICROPY_CPYTHON_COMPAT      (0)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_NONE)
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_NONE)
#define MICROPY_MODULE_FROZEN_STR   (0)

#define MP_ENDIANNESS_LITTLE        (1)
#define MICROPY_OBJ_BASE_ALIGNMENT  __attribute__((aligned(4)))

// type definitions for the specific machine

#define BYTES_PER_WORD (4)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

// This port is intended to be 32-bit, but unfortunately, int32_t for
// different targets may be defined in different ways - either as int
// or as long. This requires different printf formatting specifiers
// to print such value. So, we avoid int32_t and use int directly.
#define UINT_FMT "%u"
#define INT_FMT "%d"

#ifndef __ASSEMBLER__
typedef i32_t mp_int_t;
typedef u32_t mp_uint_t;
typedef i32_t mp_off_t;
#endif // ! __ASSEMBLER__

#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

// extra built in names to add to the global namespace
#ifndef __ASSEMBLER__
extern const struct _mp_obj_fun_builtin_t mp_builtin_open_obj;
#endif // ! __ASSEMBLER__

#define MICROPY_PORT_BUILTINS \
  { MP_OBJ_NEW_QSTR(MP_QSTR_help), (mp_obj_t)&mp_builtin_help_obj },

// extra built in modules to add to the list of known ones
#define MICROPY_PY_MACHINE (1)

#ifndef __ASSEMBLER__
extern const struct _mp_obj_module_t mp_module_machine;
#endif

#define MICROPY_PORT_BUILTIN_MODULES \
  { MP_OBJ_NEW_QSTR(MP_QSTR_machine), (mp_obj_t)&mp_module_machine }, \


// We need to provide a declaration/definition of alloca()
// Our alloca is broken
#define MICROPY_NO_ALLOCA (1)

#define MICROPY_HW_BOARD_NAME "mallard-board"
#define MICROPY_HW_MCU_NAME "ducky-cpu"

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8];

#endif // ! __MIPY_DUCKY_H__
