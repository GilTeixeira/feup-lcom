#include "i8042.h"

.global _kbd_asm_handler


.global _codeAss
.data
_codeAss: .short 0



.text
_kbd_asm_handler:

start:
	xor %eax, %eax
	in $STAT_REG,%al
	testb $OBF, %al
	jz start
	testb $IBF, %al
	jnz start
	in $OUT_BUF,%al

	movb %al, _codeAss


ret
