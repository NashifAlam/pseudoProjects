#include "bank.h"

bool Bank::vendorTransaction(float &transactionAmount)
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

std::string Bank::hash(const std::string& st)
{
    return st;
}


Bank::Bank()
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
    fetchDetails(ID, credentials);

    userInstance.accountID = ID;
    userInstance.Hash = hash(credentials);
    userInstance.balance = 100000;

    vendorInstance.accountID = 123456789;
    vendorInstance.balance = 1000000;
}

bool Bank::fetchDetails(uint32_t ID, const std::string &credential)
{
    //TODO Open the encrypted file
    //search for the current ID
    //compare the hash
    // if the hash maches then populate the structure
    return true; 
}
