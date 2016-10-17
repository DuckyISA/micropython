#include <stdint.h>
//#include <stdio.h>
#include <string.h>

#include "py/nlr.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/stackctrl.h"
#include "lib/utils/pyexec.h"

//#include <arch/ducky.h>
//#include <arch/rtc.h>
#include <stdlib.h>
#include "mpducky.h"

#include <cpu/exceptions.h>

void do_str(const char *src, mp_parse_input_kind_t input_kind) {
    mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
    if (lex == NULL) {
        printf("MemoryError: lexer could not allocate memory\n");
        return;
    }

    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, MP_EMIT_OPT_NONE, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // uncaught exception
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

// Necessary to workaround LLVM's bug - materialization of immediates
// in case immediate fits into encoding but results in a negative value.
extern char _heap;
static char *_heap_start = &_heap;

extern char _stack_start;

int main(int argc, char **argv)
{
#if MICROPY_ENABLE_GC
    gc_init(_heap_start, _heap_start + DUCKY_HEAP_SIZE);
#endif

    mp_init();

    // Enable interrupts - I guess it's safe now.
    //sti();

    #if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }
    #else
    pyexec_friendly_repl();
    #endif
    halt(0x51);
    //do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    //do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    mp_deinit();
    return 0;
}

#if MICROPY_ENABLE_GC
void gc_collect(void) {
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    gc_collect_start();
    //gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end();
    gc_dump_info();
}
#endif

mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    return NULL;
}

mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_obj_t mp_builtin_open(uint n_args, const mp_obj_t *args, mp_map_t *kwargs) {
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

void nlr_jump_fail(void *val) {
}


/**
 * IRQ and reset handling
 */

extern void __esr_rtc(void);
extern void __esr_kbd(void);

//extern u8_t __esp_rtc, __esp_kbd;

#define UNHANDLED_EVT_ENTRY() EVT_ENTRY(NULL, NULL)

evt_entry_t evt[] __attribute__((section(".evt"))) = {
//  EVT_ENTRY(__esr_rtc, &__esp_rtc), // RTC
//  EVT_ENTRY(__esr_kbd, &__esp_kbd), // Keyboard
  UNHANDLED_EVT_ENTRY(),            // Storage
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY(),
  UNHANDLED_EVT_ENTRY()
};

static void init_rtc(void)
{
  // Setup RTC frequency
  //*(u8_t *)(RTC_MMIO_ADDRESS + RTC_MMIO_FREQ) = 1;
}

void _start(void)
{
  // called by _entry, with stack initialized

  mp_stack_set_top(&_stack_start);
  mp_stack_set_limit(DUCKY_STACK_SIZE);

  // initialize CPU and peripherals
  //init_rtc();

  // now that we have a basic system up and running we can call main
  main(0, NULL);

  for (;;)
    ;
}
