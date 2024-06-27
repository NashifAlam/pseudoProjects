#include "header.h"
#include "cart.h"


int main()
{
	Cart user;
	Bank ;
	char choice;

	while(choice != 'E')
	{	
		menu();
		__fpurge(stdin);

		switch(choice = getchar())
		{
			case 'A': user.addtoCart(); 	break; 
			
			case 'R': 	if(user.removeFromCart())
					  		std::cout << "\nItem removal succesful\n";
				  		else
					  		std::cout << "\nItem removal Failed\n";
				  
				  stall();
				  break;

			case 'B': user.checkBill(); 	break;
			
			case 'C': 	if(checkout(user)) 
							std::cout << "Checkout Complete"<< "\nExiting";
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
