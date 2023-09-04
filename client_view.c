//
// Created by sohai on 8/15/2023.
//
#include "client.h"
#include "stdio.h"
#include "stdbool.h"


void separator();

void choice();

void invalid();

void head_line(u8 *title);

void scanChar(pu8 ptr);

void check_admin();

void check_user();

void scanInt(ps32 ptr);

void scanDouble(pf64 ptr);

static void client_view_();

void view_data();

void selecting_client(void(*func)());

void deposit();

void withdraw();

void pay_off_the_loan();

void take_out_a_loan();

void launch_system();

Client *current_client = NULL;

/// ========================================= HELPER FUNCTIONS ========================================

void client_or_exit() {
    printf("0. Exit the program\n"
           "1. Back to client view\n"
    );
}

void enter_amount() {
    printf("Enter the amount :");
}

//TAKES A POINTER TO VOID FUNCTION AND DISPLAYS 3 OPTIONS { EXIT , BACK TO CLIENT VIEW , FUNCTION THAT PASSED }
void selecting_client(void(*func)()) {
    u8 selector;
    separator();
    choice();
    while (true) {
        scanChar(&selector);
        if (selector == 0) return;
        else if (selector == 1)return client_view_();
        else if (selector == 2 && func != NULL) return func();
        else invalid();
    }
}
// ========================================= HELPER FUNCTIONS ========================================

/// ==================================== VALIDATION FUNCTIONS ========================================

//MAKING SURE THAT THE USER CAN'T WITHDRAW AN AMOUNT WHICH GREATER THAT ITS BALANCE
void withdraw_validation(pf64 amount) {
    while (*amount > current_client->balance) {
        printf("Your balance is not enough, try another amount :");
        scanDouble(amount);
    }
    while (*amount <= 0) {
        printf("Please enter a positive number :");
        scanDouble(amount);
        while (*amount > current_client->balance) {
            printf("Your balance is not enough, try another amount :");
            scanDouble(amount);
        }
    }
}

//MAKING SURE THAT THE USER CAN'T TAKE A LOAN WHICH GREATER THAT MAXIMUM LOAN AMOUNT (10000)
void take_a_loan_validation(pf64 amount) {
    while ((*amount + current_client->loan) > MAX_LOANS) {
        separator();
        printf("You can't take more than %d, try another amount :", MAX_LOANS);
        scanDouble(amount);
    }
    while (*amount <= 0) {
        printf("Please enter a positive number :");
        scanDouble(amount);
        while ((*amount + current_client->loan) > MAX_LOANS) {
            separator();
            printf("You can't take more than %d, try another amount :", MAX_LOANS);
            scanDouble(amount);
        }
    }
}
// ==================================== VALIDATION FUNCTIONS ========================================



/// ========================================= CLIENT VIEW =============================================

//PASSING THE CURRENT USER DATA AFTER CHECKING IT IN LAUNCH SYSTEM FUNCTION
void client_view(Client *tmp) {
//    u8 welcome[100] = "Welcome ";
//    strcat(welcome, current_client->name);
    head_line("W E L C O M E");
    current_client = tmp;
    return client_view_();
}

//DISPLAYING THE OPERATIONS THAT USER CAN ACCESS
static void client_view_() {
    separator();
    printf("0. View data\n"
           "1. Deposit\n"
           "2. Withdraw\n"
           "3. Pay off the loan\n"
           "4. Take out a loan\n"
           "5. Exit client mode\n"
    );
    separator();
    choice();
    while (true) {
        u8 selector;
        scanChar(&selector);
        switch (selector) {
            case 0:
                return view_data();
            case 1:
                return deposit();
            case 2:
                return withdraw();
            case 3:
                return pay_off_the_loan();
            case 4:
                return take_out_a_loan();
            case 5:
                return launch_system();
            default:
                invalid();
                break;
        }
    }
}
// ========================================= CLIENT VIEW ========================================


/// ====================================== CLIENT FUNCTIONS =====================================

void view_data() {
    separator();
    printf("Account Number : %d\n", current_client->acc_num);
    printf("Name           : %s\n", current_client->name);
    printf("Password       : %s\n", current_client->pass);
    printf("Balance        : %.2lf\n", current_client->balance);
    printf("Loan           : %.2lf\n", current_client->loan);
    return client_view_();
}

void deposit() {
    separator();
    enter_amount();
    f64 amount;
    scanDouble(&amount);
    while (amount <= 0) {
        printf("Please enter a positive number :");
        scanDouble(&amount);
    }
    current_client->balance += amount;
    separator();
    printf("Now your balance = %.2lf\n", current_client->balance);
    separator();
    client_or_exit();
    printf("2. Deposit again\n");
    selecting_client(deposit);
}


void withdraw() {
    separator();
    enter_amount();
    f64 amount;
    scanDouble(&amount);
    withdraw_validation(&amount);
    current_client->balance -= amount;
    separator();
    printf("Now your balance = %.2lf\n", current_client->balance);
    separator();
    client_or_exit();
    printf("2. Withdraw again\n");
    selecting_client(withdraw);
}


void pay_off_the_loan() {
    separator();
    if (current_client->loan == 0) {
        printf("You don't have any loans to pay\n");
        return client_view_();
    }
    enter_amount();
    f64 amount;
    scanDouble(&amount);
    while (amount <= 0) {
        printf("Please enter a positive number :");
        scanDouble(&amount);
    }
    if (amount > current_client->loan) {
        separator();
        printf("We have taken the loan dues and refunded the remaining amount in your account\n");
        current_client->balance += (amount - current_client->loan);
        amount = current_client->loan;
    }
    separator();
    current_client->loan -= amount;
    printf("Now your balance = %.2lf\n", current_client->balance);
    printf("Now your loan = %.2lf\n", current_client->loan);
    separator();
    client_or_exit();
    printf("2. Pay off the loan again\n");
    selecting_client(pay_off_the_loan);

}


void take_out_a_loan() {
    separator();
    if (current_client->loan == MAX_LOANS) {
        printf("You can't take more than %d\n", MAX_LOANS);
        return client_view_();
    }
    enter_amount();
    f64 amount;
    scanDouble(&amount);
    take_a_loan_validation(&amount);
    current_client->loan += amount;
    separator();
    printf("Now your loan = %.2lf\n", current_client->loan);
    client_or_exit();
    printf("2. Take out a loan again\n");
    selecting_client(take_out_a_loan);
}

// ====================================== CLIENT FUNCTIONS =====================================


