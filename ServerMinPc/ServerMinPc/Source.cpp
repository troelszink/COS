#include <iostream>
#include <fstream>
#include <string>
#include "ArchiveServer.h"
#include <bitset>
//#include "User.h"

using namespace std;

void checkIfNumbe(string h)
{
	int length = 0;
	int nameLength;

		while ((int)h[length] != 10)
		{
			length++;
		}
		nameLength = length - 5;
		cout << h.substr(length - nameLength, nameLength);
	
}

int main()
{

	ArchiveServer fa;

	cout << "" << endl;
	fa.constructFile("Hello World", "Hello World", 0, 0, "Hej med dig\ndin so\n������");
	fa.constructFile("Hello World Copy", "Hello World Copy", 0, 0, "Hej med dig\ndin so\n������ nummer 2");
	fa.read("Hello World");
	fa.read("Hello World Copy");
	fa.listFiles();
	fa.removeFile("Hello World");
	fa.listFiles();

	checkIfNumbe("01 1 hej med dig\n");

	//User d;
	//d.addUser();
	//d.addUser();
	//d.addUser();
	//d.addUser();
	//d.listUsers();
	getchar();
	return 0;
}