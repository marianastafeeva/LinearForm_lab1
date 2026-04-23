#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "field_info.h"

void menu() {
    printf("\n=== MENU ===\n");
    printf("1. Run ALL tests\n");
    printf("2. Run ONE test\n");
    printf("3. Add\n");
    printf("4. Subtract\n");
    printf("5. Multiply\n");
    printf("0. Exit\n");
}

FieldInfo* chooseField() {
    int type;
    printf("Choose type: 1 - int, 2 - double: ");
    scanf("%d", &type);

    if (type == 1) return GetIntFieldInfo();
    return GetDoubleFieldInfo();
}

void* inputValue(FieldInfo* field) {
    void* value = malloc(field->size);

    if (field->size == sizeof(int)) {
        scanf("%d", (int*)value);
    } else {
        scanf("%lf", (double*)value);
    }

    return value;
}

void printValue(FieldInfo* field, void* value) {
    if (field->size == sizeof(int)) {
        printf("%d\n", *(int*)value);
    } else {
        printf("%lf\n", *(double*)value);
    }
}

void runOperation(int op) {
    FieldInfo* field = chooseField();

    printf("Enter first number: ");
    void* a = inputValue(field);

    printf("Enter second number: ");
    void* b = inputValue(field);

    void* result = NULL;

    if (op == 1) result = field->add(a, b);
    if (op == 2) result = field->sub(a, b);
    if (op == 3) result = field->mul(a, b);

    printf("Result = ");
    printValue(field, result);

    free(a);
    free(b);
    field->free(result);
}

// запуск одного теста
void runSingleTest(int t) {
    printf("Running test %d...\n", t);

    switch (t) {
        case 1: TestCreate(); break;
        case 2: TestSetCoefficient(); break;
        case 3: TestAdd(); break;
        case 4: TestMultiply(); break;
        case 5: TestEvaluate(); break;
        case 6: TestDifferentSizes(); break;
        case 7: TestOverwriteCoefficient(); break;
        case 8: TestDifferentTypes(); break;
        case 9: TestNullCoefficient(); break;
        default: printf("No such test\n");
    }
}

int main() {
    int choice;

    while (1) {
        menu();
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                RunAllTests();
                break;

            case 2: {
                int t;
                printf("Enter test number (1-9): ");
                scanf("%d", &t);
                runSingleTest(t);
                break;
            }

            case 3:
                runOperation(1);
                break;

            case 4:
                runOperation(2);
                break;

            case 5:
                runOperation(3);
                break;

            case 0:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}