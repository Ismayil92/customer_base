#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <cxxopts.hpp>
#include <cstdlib>
#include <mutex>


class ArgParser{

    protected:
            ArgParser(): options_{"ArchiveParser", "Parsing arguments"}
            {
                options_.add_options()
                ("f,file-path", "Path to the data base file",
                cxxopts::value<std::string>()->default_value("../resource/data.csv"))
                ("h, help", "Print usage");   
            }
            ~ArgParser()
            {
                delete parser_;
            }

    public:
        ArgParser(ArgParser& _parser) = delete;
        void operator=(const ArgParser&) = delete;
        
        static ArgParser* GetInstance()
        {
            std::lock_guard<std::mutex> lock{mx_};
            if(parser_ == nullptr)
            {
                parser_ = new ArgParser();
            }
            return parser_;
        }
        
        void parse(int argc, char** argv)
        {
            result_ = options_.parse(argc, argv);
            file_path = result_["file-path"].as<std::string>();            
        }


        void help()
        {
            if (result_.count("help"))
            {
                std::cout << options_.help() << std::endl;
                std::exit(EXIT_SUCCESS);
            }
        }
        
        std::string getFilePath() const {return file_path;}


    private:
            cxxopts::Options options_;
            cxxopts::ParseResult result_;
            std::string file_path;       
            static inline ArgParser* parser_{nullptr};
            static std::mutex mx_; 
};


std::mutex ArgParser::mx_;


#endif