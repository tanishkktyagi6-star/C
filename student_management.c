#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int rollNumber;
    char name[50];
    float marks;
} Student;

void clearInputBuffer(void);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

int main(void) {
    int choice;

    while (1) {
        printf("\n=================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the program.\n");
                return 0;

            default:
                printf("\nInvalid choice. Please select 1 to 6.\n");
        }
    }
}

void clearInputBuffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        // Clear remaining input
    }
}

void addStudent(void) {
    FILE *file;
    Student student;
    Student existingStudent;

    printf("\nEnter roll number: ");

    if (scanf("%d", &student.rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file != NULL) {
        while (fread(&existingStudent, sizeof(Student), 1, file) == 1) {
            if (existingStudent.rollNumber == student.rollNumber) {
                printf("A student with this roll number already exists.\n");
                fclose(file);
                return;
            }
        }

        fclose(file);
    }

    printf("Enter student name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter marks: ");

    if (scanf("%f", &student.marks) != 1) {
        printf("Invalid marks.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }

    if (fwrite(&student, sizeof(Student), 1, file) != 1) {
        printf("Error while saving student data.\n");
    } else {
        printf("\nStudent added successfully.\n");
    }

    fclose(file);
}

void displayStudents(void) {
    FILE *file;
    Student student;
    int count = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n%-12s %-25s %-10s\n", "Roll Number", "Name", "Marks");
    printf("--------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        printf("%-12d %-25s %-10.2f\n",
               student.rollNumber,
               student.name,
               student.marks);

        count++;
    }

    if (count == 0) {
        printf("No student records found.\n");
    }

    fclose(file);
}

void searchStudent(void) {
    FILE *file;
    Student student;
    int rollNumber;
    int found = 0;

    printf("\nEnter roll number to search: ");

    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("\nStudent found:\n");
            printf("Roll Number: %d\n", student.rollNumber);
            printf("Name: %s\n", student.name);
            printf("Marks: %.2f\n", student.marks);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent not found.\n");
    }

    fclose(file);
}

void updateStudent(void) {
    FILE *file;
    Student student;
    int rollNumber;
    int found = 0;

    printf("\nEnter roll number to update: ");

    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("Enter new student name: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0';

            printf("Enter new marks: ");

            if (scanf("%f", &student.marks) != 1) {
                printf("Invalid marks.\n");
                clearInputBuffer();
                fclose(file);
                return;
            }

            clearInputBuffer();

            fseek(file, -(long)sizeof(Student), SEEK_CUR);

            if (fwrite(&student, sizeof(Student), 1, file) != 1) {
                printf("Error while updating student data.\n");
            } else {
                printf("\nStudent updated successfully.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent not found.\n");
    }

    fclose(file);
}

void deleteStudent(void) {
    FILE *file;
    FILE *temporaryFile;
    Student student;
    int rollNumber;
    int found = 0;

    printf("\nEnter roll number to delete: ");

    if (scanf("%d", &rollNumber) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    temporaryFile = fopen("temporary.dat", "wb");

    if (temporaryFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNumber == rollNumber) {
            found = 1;
        } else {
            fwrite(&student, sizeof(Student), 1, temporaryFile);
        }
    }

    fclose(file);
    fclose(temporaryFile);

    if (found) {
        remove(FILE_NAME);

        if (rename("temporary.dat", FILE_NAME) != 0) {
            printf("Error while updating the student file.\n");
            return;
        }

        printf("\nStudent deleted successfully.\n");
    } else {
        remove("temporary.dat");
        printf("\nStudent not found.\n");
    }
}