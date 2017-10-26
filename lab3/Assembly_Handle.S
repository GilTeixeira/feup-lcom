#include "i8042.h"

.global _kbd_asm_handler

.text
_kbd_asm_handler:
	xor %eax, %eax


	ret
