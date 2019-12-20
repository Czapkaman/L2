#include "TransferManager.h"
#include "Package.h"

/*
W paczce powinny znajdować się tylko index oraz size.
Dane powinny być dodawane za paczką.
Wielkość powinna być ustalana przez użytkownika.
*/

int main()
{
	TransferManager test;
	test.send("text1.txt", "text2.txt", 11);
	test.recive("text2.txt");

	std::cout << "\nSizeof Package: " << sizeof(Package) << std::endl;
	return 0;
}