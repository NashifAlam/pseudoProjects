#include <fstream>
#include <list>
#include <cstdint>
#include <iostream>

using namespace std;

//#include "authentication.h"

typedef struct
{
	uint32_t accountID;
	string hash;
	double balance;
} customers;

class bank
{
	list <customers> user;

public: 
	bool populateDatabase();
	
};

bool bank::populateDatabase()
{

	customers temp;
	/*fstream file("database.dat", ios::in | ios::out );
	for(int i =0; i < 100; ++i)
	{
		temp.accountID = rand() % 1000000 + 9999;
		temp.hash = "password";
		temp.balance = 1'000'000;

		user.push_back(temp);
	}	
	for( const auto& it : user )
	{
		file.write((char *)&it, sizeof(user));
	}
	*/
	ifstream file("database.dat", ios::in);
	if (!file) {
    		cerr << "Error in opening the file" << endl;
    		return false; // if this is main
	}
	
	//while(feof(file))
	//{
	//	file.read((char *)&temp, sizeof(user));
//user.push_back(temp);
	//}
	
	while(file >> temp.accountID >> temp.hash >> temp.balance)
	{
		user.push_back(temp);
	}	

	for(const auto& it : user )
		cout << temp.accountID << "\t" << temp.hash<<endl;
		
	file.close();
	return true;
}

int main()
{
	bank SBI;
	SBI.populateDatabase();	

}

