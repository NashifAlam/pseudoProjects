#include "header.h"

class Cart 
{

private:
	//struct Product;
	typedef struct Product
	{
		std::string productName;
		uint32_t productID;
		float productCost;	
		short int quantity;

	} product;
	
	std::list <Product> item;
	float totalCharges;
	int BankAccountID;
	int searchItem(std::string);

public: 

	Cart()
	{
		totalCharges = 0.0f;
		BankAccountID = 123456789;
	}
	void addtoCart();
	bool removeFromCart();
	void shippingCharges();
	void checkBill();
	
	friend bool checkout(Cart&);

};

