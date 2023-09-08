#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H


enum COLOR: uint8_t{
    BLUE = 1,
    GREEN,
    VIOLET,
    RED,
    YELLOW,
    TURQOISE,
    WHITE
};

struct CUSTOMER{
    int id;
    std::string first_name;
    std::string last_name;
    std::string zip_code;
    std::string city;
    uint8_t favorite_color;        
};

#endif // ifndef __DEFINED_CUSTOMER_H
