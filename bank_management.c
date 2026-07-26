#include <stdio.h>
#include <string.h>

struct BankAccount {
    int accountNumber;
    char name[50];
    double balance;
};

void createAccount(struct BankAccount *account);
void depositMoney(struct BankAccount *account);
void withdrawMoney(struct BankAccount *account);
void checkBalance(struct BankAccount account);
void displayAccount(struct BankAccount account);

int main() {
    struct BankAccount account;
    int choice;
    int accountCreated = 0;

    do {
        printf("\n=================================\n");
        printf("       BANK MANAGEMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View Account Details\n");
        printf("6. Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n') {
                // Clear invalid input
            }

            continue;
        }

        switch (choice) {
            case 1:
                if (accountCreated) {
                    printf("\nAn account has already been created.\n");
                } else {
                    createAccount(&account);
                    accountCreated = 1;
                }
                break;

            case 2:
                if (accountCreated) {
                    depositMoney(&account);
                } else {
                    printf("\nPlease create an account first.\n");
                }
                break;

            case 3:
                if (accountCreated) {
                    withdrawMoney(&account);
                } else {
                    printf("\nPlease create an account first.\n");
                }
                break;

            case 4:
                if (accountCreated) {
                    checkBalance(account);
                } else {
                    printf("\nPlease create an account first.\n");
                }
                break;

            case 5:
                if (accountCreated) {
                    displayAccount(account);
                } else {
                    printf("\nPlease create an account first.\n");
                }
                break;

            case 6:
                printf("\nThank you for using the Bank Management System.\n");
                break;

            default:
                printf("\nInvalid choice. Please select from 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}

void createAccount(struct BankAccount *account) {
    printf("\n--- Create Bank Account ---\n");

    printf("Enter account number: ");
    scanf("%d", &account->accountNumber);

    getchar();

    printf("Enter account holder name: ");
    fgets(account->name, sizeof(account->name), stdin);

    account->name[strcspn(account->name, "\n")] = '\0';

    printf("Enter initial deposit amount: $");
    scanf("%lf", &account->balance);

    if (account->balance < 0) {
        printf("Initial balance cannot be negative.\n");
        account->balance = 0;
    }

    printf("\nAccount created successfully.\n");
}

void depositMoney(struct BankAccount *account) {
    double amount;

    printf("\n--- Deposit Money ---\n");
    printf("Enter amount to deposit: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Deposit amount must be greater than zero.\n");
        return;
    }

    account->balance += amount;

    printf("$%.2f deposited successfully.\n", amount);
    printf("Current balance: $%.2f\n", account->balance);
}

void withdrawMoney(struct BankAccount *account) {
    double amount;

    printf("\n--- Withdraw Money ---\n");
    printf("Enter amount to withdraw: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Withdrawal amount must be greater than zero.\n");
    } else if (amount > account->balance) {
        printf("Insufficient balance.\n");
    } else {
        account->balance -= amount;

        printf("$%.2f withdrawn successfully.\n", amount);
        printf("Remaining balance: $%.2f\n", account->balance);
    }
}

void checkBalance(struct BankAccount account) {
    printf("\n--- Account Balance ---\n");
    printf("Available balance: $%.2f\n", account.balance);
}

void displayAccount(struct BankAccount account) {
    printf("\n--- Account Details ---\n");
    printf("Account number : %d\n", account.accountNumber);
    printf("Account holder : %s\n", account.name);
    printf("Balance        : $%.2f\n", account.balance);
}