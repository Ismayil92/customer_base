#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "kunde.hpp"


static int calculateCustomerID()
{
    int id;

    return id;
}


static int fetchRequestID()
{
    std::cout<<"Please enter ID value:";

    int id;
    std::string input;
    //input
    std::cin>>input;
    auto it = std::find_if(input.begin(), input.end(), [](const char& ch){
        return isdigit(ch);
    });

    if(input.empty() || it == input.end())
    {
        std::cerr<<"Input is not correct! Try again please!\n";
        return -1;
    }
    
    id = std::stoi(input);
    return id;
}
static CUSTOMER inputUserData(int id)
{

    std::cout<<"Please enter the customer information\n";
    CUSTOMER customer;
    
    customer.id = id;
    std::cout<<"Please enter the first name:";
    std::cin>>customer.first_name;
    std::cout<<"Please enter the last name:";
    std::cin>>customer.last_name;
    std::cout<<"Please enter the zip code:"; 
    std::cin>>customer.zip_code;
    std::cout<<"Please enter the city:";
    std::cin>>customer.city;
    std::cout<<"Please enter the favorite color:";
    std::cin>>customer.favorite_color;

    return customer;    
}

int main()
{
    KundeArchive arch{"../resource/data.csv"};
    std::cout<<"Welcome to Console Appication!"<<std::endl;
    
    std::map<int, CUSTOMER> mapping;
    char userinput;
    int id=0;

    while(true)
    {
        std::cout<<"Add new customer [A], "
                "Fetch the customer data [F], " 
                "List all customers's data [L]"<<std::endl;
        
        mapping  = arch.getData();
        std::cin>>userinput;
        switch (userinput)
        {
            case 'A':
            {
                id++;
                CUSTOMER new_cust = inputUserData(id);            
                arch.add(new_cust);
                break;
            }
            case 'F':
            {
                int request_id = fetchRequestID();          
                arch.printKundeDaten(mapping, request_id);
                break;
            }
            case 'L':
            {
                arch.printKundeDaten(mapping);
                break;
            }
            case 27:
            {
                std::cout<<"Exit was requested\n";
                return EXIT_SUCCESS;
            }
            default:
            {
                continue;
            }
        }   
        std::cout<<std::endl;     
    }
    
    return 0;
}
