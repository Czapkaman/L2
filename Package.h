#pragma once

#include <iostream>
#include <cstdint>

struct Package
{
	Package(uint32_t index, uint32_t size, uint8_t data1, uint8_t data2 = 0);

	uint32_t index = 0;
	uint32_t size = 0;
	uint8_t data1 = 0;
	uint8_t data2 = 0;

	friend std::ostream& operator<<(std::ostream& os, Package& obj);
};
