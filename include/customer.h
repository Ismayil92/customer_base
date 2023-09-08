#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H


#ifdef _cplusplus

    enum COLOR{
        BLUE = 1,
        GREEN,
        VIOLET,
        RED,
        YELLOW,
        TURQOISE,
        WHITE
    }

    struct CUSTOMER{
        int id;
        std::string first_name;
        std::string last_name;
        std::string zip_code;
        std::string city;
        COLOR favorite_color;
        
    }
    
#else

    #define	COLOR_BLUE      1
    #define COLOR_GREEN     2
    #define COLOR_VIOLET    3
    #define COLOR_RED       4
    #define COLOR_YELLOW    5
    #define COLOR_TURQUOISE 6
    #define COLOR_WHITE     7

    struct _CUSTOMER {
        int id;
        char first_name[24];
        char last_name[32];
        char zip_code[8];
        char city[32];
        int favorite_color;
    };

    typedef struct _CUSTOMER CUSTOMER;

#endif


#endif // ifndef __DEFINED_CUSTOMER_H
