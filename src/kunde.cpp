#include "kunde.hpp"

KundeArchive::KundeArchive()
{

}


KundeArchive::KundeArchive(std::string csv_file_path): storage_path{csv_file_path}
{   
    if(!file.is_open())
        file.open(csv_file_path, std::ios::app | std::ios::out | std::ios::in);
}

KundeArchive::~KundeArchive()
{
    file.close();
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
        file<<customer.id<<", "
        <<customer.first_name<<", "
        <<customer.last_name<<", "
        <<customer.zip_code<<", "
        <<customer.city<<", "
        <<customer.favorite_color<<"\n";
    }   
}


void KundeArchive::setFilePath(std::string csv_file_path)
{
    storage_path = csv_file_path;
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
                                        cst.favorite_color);           
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
                            customer.favorite_color);
   }  
}
