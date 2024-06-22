#include <iostream>
#include <list>
#include <cstdint>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
class Bank;

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
	void checkBill();
	
	friend bool checkout(Cart&);

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
	
	bool vendorTransaction(float &transactionAmount)
	{
		if(userInstance.balance < transactionAmount){
			std::cout << "\nNot enough balance.\n";
			stall();
			return false;}
		else{
			std::cout << "Bill amount of Rupees : "<<transactionAmount;
			userInstance.balance -= transactionAmount;
			vendorInstance.balance += (double)transactionAmount;	
			std::cout << "\n\nUser Balance is : "<< userInstance.balance 
				<< "\nVendor Balance is : "<<vendorInstance.balance<<std::endl;
			std::cout << "\nTransaction Complete\n";
			transactionAmount = 0;
			return true;
		}
	}

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
		std::cout<<"Welcome to bank login"
			<<"\n---------------------";

		uint32_t ID;
		std::string credentials;
		std::cout << "\nEnter your Bank Account Number : "; 
		while(!(std::cin >> ID))
		{
			std::cin.clear(); std::cin.ignore(10,'\n'); 
			std::cout<<"Invalid input\nTry Again\nEnter your Bank Account Number    : ";
		}

		std::cout << "\nEnter your password : ";
		std::cin >> credentials;
		//dduser userInstance(ID, credentials);
		userInstance.accountID = ID;
		userInstance.Hash = hash(credentials);
		userInstance.balance = 100000;

		vendorInstance.accountID = 123456789;
		vendorInstance.balance = 1000000;
	}

	friend bool checkout(Cart&);


};

void Cart::shippingCharges()
{
	totalCharges = 0;

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
	/*std::cout<< "Enter the item ID    : "; 
	while(!(std::cin >> temp.productID))
	{
		std::cin.clear(); std::cin.ignore(10,'\n'); 
		std::cout<<"Invalid input\nTry Again\nEnter the item ID    : ";
	}*/
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
	
	temp.productID = rand()% 10000 + 9999;
	
	item.push_back(temp);
	shippingCharges();
}

bool Cart::removeFromCart()
{
	uint32_t inputID;
	
	system("clear");
	short int size = item.size();	
	std::cout<< "Cart Item deletion Sheet\n"
		<<"-------------------\n"
		<< "\nAdded items: ";
	
	if(item.empty()){
		std::cout << "Nil\n\nCart is empty\nPlease use Add to Cart for adding items";
		return false;}
	
	for(const product &temp : item)
		std::cout<<"\nID : " << temp.productID
			<< "\tItem Name : " << temp.productName
			<< "\tPrice : "<< temp.productCost
			<< "\tQuantity : "<< temp.quantity ;

	std::cout<< "\n\nEnter the ID of the product to delete : ";
	std::cin>> inputID;

	item.remove_if([&inputID](const product& temp){return inputID == temp.productID;});
	//TODO: If the item not found then 
	if(item.size() == size)
	{
		std::cout << "\nItem not found\n";
		return false;
	}
	shippingCharges();
	return true;
}

bool checkout(Cart &cart)
{
	system("clear");
	Bank bank;
	system("clear");
	std::cout << "This is checkout section\n"
		<<"------------------------\n\n";	
	
	if(cart.item.empty()){
		std::cout << "Cart is empty\nPlease use Add to Cart for adding items";
		stall();
		return false;}

	if(cart.totalCharges < 1){
		std::cout << "Total bill is zero\nCannot proceed to checkout";
		stall();
		return false;}

	if(bank.vendorTransaction(cart.totalCharges))
	{
		stall();
		system("clear");
		std::cout<<"Redirecting to Merchant Site.";	
		sleep(1);	
		system("clear");
		return true;
	}
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
			
			case 'C': if(checkout(user)) 
					std::cout << "\n\nCheckout Complete"
						  << "\nExiting";
				  else
					  break;
				  sleep(2);
				  system("clear");
				  exit(0); 	
			
			case 'E': std::cout<<"Exiting\n\n"; exit(0);

			default: std::cout << "Wrong selection\nPlease try again\n"  ; break;
		}
	}

	return 0;
}
