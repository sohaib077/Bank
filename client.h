//
// Created by sohai on 8/15/2023.
//

#ifndef MAIN_C_CLIENT_H
#define MAIN_C_CLIENT_H
#include "std_type.h"
#define MAX_LOANS 10000

typedef struct Client_ {
    s32 acc_num;
    u8 name[50];
    u8 pass[50];
    f64 balance;
    f64 loan;
    struct Client_ *next;
} Client;




#endif //MAIN_C_CLIENT_H
