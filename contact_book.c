#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "contacts.dat"
#define TEMP_FILE "temp.dat"

typedef struct {
    int id;
    char name[50];
    char phone[20];
    char email[60];
    char address[100];
} Contact;

/* Function declarations */
void showMenu(void);
void addContact(void);
void viewContacts(void);
void searchContact(void);
void updateContact(void);
void deleteContact(void);

void clearInputBuffer(void);
void readLine(char text[], int size);
int contactIdExists(int id);
int isValidPhone(const char phone[]);
int isValidEmail(const char email[]);
int containsIgnoreCase(const char text[], const char search[]);

int main(void) {
    int choice;

    do {
        showMenu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
            case 1:
                addContact();
                break;

            case 2:
                viewContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                updateContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                printf("\nThank you for using Contact Book.\n");
                break;

            default:
                printf("\nInvalid choice. Please select from 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}

void showMenu(void) {
    printf("\n========================================\n");
    printf("          CONTACT BOOK SYSTEM\n");
    printf("========================================\n");
    printf("1. Add Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Update Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

void addContact(void) {
    FILE *file;
    Contact contact;

    printf("\n========== ADD CONTACT ==========\n");

    printf("Enter contact ID: ");

    if (scanf("%d", &contact.id) != 1) {
        printf("Invalid ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (contact.id <= 0) {
        printf("Contact ID must be greater than zero.\n");
        return;
    }

    if (contactIdExists(contact.id)) {
        printf("A contact with ID %d already exists.\n", contact.id);
        return;
    }

    printf("Enter name: ");
    readLine(contact.name, sizeof(contact.name));

    if (strlen(contact.name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    do {
        printf("Enter phone number: ");
        readLine(contact.phone, sizeof(contact.phone));

        if (!isValidPhone(contact.phone)) {
            printf("Invalid phone number. Use only digits, +, -, spaces, or parentheses.\n");
        }

    } while (!isValidPhone(contact.phone));

    do {
        printf("Enter email: ");
        readLine(contact.email, sizeof(contact.email));

        if (!isValidEmail(contact.email)) {
            printf("Invalid email. Example: name@example.com\n");
        }

    } while (!isValidEmail(contact.email));

    printf("Enter address: ");
    readLine(contact.address, sizeof(contact.address));

    file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("Error: Unable to open contact file.\n");
        return;
    }

    if (fwrite(&contact, sizeof(Contact), 1, file) != 1) {
        printf("Error: Contact could not be saved.\n");
    } else {
        printf("\nContact added successfully.\n");
    }

    fclose(file);
}

void viewContacts(void) {
    FILE *file;
    Contact contact;
    int totalContacts = 0;

    file = fopen(FILE_NAME, "rb");

    printf("\n================ ALL CONTACTS ================\n");

    if (file == NULL) {
        printf("No contacts found.\n");
        return;
    }

    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        printf("\n----------------------------------------------\n");
        printf("ID      : %d\n", contact.id);
        printf("Name    : %s\n", contact.name);
        printf("Phone   : %s\n", contact.phone);
        printf("Email   : %s\n", contact.email);
        printf("Address : %s\n", contact.address);

        totalContacts++;
    }

    fclose(file);

    printf("\n----------------------------------------------\n");

    if (totalContacts == 0) {
        printf("No contacts found.\n");
    } else {
        printf("Total contacts: %d\n", totalContacts);
    }
}

void searchContact(void) {
    FILE *file;
    Contact contact;
    char searchText[60];
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n========== SEARCH CONTACT ==========\n");
    printf("Enter name, phone, or email: ");
    readLine(searchText, sizeof(searchText));

    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        if (containsIgnoreCase(contact.name, searchText) ||
            containsIgnoreCase(contact.phone, searchText) ||
            containsIgnoreCase(contact.email, searchText)) {

            printf("\n------------------------------------\n");
            printf("ID      : %d\n", contact.id);
            printf("Name    : %s\n", contact.name);
            printf("Phone   : %s\n", contact.phone);
            printf("Email   : %s\n", contact.email);
            printf("Address : %s\n", contact.address);

            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nNo matching contact found.\n");
    }
}

void updateContact(void) {
    FILE *file;
    Contact contact;
    int searchId;
    int found = 0;
    char newName[50];
    char newPhone[20];
    char newEmail[60];
    char newAddress[100];

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n========== UPDATE CONTACT ==========\n");
    printf("Enter contact ID to update: ");

    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        fclose(file);
        return;
    }

    clearInputBuffer();

    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        if (contact.id == searchId) {
            found = 1;

            printf("\nCurrent information:\n");
            printf("Name    : %s\n", contact.name);
            printf("Phone   : %s\n", contact.phone);
            printf("Email   : %s\n", contact.email);
            printf("Address : %s\n", contact.address);

            printf("\nEnter new name or press Enter to keep old name: ");
            readLine(newName, sizeof(newName));

            if (strlen(newName) > 0) {
                strcpy(contact.name, newName);
            }

            while (1) {
                printf("Enter new phone or press Enter to keep old phone: ");
                readLine(newPhone, sizeof(newPhone));

                if (strlen(newPhone) == 0) {
                    break;
                }

                if (isValidPhone(newPhone)) {
                    strcpy(contact.phone, newPhone);
                    break;
                }

                printf("Invalid phone number.\n");
            }

            while (1) {
                printf("Enter new email or press Enter to keep old email: ");
                readLine(newEmail, sizeof(newEmail));

                if (strlen(newEmail) == 0) {
                    break;
                }

                if (isValidEmail(newEmail)) {
                    strcpy(contact.email, newEmail);
                    break;
                }

                printf("Invalid email address.\n");
            }

            printf("Enter new address or press Enter to keep old address: ");
            readLine(newAddress, sizeof(newAddress));

            if (strlen(newAddress) > 0) {
                strcpy(contact.address, newAddress);
            }

            /*
             * Move the file pointer back by one Contact record
             * and overwrite the old contact.
             */
            fseek(file, -(long)sizeof(Contact), SEEK_CUR);

            if (fwrite(&contact, sizeof(Contact), 1, file) == 1) {
                printf("\nContact updated successfully.\n");
            } else {
                printf("\nError: Contact could not be updated.\n");
            }

            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nContact with ID %d not found.\n", searchId);
    }
}

void deleteContact(void) {
    FILE *file;
    FILE *tempFile;
    Contact contact;
    int searchId;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    tempFile = fopen(TEMP_FILE, "wb");

    if (tempFile == NULL) {
        printf("\nError: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    printf("\n========== DELETE CONTACT ==========\n");
    printf("Enter contact ID to delete: ");

    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        fclose(file);
        fclose(tempFile);
        remove(TEMP_FILE);
        return;
    }

    clearInputBuffer();

    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        if (contact.id == searchId) {
            found = 1;
        } else {
            fwrite(&contact, sizeof(Contact), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove(FILE_NAME) != 0) {
            printf("\nError: Unable to remove old contact file.\n");
            remove(TEMP_FILE);
            return;
        }

        if (rename(TEMP_FILE, FILE_NAME) != 0) {
            printf("\nError: Unable to rename temporary file.\n");
            return;
        }

        printf("\nContact deleted successfully.\n");
    } else {
        remove(TEMP_FILE);
        printf("\nContact with ID %d not found.\n", searchId);
    }
}

void clearInputBuffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* Clear remaining input */
    }
}

void readLine(char text[], int size) {
    if (fgets(text, size, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

int contactIdExists(int id) {
    FILE *file;
    Contact contact;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        return 0;
    }

    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        if (contact.id == id) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int isValidPhone(const char phone[]) {
    int digitCount = 0;
    int index;

    if (strlen(phone) == 0) {
        return 0;
    }

    for (index = 0; phone[index] != '\0'; index++) {
        if (isdigit((unsigned char)phone[index])) {
            digitCount++;
        } else if (
            phone[index] != '+' &&
            phone[index] != '-' &&
            phone[index] != ' ' &&
            phone[index] != '(' &&
            phone[index] != ')'
        ) {
            return 0;
        }
    }

    return digitCount >= 7;
}

int isValidEmail(const char email[]) {
    const char *atSymbol;
    const char *dotSymbol;

    if (strlen(email) == 0) {
        return 0;
    }

    atSymbol = strchr(email, '@');

    if (atSymbol == NULL || atSymbol == email) {
        return 0;
    }

    dotSymbol = strrchr(atSymbol, '.');

    if (dotSymbol == NULL || dotSymbol == atSymbol + 1) {
        return 0;
    }

    if (*(dotSymbol + 1) == '\0') {
        return 0;
    }

    return 1;
}

int containsIgnoreCase(const char text[], const char search[]) {
    char lowerText[150];
    char lowerSearch[150];
    int index;

    if (strlen(search) == 0) {
        return 0;
    }

    for (index = 0;
         text[index] != '\0' && index < (int)sizeof(lowerText) - 1;
         index++) {

        lowerText[index] = (char)tolower((unsigned char)text[index]);
    }

    lowerText[index] = '\0';

    for (index = 0;
         search[index] != '\0' && index < (int)sizeof(lowerSearch) - 1;
         index++) {

        lowerSearch[index] =
            (char)tolower((unsigned char)search[index]);
    }

    lowerSearch[index] = '\0';

    return strstr(lowerText, lowerSearch) != NULL;
}