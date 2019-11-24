#include "TransferManager.h"

int main()
{
	TransferManager test;
	test.send("text1.txt", "text2.txt");
	test.recive("text2.txt");
	return 0;
}