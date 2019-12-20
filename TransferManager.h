#pragma once

#include "Package.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <vector>

class TransferManager
{
public:
	void recive(const char*  file_to_recive);
	void send(const char* file_to_send, const char* send_to, const unsigned int MAX_SIZE);

private:
	void file_contents_to_package(bool type, const unsigned int MAX_SIZE = 0);
	void get_file_contents(const char* filename);
	void set_file_contents(const char* filename, const unsigned int MAX_SIZE = 0);
	//uint32_t char_to_uint32(std::vector<char>::iterator start, std::vector<char>::iterator end);

	std::vector<char> filecontest;
	std::vector<Package> vectorOfPackages;
	std::vector<Package*> vectorOfPtr;
};

