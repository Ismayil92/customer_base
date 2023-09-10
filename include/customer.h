#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H

static std::string colors[] = {"BLUE",
                            "GREEN",
                            "VIOLET",
                            "RED",
                            "YELLOW",
                            "TURQOISE",
                            "WHITE"};

enum COLOR{
    BLUE = 0,
    GREEN,
    VIOLET,
    RED,
    YELLOW,
    TURQOISE,
    WHITE,
    COUNT
};

struct CUSTOMER{
    int id;
    std::string first_name;
    std::string last_name;
    std::string zip_code;
    std::string city;
    COLOR favorite_color;        
};

#endif // ifndef __DEFINED_CUSTOMER_H
