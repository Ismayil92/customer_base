#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <iterator>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <limits>
#include "kunde.hpp"



std::ostream& operator<<(std::ostream& cout, COLOR& color)
{
    return cout<<colors[static_cast<int>(color)];
}

std::istream& operator>>(std::istream& cin, COLOR& color)
{
    int i = std::numeric_limits<int>::max();
    while(i>=COLOR::COUNT)
    {
        cin>>i;
        if(i>=COLOR::COUNT)
            spdlog::error("The entered value:{} is not acceptable! Please enter again..", i);        
    }
    color = static_cast<COLOR>(i);    
    return cin; 
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


template<typename T>
void insertUserElement(const std::string notification_msg, T& input)
{
    std::cout<<notification_msg;
    std::cin>>input;
}

static CUSTOMER insertUserData(const int id_)
{
    std::cout<<"Please enter the customer information\n";

    CUSTOMER customer;

    customer.id = id_;
    insertUserElement<std::string>("Please enter the first name:", customer.first_name);
    insertUserElement<std::string>("Please enter the last name:", customer.last_name);
    insertUserElement<std::string>("Please enter the zip code:", customer.zip_code);
    insertUserElement<std::string>("Please enter the city:", customer.city);
    insertUserElement<COLOR>("Please enter the favourite color:", customer.favorite_color);
    
    return customer;    
}


int main(int argc, char** argv)
{
    KundeArchive arch{"../resource/data.csv"};

    std::cout<<"Welcome to Console Appication!"<<std::endl;
    
    std::map<int, CUSTOMER> mapping;
    char userinput;

    while(true)
    {
        std::cout<<"Add new customer [A], "
                "Fetch the customer data [F], " 
                "List all customers's data [L], "
                "Save to CSV file [S]"<<std::endl;

        //refresh container at each cycle    
        mapping  = arch.getData();
        //fetch console input
        std::cin>>userinput;
        switch (toupper(userinput))
        {
            case 'A':
            {
                auto idx = arch.generateID(mapping);
                CUSTOMER new_cust = insertUserData(idx);            
                arch.add(new_cust);
                break;
            }
            case 'F':
            {
                int request_id = fetchRequestID();  //user input       
                arch.printKundeDaten(mapping, request_id);
                break;
            }
            case 'L':
            {
                arch.printKundeDaten(mapping);
                break;
            }
            case 'S':
                arch.saveToCSV();
                break; 

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
        std::cin.clear();
        std::cout<<std::endl;     
    }
    
    return 0;
}
