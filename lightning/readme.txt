Para compilar no Windows 32, basta instalar:
    LibGW32C: http://gnuwin32.sourceforge.net/packages/libgw32c.htm
    mman-win32: http://code.google.com/p/mman-win32/
    � importante manter os arquivos jit_x86-cpu.c, jit_x86_sse.c, jit_x86_x87 e jit_x86.c fora da compila��o. Esses arquivos s�o compilados atrav�s do arquivo lightning.c.
    -D__WORDSIZE=32
    -DHAVE_CONFIG_H