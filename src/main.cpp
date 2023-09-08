#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "kunde.hpp"

static std::mutex mutex;
static std::condition_variable cv;

 

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
    std::unique_lock<std::mutex> lc{mutex};
    std::cout<<notification_msg;
    std::cin>>input;
    lc.unlock();
}

static CUSTOMER insertUserData()
{
    static int id = 1;
    std::cout<<"Please enter the customer information\n";

    CUSTOMER customer;

    customer.id = id;

    insertUserElement<std::string>("Please enter the first name:", customer.first_name);
    insertUserElement<std::string>("Please enter the last name:", customer.last_name);
    insertUserElement<std::string>("Please enter the zip code:", customer.zip_code);
    insertUserElement<std::string>("Please enter the city:", customer.city);
    insertUserElement<uint8_t>("Please enter the favourite color:", customer.favorite_color);
    
    id++;
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
        
        mapping  = arch.getData();
        std::cin>>userinput;
        switch (toupper(userinput))
        {
            case 'A':
            {
                CUSTOMER new_cust = insertUserData();            
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
