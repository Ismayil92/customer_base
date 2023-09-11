/*
NOTE:
I could also wrap C code by adding:
#ifdef __cplusplus
extern "C"{
#endif
    ...
    OLD_C_CODE
    ...
#ifdef __cplusplus
    }

I did not write so,
because instead of using MACROs for global constants, I would prefer using Enums. 
and in struct , I wanted to use enum object directly. 
#endif




*/
#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H

#ifdef __cplusplus

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
#endif // __cplusplus


#ifndef __cplusplus


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
