# TinyELF

This is a binary file you can use to make really small Linux/ELF executables
for x86-64:

    $ ./helloworld              # a tinyelf
    hello world
    $ ./helloworld-c            # compiled with gcc
    hello world
    $ wc -c helloworld-c helloworld
    1733 helloworld-c
     329 helloworld
    2062 total
    $

The machine code for `helloworld` and `helloworld-c` is identical; each was
compiled from `helloworld.c`.

## Using TinyELF

    $ gcc helloworld.c -nostdlib -o helloworld-c
    $ objcopy -O binary -j .text helloworld-c helloworld-bin
    $ cat tinyelf helloworld-bin > helloworld
    $ chmod +x helloworld

You then have a tiny executable that you can run normally:

    $ ./helloworld
    hello world!
    $

See `helloworld.c` for some important caveats and things you need to do in
order for this to work. In particular, some of the obvious limitations are that
you can't use `libc` or have any global data, including string literals.
