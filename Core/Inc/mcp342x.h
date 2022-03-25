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
#define MCP342X_SIZE_MASK				0x0C

// Gain Definitions
#define MCP342X_GAIN_1X					0x00
#define MCP342X_GAIN_2X					0x01
#define MCP342X_GAIN_4X					0x02
#define MCP342X_GAIN_8X					0x03
#define MCP342X_GAIN_MASK				0x03

#define MCP342X_RDY						0x80
#define MCP342X_RESET					0x06

class MCP342X_I2C_OPRTS {
  public:
	 uint8_t _IIC_ADDR;
	 I2C_HandleTypeDef *i2c;

	 void i2c_init(I2C_HandleTypeDef *hi2c){
		i2c = hi2c;
	}
    void set_i2c_addr(uint8_t address){
    	_IIC_ADDR = address;
    }

    uint8_t I2C_read_bytes(uint8_t* data, uint16_t data_len);
    uint8_t I2C_write_bytes(uint8_t* data, uint16_t data_len);
};

class MCP342X: public MCP342X_I2C_OPRTS {
public:
	MCP342X();
	MCP342X(uint8_t I2C_ADDR=MCP342X_DEFAULT_ADDRESS);
	~MCP342X();

	bool isConnected(void);
	void reset(void);

	void configure(uint8_t config);
	uint8_t getConfig(void);

	// conversion
	uint8_t startConversion(void);
	uint8_t startConversion(uint8_t channel);

	//read the adc result
	uint8_t getResult(int16_t *data);
	uint8_t getResult(int32_t *data);

	uint8_t checkforResult(int16_t *data);
	uint8_t checkforResult(int32_t *data);

private:
	uint8_t configReg;
	uint8_t channel;
};

#endif /* INC_MCP342X_H_ */
