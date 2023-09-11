#ifndef KUNDE_HPP
#define KUNDE_HPP

#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include "customer.h"
#include "spdlog/spdlog.h"



class KundePrinter{
    public:
        void printKundeDaten(const std::map<int, CUSTOMER>& customer_dict,
                            const int _id);
        void printKundeDaten(const std::map<int, CUSTOMER>& customer_dict);

};


class KundeArchive: public KundePrinter{

    protected:
       std::map<int, CUSTOMER> customer_dict;
       std::string storage_path;
       std::fstream file_stream;
       

    public:
        KundeArchive(std::string csv_file_path);
        ~KundeArchive();
        KundeArchive(const KundeArchive& _arch) = delete;
        KundeArchive& operator=(const KundeArchive& _arch) = delete;      

        void add(CUSTOMER& _new_customer);
        void loadFromCSV();
        void saveToCSV();
        CUSTOMER getCredentials(const int _ID)  {return  customer_dict[_ID]; }
        std::map<int, CUSTOMER>& getData()  {return customer_dict;}
        std::string getFilePath() const {return storage_path;}  
        bool isCSVEmpty(){ return file_stream.peek() == std::ifstream::traits_type::eof();}
        int  generateID(std::map<int, CUSTOMER>& container); 
};






#endif
