//
// Created by sohai on 8/16/2023.
//

#ifndef MAIN_C_ADMIN_H
#define MAIN_C_ADMIN_H


#include "std_type.h"

typedef struct Admin_ {
    s32 id;
    u8 name[50];
    u8 pass[50];
    f64 salary;
    struct Admin_ *next;
} Admin;


#endif //MAIN_C_ADMIN_H
