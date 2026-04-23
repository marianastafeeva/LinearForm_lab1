#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/field_info.h"
#include "../include/linear_form.h"

// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ

void print_double(void* value) {
    printf("%lf\n", *(double*)value);
}

// ТЕСТ СОЗДАНИЯ

void TestCreate() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(3, field);

    assert(lf != NULL);
    assert(lf->size == 3);
    assert(lf->field == field);

    FreeLinearForm(lf);

    printf("TestCreate passed\n");
}

// ТЕСТ SET

void TestSetCoefficient() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(2, field);

    double a = 5.0;
    double b = 3.0;

    SetCoefficient(lf, 0, &a);
    SetCoefficient(lf, 1, &b);

    assert(*(double*)lf->coeffs[0] == 5.0);
    assert(*(double*)lf->coeffs[1] == 3.0);

    FreeLinearForm(lf);

    printf("TestSetCoefficient passed\n");
}

// ТЕСТ СЛОЖЕНИЯ

void TestAdd() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* a = CreateLinearForm(2, field);
    LinearForm* b = CreateLinearForm(2, field);

    double x = 2.0, y = 3.0;
    double p = 1.0, q = 4.0;

    SetCoefficient(a, 0, &x);
    SetCoefficient(a, 1, &y);

    SetCoefficient(b, 0, &p);
    SetCoefficient(b, 1, &q);

    LinearForm* result = AddLinearForm(a, b);

    assert(*(double*)result->coeffs[0] == 3.0);
    assert(*(double*)result->coeffs[1] == 7.0);

    FreeLinearForm(a);
    FreeLinearForm(b);
    FreeLinearForm(result);

    printf("TestAdd passed\n");
}

// ТЕСТ УМНОЖЕНИЯ

void TestMultiply() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(2, field);

    double a = 2.0, b = 3.0;
    double scalar = 2.0;

    SetCoefficient(lf, 0, &a);
    SetCoefficient(lf, 1, &b);

    LinearForm* result = MultiplyByScalar(lf, &scalar);

    assert(*(double*)result->coeffs[0] == 4.0);
    assert(*(double*)result->coeffs[1] == 6.0);

    FreeLinearForm(lf);
    FreeLinearForm(result);

    printf("TestMultiply passed\n");
}

//ТЕСТ ВЫЧИСЛЕНИЯ

void TestEvaluate() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(3, field);

    // F(x1, x2) = 1 + 2*x1 + 3*x2
    double a0 = 1.0, a1 = 2.0, a2 = 3.0;

    SetCoefficient(lf, 0, &a0);
    SetCoefficient(lf, 1, &a1);
    SetCoefficient(lf, 2, &a2);

    double x1 = 2.0;
    double x2 = 1.0;

    void* args[2];
    args[0] = &x1;
    args[1] = &x2;

    void* result = EvaluateLinearForm(lf, args);

    double value = *(double*)result;

    // 1 + 2*2 + 3*1 = 1 + 4 + 3 = 8
    assert(value == 8.0);

    free(result);
    FreeLinearForm(lf);

    printf("TestEvaluate passed\n");
}

// РАЗНЫЕ  РАЗМЕРЫ
void TestDifferentSizes() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* a = CreateLinearForm(2, field);
    LinearForm* b = CreateLinearForm(3, field);

    LinearForm* result = AddLinearForm(a, b);

    assert(result == NULL);

    FreeLinearForm(a);
    FreeLinearForm(b);

    printf("TestDifferentSizes passed\n");
}

// ПЕРЕЗАПИСЬ КОЭФФИЦЕНТА
void TestOverwriteCoefficient() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(1, field);

    double a = 5.0;
    double b = 10.0;

    SetCoefficient(lf, 0, &a);
    SetCoefficient(lf, 0, &b);

    assert(*(double*)lf->coeffs[0] == 10.0);

    FreeLinearForm(lf);

    printf("TestOverwriteCoefficient passed\n");
}
// РАЗНЫЕ ТИПЫ
void TestDifferentTypes() {
    FieldInfo* intField = GetIntFieldInfo();
    FieldInfo* doubleField = GetDoubleFieldInfo();

    LinearForm* a = CreateLinearForm(2, intField);
    LinearForm* b = CreateLinearForm(2, doubleField);

    LinearForm* result = AddLinearForm(a, b);

    if (result == NULL) {
        printf("TestDifferentTypes passed: cannot combine int and double\n");
    } else {
        printf("TestDifferentTypes FAILED\n");
    }

    FreeLinearForm(a);
    FreeLinearForm(b);
}
// NULL коэффициент (защита)

void TestNullCoefficient() {
    printf("Running TestNullCoefficient...\n");

    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(2, field);

    double a = 5.0;
    SetCoefficient(lf, 0, &a);

    // coeff[1] = NULL

    double x1 = 2.0;
    void* args[1];
    args[0] = &x1;

    void* result = EvaluateLinearForm(lf, args);

    if (result == NULL) {
        printf("Handled NULL correctly\n");
    } else {
        printf("Result = %lf\n", *(double*)result);
        free(result);
    }

    FreeLinearForm(lf);

    printf("TestNullCoefficient finished\n");
}

//ЗАПУСК ВСЕХ ТЕСТОВ

void RunAllTests() {
    TestCreate();
    TestSetCoefficient();
    TestAdd();
    TestMultiply();
    TestEvaluate();
    TestDifferentSizes();
    TestOverwriteCoefficient();
    TestDifferentTypes();
    TestNullCoefficient();

    printf("ALL TESTS PASSED\n");
}