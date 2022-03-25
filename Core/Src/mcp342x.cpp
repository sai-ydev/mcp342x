/*
 * mcp342x.cpp
 *
 *  Created on: Mar 23, 2022
 *      Author: yaman
 */
#include "mcp342x.h"

/*
 * Default constructor
 *
 */
MCP342X::MCP342X() {
	set_i2c_addr((MCP342X_DEFAULT_ADDRESS << 1));
}

/*
 * Constructor with address
 *
 */
MCP342X::MCP342X(uint8_t I2C_ADDR) {
	set_i2c_addr((I2C_ADDR << 1));
}

/*
 *
 * General Call Reset
 *
 */
void MCP342X::reset() {
	uint8_t reset_data = MCP342X_RESET;
	HAL_I2C_Master_Receive(i2c, 0x00, &reset_data, 1, HAL_MAX_DELAY);
}

/*
 * Returns whether MCP342X is connected
 *
 */
bool MCP342X::isConnected() {
	return (HAL_I2C_IsDeviceReady(i2c, _IIC_ADDR, 2, 2) == HAL_OK);
}

void MCP342X::configure(uint8_t config) {
	configReg = config;
}

uint8_t MCP342X::getConfig(void) {
	return configReg;
}

uint8_t MCP342X::startConversion(void) {

	uint8_t config_data = (configReg | MCP342X_RDY);

	return I2C_write_bytes(&config_data, 1);
}

uint8_t MCP342X::startConversion(uint8_t channel) {

	uint8_t config_data = ((configReg & ~MCP342X_CHANNEL_MASK)
			| (channel & MCP342X_CHANNEL_MASK));
	config_data |= MCP342X_RDY;

	return I2C_write_bytes(&config_data, 1);
}

uint8_t MCP342X::getResult(int16_t *data) {
	uint8_t adcStatus;
	uint8_t adc_data[3];

	if ((configReg & MCP342X_SIZE_MASK) == MCP342X_SIZE_18BIT) {
		return 0xFF;
	}

	do {
		I2C_read_bytes(adc_data, 3);
		((uint8_t*) data)[1] = adc_data[0];
		((uint8_t*) data)[0] = adc_data[1];
		adcStatus = adc_data[2];

	} while ((adcStatus & MCP342X_RDY) != 0x00);

	return adcStatus;
}

uint8_t MCP342X::getResult(int32_t *data) {

	uint8_t adcStatus;
	uint8_t adc_data[4];

	if ((configReg & MCP342X_SIZE_MASK) != MCP342X_SIZE_18BIT) {
		return 0xFF;
	}

	do {
		I2C_read_bytes(adc_data, 4);
		((uint8_t*) data)[3] = adc_data[0];
		((uint8_t*) data)[2] = adc_data[1];
		((uint8_t*) data)[1] = adc_data[2];
		adcStatus = adc_data[3];

	} while ((adcStatus & MCP342X_RDY) != 0x00);

	*data = (*data) >> 8;

	return adcStatus;

}

uint8_t MCP342X::checkforResult(int16_t *data) {

	uint8_t adcStatus;
	uint8_t adc_data[3];

	if((configReg & MCP342X_SIZE_MASK) == MCP342X_SIZE_18BIT){
		return 0xFF;
	}

	if(I2C_read_bytes(adc_data, 3) == HAL_OK){
		((uint8_t*)data)[1] = adc_data[0];
		((uint8_t*)data)[0] = adc_data[1];
		adcStatus = adc_data[2];
	} else{
		return 0xFF;
	}


	return adcStatus;
}

uint8_t MCP342X::checkforResult(int32_t *data){
	uint8_t adcStatus;
	uint8_t adc_data[4];

	if((configReg & MCP342X_SIZE_MASK) != MCP342X_SIZE_18BIT){
		return 0xFF;
	}

	if(I2C_read_bytes(adc_data, 4) == HAL_OK){
		((uint8_t*)data)[3] = adc_data[0];
		((uint8_t*)data)[2] = adc_data[1];
		((uint8_t*)data)[1] = adc_data[2];
		adcStatus = adc_data[3];
	} else{
		return 0xFF;
	}

	*data = (*data) >> 8;

	return adcStatus;
}

uint8_t MCP342X_I2C_OPRTS::I2C_read_bytes(uint8_t *data, uint16_t data_len) {

	uint8_t rslt = HAL_ERROR;

	rslt = HAL_I2C_Master_Receive(i2c, _IIC_ADDR, data, data_len,
	HAL_MAX_DELAY);

	return rslt;

}

uint8_t MCP342X_I2C_OPRTS::I2C_write_bytes(uint8_t *data, uint16_t data_len) {
	uint8_t rslt = HAL_ERROR;

	rslt = HAL_I2C_Master_Transmit(i2c, _IIC_ADDR, data, data_len,
	HAL_MAX_DELAY);

	return rslt;
}

