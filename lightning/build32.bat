gcc -Iinc -D__WORDSIZE=32 -DHAVE_CONFIG_H=1 src/jit_disasm.c src/jit_memory.c src/jit_note.c src/jit_print.c src/lightning.c src/mman.c src/main.c -lgw32c -o lightning.exe
pause