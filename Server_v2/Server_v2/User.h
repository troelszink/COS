#include <vector>
#include <iostream>
#include <array>
#include "bitset"

using namespace std;
class User
{
public:
	User();

	string     createUser();
	void	addUser();
	void	listUsers();


	string	getUser(int user);


	~User();
private:
	array<string, 15> users;
	int userAmount;

};

