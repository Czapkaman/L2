#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

struct Package
{
	Package(uint32_t index, uint32_t size);

	uint32_t index = 0;
	uint32_t size = 0;

	friend std::ostream& operator<<(std::ostream& os, Package& obj);
};
