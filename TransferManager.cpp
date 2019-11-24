#include "TransferManager.h"

void TransferManager::recive(const char* file_to_recive)
{
	get_file_contents(file_to_recive);
	file_contents_to_package(1);
	std::sort(std::begin(vectorOfPackages), std::end(vectorOfPackages), 
		[](Package const& a, Package const& b) -> bool { return a.index < b.index; });
	std::cout << "recive message..." << std::endl;
	//for (auto v : vectorOfPackages)
	//{
	//	std::cout << v.index << v.size << "|" << v << std::endl;
	//}
	std::cout << "Message is: " << std::endl;
	for (auto v : vectorOfPackages)
		if (v.size == 2)
			std::cout << v.data1 << v.data2;
		else
			std::cout << v.data1;
	
}

void TransferManager::send(const char* file_to_send, const char* send_to)
{
	get_file_contents(file_to_send);
	file_contents_to_package(0);
	std::cout << "send message..." << std::endl;
	//for (auto v : vectorOfPackages)
	//{
	//	std::cout << v.index << v.size << "|" << v << std::endl;
	//}
	set_file_contents(send_to);
}

void TransferManager::file_contents_to_package(bool type)
{
	if (!this->vectorOfPackages.empty())
		this->vectorOfPackages.clear();
	switch (type)
	{
	case 0: //file to send
		vectorOfPackages.reserve(filecontest.size() / 2);
		for (unsigned int i = 0; (i ^ 1) < filecontest.size(); i += 2)
		{
			vectorOfPackages.emplace_back(Package(i / 2, 2, filecontest[i], filecontest[i + 1]));
		}
		if (filecontest.size() & 1)
			vectorOfPackages.emplace_back(Package(vectorOfPackages.back().index + 1, 1, filecontest.back()));
		break;
	case 1: //recived file
		vectorOfPackages.reserve(filecontest.size() / 10);
		for(unsigned int i = 0; i < filecontest.size() ;i += 10)
		{
			vectorOfPackages.emplace_back(Package(char_to_uint32(filecontest.begin() + i, filecontest.begin() + 4 + i),
				char_to_uint32(filecontest.begin() + 4 + i, filecontest.begin() + 8 + i),
				filecontest[8 + i], filecontest[9 + i]));
		}
	default:
		break;
	}
	
}

void TransferManager::get_file_contents(const char* filename)
{
	if (!this->filecontest.empty())
		this->filecontest.clear();
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		this->filecontest.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&this->filecontest[0], this->filecontest.size());
		in.close();
		return;
	}
	throw(errno);
}

void TransferManager::set_file_contents(const char* filename)
{
	std::ofstream out(filename, std::ios::out | std::ios::binary);
	if (out.is_open())
	{
		for (std::vector<Package>::reverse_iterator i = vectorOfPackages.rbegin(); i != vectorOfPackages.rend(); std::advance(i, 1))
			out << *i;
		out.close();
		return;
	}
	throw(errno);
}

uint32_t TransferManager::char_to_uint32(std::vector<char>::iterator start, std::vector<char>::iterator end)
{
	uint32_t temp = 0;
	unsigned int i = 0;
	unsigned char tmp;
	for (std::vector<char>::iterator it = start;
		it != end; i++, it++)
	{	
		tmp = static_cast<unsigned char>(*it);
		temp ^= (static_cast<uint32_t>(tmp) << (i * 8));
	}
	return temp;
}


