#include "Package.h"

Package::Package(uint32_t index, uint32_t size, uint8_t data1, uint8_t data2)
{
	this->index = index;
	this->size = size;
	this->data1 = data1;
	this->data2 = data2;
}

bool operator<( Package const& a, Package const&  b)
{
	return a.index < b.index;
}

std::ostream& operator<<(std::ostream& os, Package& obj)
{
	os.write((char*)& obj.index, sizeof(obj.index));
	os.write((char*)& obj.size, sizeof(obj.size));
	os << obj.data1 << obj.data2;
	return os;
}
