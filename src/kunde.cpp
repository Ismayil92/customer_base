#include "kunde.hpp"
#include "spdlog/fmt/ostr.h"


KundeArchive::KundeArchive()
{

}


KundeArchive::KundeArchive(std::string csv_file_path): storage_path{csv_file_path}
{   
   
    file_stream.open(csv_file_path, std::ios::app | std::ios::out | std::ios::in);
    if(!file_stream.is_open())
    {
        spdlog::error("CSV file not found!");
        std::exit(EXIT_FAILURE);
    }

    if(!this->isCSVEmpty())
    {
        this->loadFromCSV();
        spdlog::info("CSV file successfully loaded..");
    }
    else{
        spdlog::warn("CSV file is empty. You may add new customers!");
    }
    
}

KundeArchive::~KundeArchive()
{
    file_stream.close();
}


void KundeArchive::add(CUSTOMER& new_customer_)
{
    auto cst_it = customer_dict.find(new_customer_.id);
    if(cst_it != customer_dict.end())
    {
        spdlog::error("The customer with ID {} already exists!",
                    cst_it->first);
        return;
    }
        
    customer_dict[new_customer_.id] = new_customer_;
}

void KundeArchive::saveToCSV()
{
    if(customer_dict.empty())
    {
        spdlog::warn("Customer Archive is empty!");
        return;
    }
    for (const auto& [id, customer] : customer_dict)
    {
        file_stream<<customer.id<<", "
        <<customer.first_name<<", "
        <<customer.last_name<<", "
        <<customer.zip_code<<", "
        <<customer.city<<", "
        <<customer.favorite_color<<"\n";
    }   
    if(file_stream.fail())
    {
        spdlog::info("Data successfully saved..");
    }
}


void KundeArchive::loadFromCSV()
{
    std::string row;
    std::string word;
    std::vector<std::string> columns;
    while(!file_stream.eof())
    {
        columns.clear();        
        
        std::getline(file_stream, row, '\n');
        std::stringstream s{row};
        while(std::getline(s, word, ','))
        {
            columns.push_back(word);
        }
        CUSTOMER customer{
                            .id = std::stoi(columns[0]),
                            .first_name = columns[1],
                            .last_name = columns[2],
                            .zip_code = columns[3],
                            .city = columns[4],
                            .favorite_color = static_cast<COLOR>(std::stoi(columns[5]))};

        customer_dict[stoi(columns[0])] = customer;        
    }
}


void KundeArchive::setFilePath(std::string csv_file_path)
{
    storage_path = csv_file_path;
}


int KundeArchive::generateID(std::map<int, CUSTOMER>& container)  
{
    if(customer_dict.empty()){
        return 1;
    }
    auto idx = std::prev(customer_dict.end())->first;
    return idx+1;
}  

void KundePrinter::printKundeDaten(const std::map<int, CUSTOMER>& customer_dict,
                                const int _ID)
{

    auto cst_it = customer_dict.find(_ID);
    if(cst_it == customer_dict.end())
    {
        spdlog::warn("The matching person with the given ID value: {} not found",
                _ID);
        return;
    }

    CUSTOMER cst {cst_it->second};

    spdlog::info("{},{},{},{},{}", cst.first_name,
                                    cst.last_name,
                                    cst.zip_code,
                                    cst.city,
                                    colors[cst.favorite_color]);           
}


void KundePrinter::printKundeDaten(const std::map<int, CUSTOMER>& customer_dict)
                            
{
   for (const auto& [id, customer] : customer_dict)
   {
        spdlog::info("{},{},{},{},{},{}", 
                            customer.id,
                            customer.first_name,
                            customer.last_name,
                            customer.zip_code,
                            customer.city,
                            colors[customer.favorite_color]);
   }  
}



