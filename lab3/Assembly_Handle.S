#include "i8042.h"

.global _kbd_asm_handler

.text
_kbd_asm_handler:

start:
	xor %eax, %eax
	in $STAT_REG,%al
	testb $OBF, %al
	jz start
	testb $IBF, %al
	jz start
	in $OUT_BUF,%al

ret
