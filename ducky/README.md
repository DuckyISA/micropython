# The Ducky port

## Building for a Ducky implementation

    $ CFLAGS='-fno-builtin -nostdinc -mllvm -disable-tail-duplicate' DUCKY=<path-to-ducky-virtualenv> make V=1 DEBUG=1 CC=<path-to-clang> firmware
