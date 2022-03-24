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
MCP342X::MCP342X(){
	set_i2c_addr((MCP342X_DEFAULT_ADDRESS << 1));
}

/*
 * Constructor with address
 *
 */
MCP342X::MCP342X(uint8_t I2C_ADDR){
	set_i2c_addr((I2C_ADDR<<1));
}

/*
 * Returns whether MCP342X is connected
 *
 */
bool MCP342X::isConnected(){
	return (HAL_I2C_IsDeviceReady(i2c, _IIC_ADDR, 2, 2) == HAL_OK);
}

void MCP342X::configure(uint8_t config){
	configReg = config;
}

uint8_t MCP342X::getConfig(void){
	return configReg;
}

HAL_StatusTypeDef MCP342X::startConversion(void){


}


HAL_StatusTypeDef MCP342X_I2C_OPRTS::I2C_read_bytes(uint8_t start_reg, uint8_t* data, uint32_t data_len){

}

HAL_StatusTypeDef MCP342X_I2C_OPRTS::I2C_write_bytes(uint8_t start_reg, uint8_t* data, uint32_t data_len){

}





