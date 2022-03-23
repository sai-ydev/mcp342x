/*
 * mcp342x.h
 *
 * This driver is based on this library:
 * https://github.com/uChip/MCP342X/blob/master/MCP342X.h
 *
 *  Created on: Mar 22, 2022
 *      Author: yaman
 */

#ifndef INC_MCP342X_H_
#define INC_MCP342X_H_

#include "stm32l4xx_hal.h"
//
#define MCP342X_DEFAULT_ADDRESS 		0x69

//this was defined using table 55 of MCP342x datasheet
#define MCP342X_A0						0x68
#define MCP342X_A1						0x69
#define MCP342X_A2						0x6A
#define MCP342X_A3						0x6B
#define MCP342X_A4						0x6C
#define MCP342X_A5						0x6D
#define MCP342X_A6						0x6E
#define MCP342X_A7						0x6F

// COnversion modes
#define MCP342X_MODE_ONESHOT			0x00
#define MCP3342X_MODE_CONTINUOUS 		0x10

// Channel selection
#define MCP342X_CHANNEL_1				0x00
#define MCP342X_CHANNEL_2				0x20
#define MCP342X_CHANNEL_3				0x40
#define MCP342X_CHANNEL_4				0x60
#define MCP342X_CHANNEL_MASK			0x60

// ADC Resolution
#define MCP342X_SIZE_12BIT				0x00
#define MCP342X_SIZE_14BIT				0x04
#define MCP342X_SIZE_16BIT				0x08
#define MCP342X_SIZE_18BIT				0x0C

// Gain Definitions
#define MCP342X_GAIN_1X					0x00
#define MCP342X_GAIN_2X					0x01
#define MCP342X_GAIN_4X					0x02
#define MCP342X_GAIN_8X					0x03

#define MXP342X_RDY						0x80

class MCP9600_IIC_OPRTS {
  public:

	void IIC_begin(I2C_HandleTypeDef *hi2c){
		i2c = hi2c;
	}
    void set_iic_addr(u8 IIC_ADDR);
    HAL IIC_read_bytes(u8 start_reg, u8* data, u32 data_len);
  private:
    I2C_HandleTypeDef *i2c;
    uint8_t _IIC_ADDR;

};

#endif /* INC_MCP342X_H_ */
