//
// Created by sohai on 8/15/2023.
//

#include "client.h"
#include "admin.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define MIN_PASS_LENGTH 6
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-sign"
extern Client *client_head;
extern Client *client_tail;
extern Admin *admin_head;
extern Admin *admin_tail;
extern Client clients_list[];

Admin *current_admin = NULL;


static void admin_view_();

void selecting(void(*func)());

void launch_system();

void view_clients();

void view_admins();

static void add_client_logic();

void add_client();

Client *delete_client_by_acc_num(u32 acc_num);

void delete_client();

void view_my_data();

void edit_my_data();

void edit_client();

static bool accNumChecker(s32 acc_num);

/// ========================================= HELPER FUNCTIONS ========================================
void choice() {
    printf("Enter your choice :");
}

void separator() {
    printf("---------------------------------------------\n");
}

void head_line(u8 *title) {
    separator();
    printf("\t||\t%s\t||\t\n", title);
    separator();
}

void admin_or_exit() {
    printf("0. Exit the program\n"
           "1. Back to admin view\n"
    );
}

bool isEmpty() {
    return client_head == NULL;
}

void invalid() {
    printf("Invalid input, try again :");
}

// DYNAMIC ALLOCATING TO NEW CLIENT OBJECT
Client *newClientObject() {
    return (Client *) malloc(sizeof(Client));
}

void scanInt(ps32 ptr) {
    while (!scanf("%d", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scanShort(ps16 ptr) {
    while (!scanf("%hi", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scanChar(pu8 ptr) {
    while (!scanf("%u", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scanDouble(pf64 ptr) {
    while (!scanf("%lf", ptr)) {
        invalid();
        fflush(stdin);
    }
}


//TAKES A POINTER TO VOID FUNCTION AND DISPLAYS 3 OPTIONS { EXIT , BACK TO ADMIN VIEW , FUNCTION THAT PASSED }
void selecting(void(*func)()) {
    u8 selector;
    separator();
    choice();
    while (true) {
        scanChar(&selector);
        if (selector == 0) return;
        else if (selector == 1)return admin_view_();
        else if (selector == 2 && func != NULL) return func();
        else invalid();
    }
}

// ========================================= HELPER FUNCTIONS ========================================

/// ==================================== VALIDATION FUNCTIONS ========================================
// JUST TO BE SURE THAT THE DATA WHICH SCANNED IS VALID TO DEAL WITH


void scan_acc_num(Client *newClient) {
    scanInt(&newClient->acc_num);
    while (newClient->acc_num <= 0) {
        printf("Account Number must be greater than zero, try another one :");
        scanInt(&newClient->acc_num);
    }
    while (!accNumChecker(newClient->acc_num)) {
        printf("This Account Number is already used try another one :");
        scanInt(&newClient->acc_num);
        while (newClient->acc_num <= 0) {
            printf("Account Number must be greater than zero, try another one :");
            scanInt(&newClient->acc_num);
        }
    }
}

void scan_pass(Client *newClient) {
    gets(newClient->pass);
    while (strlen(newClient->pass) < MIN_PASS_LENGTH) {
        separator();
        printf("Password can't be less than %d characters, try another one :", MIN_PASS_LENGTH);
        gets(newClient->pass);
    }
}

void scan_balance(Client *newClient) {
    scanDouble(&newClient->balance);
    while (newClient->balance < 0) {
        printf("Balance can't be less than zero, try another amount :");
        scanDouble(&newClient->balance);
    }
}

void scan_loan(Client *newClient) {
    scanDouble(&newClient->loan);
    while (newClient->loan < 0 || newClient->loan > MAX_LOANS) {
        if (newClient->loan < 0)
            printf("Loan can't be less than zero, try another amount :");
        else
            printf("Loan can't be more than %d, try another amount :", MAX_LOANS);
        scanDouble(&newClient->loan);
    }
}

// ==================================== VALIDATION FUNCTIONS ========================================


/// ==================================== CHECKER FUNCTIONS ==========================================
//JUST CHECKING FOR EXISTENCE OF SPECIFIC ACCOUNT NUMBER TO DO AN OPERATION ON IT'S CLIENT

//CHECKING IF THERE IS AN ACC_NUM EQUALS TO THIS ONE TO KNOW THE AVAILABILITY OF ADDING A CLIENT WITH THIS ACC_NUM
static bool accNumChecker(s32 acc_num) {
    Client *tmp = client_head;
    while (tmp != NULL) {
        if (tmp->acc_num == acc_num)
            return false;
        tmp = tmp->next;
    }
    return true;
}

//CHECKING IF ACCOUNT NUMBER EXISTS AND RETURNING POINTER TO THE PREVIOUS CLIENT TO DELETE IT
Client *delete_client_by_acc_num(u32 acc_num) {
    Client *tmp = client_head;
    while (tmp->next != NULL) {
        if (tmp->next->acc_num == acc_num)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

//CHECKING IF ACCOUNT NUMBER EXISTS AND RETURNING POINTER THIS CLIENT TO EDIT IT
Client *get_patient_by_id(s32 acc_num) {
    Client *tmp = client_head;
    while (tmp != NULL) {
        if (tmp->acc_num == acc_num)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
// ==================================== CHECKER FUNCTIONS ==========================================


/// ==================================== ADMIN VIEW ==========================================

//PASSING THE CURRENT ADMIN DATA AFTER CHECKING IT IN LAUNCH SYSTEM FUNCTION
void admin_view(Admin *tmp) {
    head_line("W E L C O M E");
    current_admin = tmp;
    return admin_view_();
}

//DISPLAYING THE OPERATIONS THAT ADMIN CAN ACCESS
static void admin_view_() {
    separator();
    printf("0. View my data\n"
           "1. Add client\n"
           "2. Delete client\n"
           "3. Edit client\n"
           "4. View clients\n"
           "5. View admins\n"
           "6. Edit my data\n"
           "7. Exit admin mode\n"
    );
    separator();
    choice();
    while (true) {
        u8 selector;
        scanChar(&selector);
        switch (selector) {
            case 0:
                return view_my_data();
            case 1:
                return add_client();
            case 2:
                return delete_client();
            case 3:
                return edit_client();
            case 4:
                return view_clients();
            case 5:
                return view_admins();
            case 6:
                return edit_my_data();
            case 7:
                return launch_system();
            default:
                invalid();
                break;
        }
    }
}
// ==================================== ADMIN VIEW ==========================================


/// ==================================== CLIENT ADDITION ==========================================

//SCANNING THE DATA FOR THE NEW CLIENT BY THE ADMIN
void add_client() {
    separator();
    Client *newClient = newClientObject();
    printf("Enter client's data :\n");
    printf("Account Number :");
    scan_acc_num(newClient);
    printf("Name :");
    getchar();
    gets(newClient->name);
    printf("Password :");
    scan_pass(newClient);
    printf("Balance :");
    scan_balance(newClient);
    printf("Loan :");
    scan_loan(newClient);
    add_client_logic(newClient);
    separator();
    printf("%s is added successfully\n", newClient->name);
    separator();
    admin_or_exit();
    printf("2. Add another client\n");
    selecting(add_client);
}

//DOING ADDITION LOGIC ON CLIENTS LIST
static void add_client_logic(Client *newClient) {
    Client *tmp = client_tail;
    client_tail = newClient;
    newClient->next = NULL;
    if (!isEmpty()) tmp->next = newClient;
    if (isEmpty()) client_head = newClient;

}
// ==================================== CLIENT ADDITION ==========================================

/// ==================================== CLIENT DELETION ==========================================

//ASKING FOR CLIENT ACC_NUM THEN CHECKING ITS EXISTENCE THEN DECIDING TO DELETE THE CLIENT OR CANCEL
void delete_client() {
    separator();
    s32 acc_num;
    printf("Enter client's account number :");
    scanInt(&acc_num);
    Client *prev = NULL;
    Client *tmp = NULL;
    if (!isEmpty()) {
        if (client_head->acc_num == acc_num) tmp = client_head;
        else prev = delete_client_by_acc_num(acc_num);
    }
    if (prev == NULL && tmp == NULL) {
        printf("Can't find such an account number, try another one\n");
        return delete_client();
    }
    separator();
    tmp == NULL ?
    printf("{ Name: %s , Password: %s , Balance: %lf , Loan: %lf }\n", prev->next->name, prev->next->pass,
           prev->next->balance, prev->next->loan) :
    printf("{ Name: %s , Password: %s , Balance: %lf , Loan: %lf }\n", tmp->name, tmp->pass, tmp->balance, tmp->loan);
    printf("\nWanna delete this client ?\n"
           "0. Delete\n"
           "1. Cancel\n"
    );
    separator();
    choice();
    u8 selector;
    scanChar(&selector);
    while (selector != 1 && selector != 0) {
        invalid();
        scanChar(&selector);
    };
    if (selector) return admin_view_();

// HANDLING 3 CASES OF DELETION { HEAD , MID , TAIL }
    if (tmp != NULL) {
        if (client_head == client_tail) {
            client_head = NULL;
            client_tail = NULL;
        } else {
            client_head = client_head->next;
        }
    } else {
        tmp = prev->next;
        if (prev->next == client_tail) {
            client_tail = prev;
            client_tail->next = NULL;
        } else {
            prev->next = prev->next->next;
        }
    }

    separator();
    printf("%s is deleted successfully\n", tmp->name);
    separator();
    free(tmp);
    admin_or_exit();
    printf("2. Delete another client\n"
    );
    selecting(delete_client);
}
// ==================================== CLIENT DELETION ==========================================


/// ==================================== CLIENT EDITION ==========================================
void edit_client() {
    separator();
    s32 acc_num;
    printf("Enter patient Account Number :");
    scanInt(&acc_num);
    Client *ptr = get_patient_by_id(acc_num);
    if (ptr == NULL) {
        printf("Can't find such an account number, try another one\n");
        return edit_client();
    }
    separator();
    printf("{ Name: %s , Password: %s , Balance: %.2lf , Loan: %.2lf }\n", ptr->name, ptr->pass, ptr->balance,
           ptr->loan);
    printf("\n0. Name\n"
           "1. Password\n"
           "2. Balance\n"
           "3. Loan\n"
    );
    u8 selector, checker = 1;
    while (checker) {
        checker = 1;
        separator();
        printf("Which attribute you wanna edit :");
        scanChar(&selector);
        switch (selector) {
            case 0:
                printf("Enter new name :");
                getchar();
                gets(ptr->name);
                break;
            case 1:
                printf("Enter new pass :");
                getchar();
                scan_pass(ptr);
                break;
            case 2:
                printf("Enter new balance :");
                scan_balance(ptr);
                break;
            case 3:
                printf("Enter new loan :");
                scan_loan(ptr);
                break;
            default:
                invalid();
                checker = 2;
                break;
        }
        if (checker == 2)
            printf("\n");
        else {
            separator();
            printf("%s is updated successfully\n", ptr->name);
            separator();
            admin_or_exit();
            printf("2. Edit another attribute\n"
                   "3. Edit another client\n"
            );
            separator();
            choice();
            bool checker2 = true;
            while (checker2) {
                u8 selector;
                scanChar(&selector);
                switch (selector) {
                    case 0:
                        return;
                    case 1:
                        return admin_view_();
                    case 2:
                        checker2 = false;
                        break;
                    case 3:
                        return edit_client();
                    default:
                        invalid();
                        break;
                }
            }
        }
    }

}
// ==================================== CLIENT EDITION ==========================================


/// ===================================== ADMIN DATA =============================================

// JUST DISPLAYING THE DATA OF CURRENT ADMIN
void view_my_data() {
    separator();
    printf("ID             : %d\n", current_admin->id);
    printf("Name           : %s\n", current_admin->name);
    printf("Password       : %s\n", current_admin->pass);
    printf("Salary         : %.2lf\n", current_admin->salary);
    separator();
    return admin_view_();
}

// JUST EDITING THE DATA OF CURRENT ADMIN BUT WITHOUT ACCESSING THE SALARY
void edit_my_data() {
    separator();
    printf("Enter your new data :\n");
    printf("Name :");
    getchar();
    gets(current_admin->name);
    printf("Password :");
    gets(current_admin->pass);
    while (strlen(current_admin->pass) < MIN_PASS_LENGTH) {
        separator();
        printf("Password can't be less than %d characters, try another one :", MIN_PASS_LENGTH);
        gets(current_admin->pass);
    }
    separator();
    printf("Your data is updated successfully\n");
    separator();
    return admin_view_();
}
// ===================================== ADMIN DATA =============================================


/// ===================================== VIEW DATA =============================================

//JUST DISPLAYING ALL CLIENTS DATA
void view_clients() {
    head_line("C L I E N T S");
    Client *tmp = client_head;
    if (isEmpty()) printf("There are no clients \n");
    while (tmp != NULL) {
        printf("Account Number : %d\n", tmp->acc_num);
        printf("Name           : %s\n", tmp->name);
        printf("Password       : %s\n", tmp->pass);
        printf("Balance        : %.2lf\n", tmp->balance);
        printf("Loan           : %.2lf\n", tmp->loan);
        separator();
        tmp = tmp->next;
    }
    return admin_view_();
}

//JUST DISPLAYING ALL ADMINS DATA WITHOUT ACCESSING THE SALARY OR PASSWORDS
void view_admins() {
    head_line("A D M I N S");
    Admin *tmp = admin_head;
    if (tmp == NULL)printf("There are no admins \n");
    while (tmp != NULL) {
        printf("ID             : %d\n", tmp->id);
        printf("Name           : %s\n", tmp->name);
        separator();
        tmp = tmp->next;
    }
    return admin_view_();
}
// ===================================== VIEW DATA =============================================


#pragma clang diagnostic pop