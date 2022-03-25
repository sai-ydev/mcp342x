# MCP342X drivers for STM32 microcontrollers

Drivers for interfacing the [MCP342x](http://ww1.microchip.com/downloads/en/devicedoc/22088c.pdf) family of ADCs. I wrote this driver based on [this Arduino driver.](https://github.com/uChip/MCP342X)

I wrote this driver using an MCP3422 and an [STM32L4 Discovery Kit](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)

## License

The original driver comes with a BSD-3 License. I have included the license file in this repo. While I don't care how you use my driver, please respect the original author's licensing requirement.

## Usage

The driver consists of two files namely:

1. mcp342x.h
2. mcp342x.cpp

The file main.cpp contains an example of how to use the drivers. If you find a problem, feel free to submit an issue.
