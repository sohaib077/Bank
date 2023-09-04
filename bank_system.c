//
// Created by sohai on 8/15/2023.
//
#include "client.h"
#include "admin.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-sign"

void separator();

void choice();

void invalid();

void head_line(u8 *title);

void scanChar(pu8 ptr);

void check_admin();

void check_user();

void scanInt(ps32 ptr);

void client_view(Client *tmp);

void admin_view(Admin *tmp);

extern Client *client_head;
extern Admin *admin_head;


/// ====================================== SYSTEM START =====================================

// JUST DISPLAYS THE AVAILABLE MODES ( ADMIN _OR_ CLIENT)
// THEN AUTHENTICATE THE ID OR ACCOUNT NUMBER  AND PASSWORD
// THEN NAVIGATE TO ( ADMIN VIEW _OR_ USER VIEW )

void launch_system() {
    head_line("W E L C O M E");
    printf("0. Admin Mode\n"
           "1. User Mode\n");
    separator();
    choice();
    u8 selector;
    scanChar(&selector);
    while (selector != 0 && selector != 1) {
        invalid();
        scanChar(&selector);
    }
    if (selector) return check_user();
    return check_admin();
}


void check_admin() {
    s32 id;
    u8 pass[50];
    while (true) {
        separator();
        printf("Enter your ID :");
        scanInt(&id);
        printf("Enter your Password :");
        getchar();
        gets(pass);
        Admin *tmp = admin_head;
        bool id_found = false, pass_found = false;
        while (tmp != NULL) {
            if (tmp->id == id) {
                id_found = true;
                if (strcmp(tmp->pass, pass) == 0) {
                    pass_found = true;
                    break;
                }
            }
            tmp = tmp->next;
        }
        if (!pass_found)separator();
        if (id_found && pass_found)return admin_view(tmp);
        else if (id_found) printf("Wrong password, try again\n");
        else printf("Wrong id, try again\n");
    }
};

void check_user() {
    s32 acc_num;
    u8 pass[50];

    while (true) {
        separator();
        printf("Enter your Account Number :");
        scanInt(&acc_num);
        printf("Enter your Password :");
        getchar();
        gets(pass);
        Client *tmp = client_head;
        bool acc_found = false, pass_found = false;
        while (tmp != NULL) {
            if (tmp->acc_num == acc_num) {
                acc_found = true;
                if (strcmp(tmp->pass, pass) == 0) {
                    pass_found = true;
                    break;
                }
            }
            tmp = tmp->next;
        }
        if (!pass_found)separator();
        if (acc_found && pass_found)return client_view(tmp);
        else if (acc_found) printf("Wrong password, try again\n");
        else printf("Wrong account number, try again\n");
    }

};

#pragma clang diagnostic pop