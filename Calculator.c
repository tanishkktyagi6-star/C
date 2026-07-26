#include <stdio.h>
#include <math.h>

void showMenu(void);
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main(void) {
    int choice;
    double firstNumber, secondNumber, result;

    do {
        showMenu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");

            while (getchar() != '\n') {
                /* Clear input buffer */
            }

            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &firstNumber, &secondNumber);

                result = add(firstNumber, secondNumber);
                printf("Result: %.2lf\n", result);
                break;

            case 2:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &firstNumber, &secondNumber);

                result = subtract(firstNumber, secondNumber);
                printf("Result: %.2lf\n", result);
                break;

            case 3:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &firstNumber, &secondNumber);

                result = multiply(firstNumber, secondNumber);
                printf("Result: %.2lf\n", result);
                break;

            case 4:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &firstNumber, &secondNumber);

                if (secondNumber == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    result = divide(firstNumber, secondNumber);
                    printf("Result: %.2lf\n", result);
                }
                break;

            case 5:
                printf("Enter base and exponent: ");
                scanf("%lf %lf", &firstNumber, &secondNumber);

                result = pow(firstNumber, secondNumber);
                printf("Result: %.2lf\n", result);
                break;

            case 6:
                printf("Enter a number: ");
                scanf("%lf", &firstNumber);

                if (firstNumber < 0) {
                    printf("Error: Square root of a negative number is invalid.\n");
                } else {
                    result = sqrt(firstNumber);
                    printf("Result: %.2lf\n", result);
                }
                break;

            case 7:
                printf("Enter a number: ");
                scanf("%lf", &firstNumber);

                result = firstNumber * firstNumber;
                printf("Square: %.2lf\n", result);
                break;

            case 8:
                printf("Enter a number: ");
                scanf("%lf", &firstNumber);

                result = firstNumber * firstNumber * firstNumber;
                printf("Cube: %.2lf\n", result);
                break;

            case 9:
                printf("\nThank you for using the calculator.\n");
                break;

            default:
                printf("\nInvalid choice. Please select from 1 to 9.\n");
        }

    } while (choice != 9);

    return 0;
}

void showMenu(void) {
    printf("\n=================================\n");
    printf("          C CALCULATOR\n");
    printf("=================================\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Power\n");
    printf("6. Square Root\n");
    printf("7. Square\n");
    printf("8. Cube\n");
    printf("9. Exit\n");
    printf("=================================\n");
}

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}