#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define ESC 			0x81
#define FIRST_BYTE		0xE0
#define BIT(n) (0x01<<(n))
#define OUT_BUF 0x60
#define IN_BUF 0x64
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64

#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)
#define AUX BIT(5)
#define OBF BIT(0)
#define IBF BIT(1)





#define ENABLE_KBD_INT BIT(0)

#define READ_COMM_BYTE 0x20
#define WRITE_COMM_BYTE 0x60

#define DELAY_US    20000






#define KBD_IRQ	        1    /**< @brief KBD IRQ line */




#endif
