#include "TransferManager.h"

void TransferManager::recive(const char* file_to_recive)
{
	get_file_contents(file_to_recive);
	file_contents_to_package(1);

	std::sort(std::begin(vectorOfPtr), std::end(vectorOfPtr),
		[](Package* const& a, Package* const& b) -> bool { return a->index < b->index; });

	char* ptr;
	std::cout << "recive message..." << std::endl;
	for (auto v : vectorOfPtr)
	{
		std::cout << v->index << " " << v->size << " | ";
		ptr = reinterpret_cast<char*>(v) + sizeof(Package);
		for (int i = 0; i < v->size; i++)
		{
			std::cout << ptr[0];
			ptr++;
		}
		std::cout << std::endl;
	}
}

void TransferManager::send(const char* file_to_send, const char* send_to, const unsigned int MAX_SIZE)
{
	get_file_contents(file_to_send);
	file_contents_to_package(0, MAX_SIZE);
	std::cout << "send message..." << std::endl;
	for (auto i = 0, j = 0; i < this->vectorOfPackages.size(); i++)
	{
		std::cout << this->vectorOfPackages[i].index << " " << this->vectorOfPackages[i].size << " | " ;
		for (auto k = j; k < this->vectorOfPackages[i].size + j; k++)
			std::cout << filecontest[k];
		std::cout << std::endl;
		j += this->vectorOfPackages[i].size;
	}
	set_file_contents(send_to, MAX_SIZE);
}

void TransferManager::set_file_contents(const char* filename, const unsigned int MAX_SIZE)
{
	std::ofstream out(filename, std::ios::out | std::ios::binary);
	if (out.is_open())
	{
		for (int i = filecontest.size(); i >= 0; i -= MAX_SIZE)
		{
			if (i / MAX_SIZE >= vectorOfPackages.size())
				continue;
			out << vectorOfPackages[ i / MAX_SIZE ];
			for (auto j = 0; j < vectorOfPackages[i / MAX_SIZE].size; j++)
			{
				out << filecontest[j + (vectorOfPackages[i / MAX_SIZE].index * MAX_SIZE)];
			}
		}
		out.close();
	}
}

void TransferManager::file_contents_to_package(bool type, const unsigned int MAX_SIZE)
{
	if (!this->vectorOfPackages.empty())
		this->vectorOfPackages.clear();
	switch (type)
	{
	case 0: //file to send
		vectorOfPackages.reserve(filecontest.size() / MAX_SIZE);
		for (unsigned int i = 0; (i + MAX_SIZE - 1) < filecontest.size(); i += MAX_SIZE)
		{
			vectorOfPackages.emplace_back(Package(i / MAX_SIZE, MAX_SIZE));
		}
		if (filecontest.size() % MAX_SIZE != 0)
			vectorOfPackages.emplace_back(Package(vectorOfPackages.back().index + 1, filecontest.size() % MAX_SIZE));
		break;
	case 1: //file to recive
		Package * ptr;
		vectorOfPtr.reserve(filecontest.size() / (8 + MAX_SIZE));
		ptr = reinterpret_cast<Package*>(std::data(filecontest));
		for (int i = 0, j = 0; i < filecontest.size(); j++)
		{
			if(j)
				ptr = reinterpret_cast<Package*>(reinterpret_cast<char*>(ptr) + sizeof(Package) + ptr->size);
			vectorOfPtr.push_back(ptr);
			i += sizeof(Package) + vectorOfPtr[j]->size;
		}
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
}

/*uint32_t TransferManager::char_to_uint32(std::vector<char>::iterator start, std::vector<char>::iterator end)
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
}*/
