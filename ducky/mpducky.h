#ifndef __MPDUCKY_H__
#define __MPDUCKY_H__

extern void __do_idle(void);
extern void __do_cli(void);
extern void __do_sti(void);
extern void __do_halt(int exit_code) __attribute__((noreturn));

#define idle() __do_idle()
#define cli() __do_cli()
#define sti() __do_sti()
#define halt(_exit_code) __do_halt(_exit_code)

#endif // __MPDUCKY_H__
