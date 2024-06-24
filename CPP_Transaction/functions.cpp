#include "header.h"
#include "cart.h"
#include "bank.h"

void stall()
{
	__fpurge(stdin);
	std::cout << "\nPress enter to continue\n";
	getchar();
	return;
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
		std::cout<<"Redirecting to Merchant Site.\n";	
		sleep(1);	
		system("clear");
		return true;
	}
	return false;
}


 