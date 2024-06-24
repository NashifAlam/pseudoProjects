#include <iostream>
#include <string.h>
class bank
{

	struct user
	{
		std::string name;
		std::string accountID;
		float balance;	
	};
	
	struct user User;
	std::string key;
	
	std::string hash();

public:

	bool addUser();
	bool editBalance();
	bool getBalance();

};
