Para compilar no Windows 32, basta instalar:
    LibGW32C: http://gnuwin32.sourceforge.net/packages/libgw32c.htm
    mman-win32: http://code.google.com/p/mman-win32/
    É importante manter os arquivos jit_x86-cpu.c, jit_x86_sse.c, jit_x86_x87 e jit_x86.c fora da compilação. Esses arquivos são compilados através do arquivo lightning.c.
    -D__WORDSIZE=32
    -DHAVE_CONFIG_H