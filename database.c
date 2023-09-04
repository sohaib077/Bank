//
// Created by sohai on 8/15/2023.
//
#include  <stdlib.h>
#include "client.h"
#include "admin.h"
#include "string.h"

Client *client_head = NULL;
Client *client_tail = NULL;
Admin *admin_head = NULL;
Admin *admin_tail = NULL;

// FAKE CLIENTS AND ADMINS DATABASE TO DEAL WITH IN OUR SYSTEM

Client clients_list[] = {
        {1,  "John Doe",       "123",           1000.00, 5000.00},
        {2,  "Alice Smith",    "secret456",     5000.00, 3000.00},
        {3,  "Mike Johnson",   "mypass789",     2500.00, 0.00},
        {4,  "Emily Brown",    "password987",   1500.00, 0.00},
        {5,  "David Wilson",   "securepass321", 3000.00, 1500.00},
        {6,  "Sarah Davis",    "topsecret789",  2000.00, 2500.00},
        {7,  "Michael Miller", "mypassword123", 0.00,    0.00},
        {8,  "Olivia Taylor",  "ilovecats456",  4000.00, 2200.00},
        {9,  "Ethan Anderson", "letmein789",    1800.00, 0.00},
        {10, "Ava Martinez",   "qwerty123",     2200.00, 3500.00},
};

Admin admins_list[] = {
        {1,  "John Doe",        "pass1",  5000.00},
        {2,  "Jane Smith",      "pass2",  6000.00},
        {3,  "Michael Johnson", "pass3",  5500.00},
        {4,  "Emily Davis",     "pass4",  5200.00},
        {5,  "Daniel Wilson",   "pass5",  4800.00},
        {6,  "Sophia Brown",    "pass6",  5100.00},
        {7,  "David Miller",    "pass7",  5300.00},
        {8,  "Olivia Taylor",   "pass8",  5800.00},
        {9,  "James Anderson",  "pass9",  5400.00},
        {10, "Emma Thomas",     "pass10", 5600.00}
};



static void initialize_clients();
static void initialize_admins();

// WE CALL IT BEFORE ANY FUNCTION TO DEAL WITH THE DATA
void initialize_data() {
    initialize_clients();
    initialize_admins();
}

// INITIALIZING CLIENTS LIST
static void initialize_clients() {
    u32 size = sizeof(clients_list) / sizeof(clients_list[0]);
    for (int i = 0; i < size; ++i) {
        Client client = clients_list[i];
        Client *ptr = (Client *) malloc(sizeof(Client));
        strcpy(ptr->name, client.name);
        strcpy(ptr->pass, client.pass);
        ptr->acc_num = client.acc_num;
        ptr->balance = client.balance;
        ptr->loan = client.loan;
        if (i == 0) {
            client_head = ptr;
            client_tail = ptr;
        } else {
            Client *tmp = client_tail;
            client_tail = ptr;
            tmp->next = client_tail;
        }
        client_tail->next = NULL;
    }
}

// INITIALIZING ADMINS LIST
static void initialize_admins() {
    u32 size = sizeof(admins_list) / sizeof(admins_list[0]);
    for (int i = 0; i < size; ++i) {
        Admin admin = admins_list[i];
        Admin *ptr = (Admin *) malloc(sizeof(Admin));
        strcpy(ptr->name, admin.name);
        strcpy(ptr->pass, admin.pass);
        ptr->id = admin.id;
        ptr->salary = admin.salary;
        if (i == 0) {
            admin_head = ptr;
            admin_tail = ptr;
        } else {
            Admin *tmp = admin_tail;
            admin_tail = ptr;
            tmp->next = admin_tail;
        }
        admin_tail->next = NULL;
    }
}



