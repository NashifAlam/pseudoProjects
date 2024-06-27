#include <cstdint>
#include "header.h"

class Bank 
{	
	uint32_t ID;
	std::string credentials;

	typedef struct
	{
		uint32_t accountID;
		std::string Hash;
	}customer;

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

	std::list <customer> customerList;
	bool populateCustomer();
	
    bool vendorTransaction(float &);
	bool fetchDetails(uint32_t,const std::string&);
	std::string hash(const std::string&);

public:
	Bank();
	friend bool checkout(Cart&);
}; 