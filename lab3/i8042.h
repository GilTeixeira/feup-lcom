#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define ESC 			0x81
#define FIRST_BYTE		0xE0

#define OUT_BUF 0x60
#define IN_BUF 0x64
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64


#define OBF 0x01
#define IBF 0x02




#define KBD_IRQ	        1    /**< @brief KBD IRQ line */




#endif
