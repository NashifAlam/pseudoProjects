#include "header.h"
#include "cart.h"


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

