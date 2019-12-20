#include "Package.h"

Package::Package(uint32_t index, uint32_t size)
{
	this->index = index;
	this->size = size;
}

bool operator<( Package const& a, Package const&  b)
{
	return a.index < b.index;
}

std::ostream& operator<<(std::ostream& os, Package& obj)
{
	os.write((char*)& obj.index, sizeof(obj.index));
	os.write((char*)& obj.size, sizeof(obj.size));
	return os;
}
