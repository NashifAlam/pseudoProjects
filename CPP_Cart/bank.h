#include <cstdint>
#include "header.h"

class Bank 
{	
	uint32_t ID;
	std::string credentials;

	struct vendor
	{
		uint32_t accountID;
		double balance;
	}vendorInstance;
	
	struct user	
	{
		uint32_t accountID;
		double balance;
		std::string Hash;
	}userInstance;

    bool vendorTransaction(float &);
	std::string hash(const std::string&);

public:
	Bank();
	friend bool checkout(Cart&);
};