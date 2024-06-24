#include <iostream>
#include <list>
#include <cstdint>
#include <stdio_ext.h>
#include <stdlib.h>

void stall()
{
	__fpurge(stdin);
	std::cout << "\n\nPress enter to continue\n";
	getchar();
	return;
}

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
	bool checkout();
	void checkBill();
	//bool vendorTransaction(float);

};



class Bank 
{	
	uint32_t ID;
	std::string credentials;

	struct vendor
	{
		uint32_t accountID;
		double balance;
		/*
		vendor(uint32_t  ID, double b= 100000)
		{
			accountID = ID;
			balance = b;
		}*/

	}vendorInstance;

	struct user
	{
		uint32_t accountID;
		double balance;
		std::string Hash;/*
		user(uint32_t &ID, std::string &H, double b= 100000)
		{
			accountID = ID;
			Hash = H;
			balance = b;
		}*/
	}userInstance;

	std::string hash(const std::string& st)
	{
		return st;
	}


public:
	Bank()
	{
		//vendorInstance(123456789);
		
		uint32_t ID;
		std::string credentials;
		std::cout << "\nEnter your Bank Account Number : "; 
		std::cin >> ID;
		std::cout << "\nEnter your password : ";
		std::cin >> credentials;
		//user userInstance(ID, credentials);
		userInstance.accountID = ID;
		userInstance.Hash = hash(credentials);
		userInstance.balance = 100000;

		vendorInstance.accountID = 123456789;
		vendorInstance.balance = 1000000;
	}

	bool vendorTransaction(float &transactionAmount)
	{
		if(userInstance.balance < transactionAmount){
			std::cout << "\nNot enough balance.\n";
			return false;}
		else{
			userInstance.balance -= transactionAmount;
			vendorInstance.balance += (double)transactionAmount;	
			std::cout << "\n\nUser Balance is : "<< userInstance.balance 
				<< "\nVendor Balance is : "<<vendorInstance.balance<<std::endl;
			std::cout << "\nTransaction Complete\nRedirecting to Merchant site\n";
			return true;
		}
	}

};

void Cart::shippingCharges()
{
	for(const product &temp : item)
		totalCharges += (temp.productCost * temp.quantity);
}


void Cart::checkBill()
{
	system( "clear" );
	std::cout<< "Total Bill\n"
		<< "----------\n";
	
	if(item.empty()){
		std::cout << "Cart is empty\nPlease use Add to Cart for adding items";
		stall();
		return;}

	for(const product &temp : item)
		std::cout<<"Item Name : "
			<<temp.productName<<"\tID : "
			<<temp.productID<<"\tPrice : "
			<< temp.productCost<< "\tQuantity : "
			<<temp.quantity<<std::endl;

	std::cout<<"\nTotal Price is : "
		<< totalCharges
		<< std::endl
		<< std::endl;
	
	stall();	
}

void Cart::addtoCart()
{		
	product temp;
	system("clear");
	std::cout<< "Cart Entry Sheet\n"
		<<"----------------\n";

	std::cout<< "\nEnter the item name  : "; 
	while(!(std::cin >> temp.productName))
	{
		std::cin.clear(); std::cin.ignore(10,'\n'); 
		std::cout<<"Invalid input\nTry Again\nEnter the item ID    : ";
	}
	std::cout<< "Enter the item ID    : "; 
	while(!(std::cin >> temp.productID))
	{
		std::cin.clear(); std::cin.ignore(10,'\n'); 
		std::cout<<"Invalid input\nTry Again\nEnter the item ID    : ";
	}
	std::cout<< "Enter the item price : "; 
	while(!(std::cin >> temp.productCost))
	{
		std::cin.clear(); std::cin.ignore(10,'\n'); 
		std::cout<<"Invalid Cost\nTry Again\nEnter the item cost  : ";
	}
	
	std::cout<< "Enter the quantity   : "; 
	while(!(std::cin >> temp.quantity))
	{
		std::cin.clear(); std::cin.ignore(3,'\n'); 
		std::cout<<"Maximum quantity exceeding\nTry Again\nEnter the quantity   : ";
	}
	

	item.push_back(temp);
	shippingCharges();
}

bool Cart::removeFromCart()
{
	uint32_t inputID;
	
	system("clear");
	
	std::cout<< "Cart Item deletion Sheet\n"
		<<"-------------------\n"
		<< "\nAdded items: ";
	
	if(item.empty()){
		std::cout << "Nil\n\nCart is empty\nPlease use Add to Cart for adding items";
		return false;}
	
	for(const product &temp : item)
		std::cout<<"\nItem Name : " << temp.productName
			<< "\tID : " << temp.productID
			<< "\tPrice : "<< temp.productCost
			<< "\tQuantity : "<< temp.quantity 
			<< std::endl;

	std::cout<< "\nEnter the ID of the product to delete : ";
	std::cin>> inputID;

	item.remove_if([&inputID](const product& temp){return inputID == temp.productID;});

	shippingCharges();
	stall();
	return true;
}

bool Cart::checkout()
{
	system("clear");
	std::cout << "This is checkout section\n";	
	
	if(item.empty()){
		std::cout << "Cart is empty\nPlease use Add to Cart for adding items";
		stall();
		return false;}

	if(totalCharges < 1){
		std::cout << "Total bill is zero\nCannot proceed to checkout";
		stall();
		return false;}
	
	Bank Vendor;

	if(Vendor.vendorTransaction(totalCharges))
		return true;
	
	return false;
}

void menu()
{
	system("clear");
	std::cout<< "Please select your preferences " 
		<< "\nA: Add item to cart"
		<<"\nR: Remove item from cart"
		<<"\nB: View the total Bill"
		<<"\nC: Checkout\nE: Exit\n"
		<< "Enter your selection : "; 
}

int main()
{
	Cart user;
	char choice;

	while(choice != 'E')
	{	
		menu();
		__fpurge(stdin);

		switch(choice = getchar())
		{
			case 'A': user.addtoCart(); 	break; 
			
			case 'R': if(user.removeFromCart())
					  std::cout << "\nItem removal succesful\n";
				  else
					  std::cout << "\nItem removal Failed\n";
				  stall();
				  break;

			case 'B': user.checkBill(); 	break;
			
			case 'C': if(user.checkout()) 
					  std::cout << "Transaction Complete !!"
						  << "\nExiting";
				  else
					  break;
				  stall();
				  system("clear");
				  exit(0); 	
			
			case 'E': std::cout<<"Exiting\n\n"; exit(0);

			default: std::cout << "Wrong selection\nPlease try again\n"  ; break;
		}
	}

	return 0;
}
