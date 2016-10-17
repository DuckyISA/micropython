//#include <arch/ducky.h>
#include "mpconfigport.h"


.macro FUNC name
  .type \name , @function
  .size \name , . - \name
.endm

.macro PUBFUNC name
  FUNC \name
  .globl \name
.endm


/*
 * Boot entry point
 */

  .section .text.boot, "x", @progbits

_entry:
  // setup a stack
  la sp, _stack_start

  // reset FP to mark end of chain of frames
  li fp, 0x00

  // we're prepared, call C code
  call _start

  // it does not return, signal such condition by weird exit code
  hlt 0x1f

  //FUNC _entry


/*
 * Low-level CPU control
 */

  .text

__do_idle:
  idle
  ret

  //PUBFUNC __do_idle

__do_cli:
  cli
  ret

  //PUBFUNC __do_cli


  .global __do_sti
__do_sti:
  sti
  ret

  //PUBFUNC __do_sti


  .global __do_halt
__do_halt:
  hlt r0
  ret

  //PUBFUNC __do_halt


/*
 * Interrupt stuff
 */

  .section .bss

jiffies:
  .int 0x00000000

//  .global __esp_rtc
//__esp_rtc:
//  .space PAGE_SIZE

//  .global __esp_kbd
//__esp_kbd:
//  .space PAGE_SIZE

  .text

__esr_rtc:
  push r0
  push r1
  la r0, jiffies
  lw r1, r0
  inc r1
  stw r0, r1
  pop r1
  pop r0
  retint

  //PUBFUNC __esr_rtc


__esr_kbd:
  retint

  //PUBFUNC __esr_kbd
