#include <stdio.h>
#include <stdlib.h>
#include "linear_form.h"
#include "field_info.h"
#include "tests.h"

LinearForm* currentForm = NULL;
FieldInfo* currentField = NULL;

void inputValue(FieldInfo* f, void* dst) {
    if (f->element_size == sizeof(int)) scanf("%d", (int*)dst);
    else if (f->element_size == sizeof(double)) scanf("%lf", (double*)dst);
}

void printValue(FieldInfo* f, const void* v) {
    if (f->element_size == sizeof(int)) printf("%d", *(const int*)v);
    else if (f->element_size == sizeof(double)) printf("%lf", *(const double*)v);
}

void createLinearForm() {
    if (currentForm) { lf_destroy(currentForm); currentForm = NULL; }
    int n;
    printf("\n--- Create New Linear Form ---\n");
    printf("Enter size (number of coefficients, including a0): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid size.\n"); while(getchar() != '\n'); return;
    }
    currentForm = lf_create(n, currentField);
    if (!currentForm) { printf("Error: Memory allocation failed.\n"); return; }

    printf("Enter %d coefficients manually:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  a[%d] = ", i);
        void* ptr = lf_get_coeff_ptr(currentForm, i);
        inputValue(currentField, ptr);
    }
    printf("Form created.\n");
}

void showLinearForm() {
    if (!currentForm) { printf("No form created.\n"); return; }
    printf("\n--- Current Form ---\nF(x) = ");
    for (int i = 0; i < currentForm->size; i++) {
        if (i > 0) printf(" + ");
        printValue(currentField, lf_get_coeff_ptr(currentForm, i));
        if (i > 0) printf("*x%d", i);
    }
    printf("\n");
}

void addForms() {
    if (!currentForm) { printf("Create form first.\n"); return; }
    int n = currentForm->size;
    printf("\n--- Add Another Form ---\n");
    printf("Enter %d coefficients for the SECOND form:\n", n);

    LinearForm* b = lf_create(n, currentField);
    if (!b) return;
    for (int i = 0; i < n; i++) {
        printf("  b[%d] = ", i);
        inputValue(currentField, lf_get_coeff_ptr(b, i));
    }

    LinearForm* result = lf_create(n, currentField);
    if (!result) { lf_destroy(b); return; }

    lf_add(currentForm, b, result);

    printf("\nResult Coefficients: [ ");
    for (int i = 0; i < n; i++) {
        printValue(currentField, lf_get_coeff_ptr(result, i));
        printf(" ");
    }
    printf("]\n");

    lf_destroy(b); lf_destroy(result);
}

void multiplyByScalar() {
    if (!currentForm) { printf("Create form first.\n"); return; }
    printf("\n--- Multiply by Scalar ---\n");
    printf("Enter scalar value: ");

    // Allocate memory for scalar based on type
    void* scalar = malloc(currentField->element_size);
    if (!scalar) return;
    inputValue(currentField, scalar);

    LinearForm* result = lf_create(currentForm->size, currentField);
    if (!result) { free(scalar); return; }

    lf_mul_scalar(currentForm, scalar, result);

    printf("Result Coefficients: [ ");
    for (int i = 0; i < currentForm->size; i++) {
        printValue(currentField, lf_get_coeff_ptr(result, i));
        printf(" ");
    }
    printf("]\n");

    lf_destroy(result);
    free(scalar);
}

void evalForm() {
    if (!currentForm) { printf("No form created.\n"); return; }
    if (currentForm->size < 2) {
        printf("Constant form. Value = ");
        printValue(currentField, lf_get_coeff_ptr(currentForm, 0));
        printf("\n");
        return;
    }

    int numVars = currentForm->size - 1;
    const void** args = malloc(numVars * sizeof(const void*));
    double* temps = malloc(numVars * sizeof(double));
    if (!args || !temps) { free(args); free(temps); return; }

    printf("\n--- Evaluate Form ---\n");
    printf("Enter %d arguments (x1..x%d):\n", numVars, numVars);
    for (int i = 0; i < numVars; i++) {
        printf("  x%d = ", i + 1);
        if (currentField->element_size == sizeof(int)) {
            int tmp; scanf("%d", &tmp); temps[i] = (double)tmp;
        } else {
            scanf("%lf", &temps[i]);
        }
        args[i] = &temps[i];
    }

    double resultVal;
    lf_eval(currentForm, args, &resultVal);
    printf("Result F(x) = %lf\n", resultVal);

    free(args); free(temps);
}

void printMenu() {
    printf("\n=================================\n");
    printf("   LINEAR FORM MANAGER           \n");
    printf("=================================\n");
    printf("1. Create new linear form\n");
    printf("2. Show current form\n");
    printf("3. Add another form\n");
    printf("4. Multiply by scalar\n");
    printf("5. Evaluate form\n");
    printf("6. Run automated tests (7 tests)\n");
    printf("0. Exit\n");
    printf("---------------------------------\n");
    printf("Choice: ");
}

int main() {
    int type;
    printf("=== Polymorphic Linear Form ===\n");
    printf("Select type:\n1. Integer (int)\n2. Real (double)\nChoice: ");
    if (scanf("%d", &type) != 1) return 1;

    currentField = (type == 1) ? GetIntFieldInfo() : GetDoubleFieldInfo();
    printf("Selected: %s\n", (type == 1 ? "int" : "double"));

    int choice;
    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }

        switch (choice) {
            case 1: createLinearForm(); break;
            case 2: showLinearForm(); break;
            case 3: addForms(); break;
            case 4: multiplyByScalar(); break;
            case 5: evalForm(); break;
            case 6: RunAllTests(); break;
            case 0: if (currentForm) lf_destroy(currentForm); printf("Bye!\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
