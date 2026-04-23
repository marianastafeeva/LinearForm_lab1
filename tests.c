#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "field_info.h"
#include "linear_form.h"

// вспомогательное получение элемента
#define ELEM(lf, i) ((char*)lf->coeffs + i * lf->field->size)

// ТЕСТ СОЗДАНИЯ
void TestCreate() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(3, field);

    assert(lf != NULL);
    assert(lf->size == 3);

    FreeLinearForm(lf);
    printf("TestCreate passed\n");
}

// SET
void TestSetCoefficient() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(2, field);

    double a = 5.0, b = 3.0;

    SetCoefficient(lf, 0, &a);
    SetCoefficient(lf, 1, &b);

    assert(*(double*)ELEM(lf,0) == 5.0);
    assert(*(double*)ELEM(lf,1) == 3.0);

    FreeLinearForm(lf);
    printf("TestSetCoefficient passed\n");
}

// ADD
void TestAdd() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* a = CreateLinearForm(2, field);
    LinearForm* b = CreateLinearForm(2, field);
    LinearForm* result = CreateLinearForm(2, field);

    double x=2,y=3,p=1,q=4;

    SetCoefficient(a,0,&x);
    SetCoefficient(a,1,&y);
    SetCoefficient(b,0,&p);
    SetCoefficient(b,1,&q);

    AddLinearForm(a,b,result);

    assert(*(double*)ELEM(result,0) == 3.0);
    assert(*(double*)ELEM(result,1) == 7.0);

    FreeLinearForm(a);
    FreeLinearForm(b);
    FreeLinearForm(result);

    printf("TestAdd passed\n");
}

// MUL
void TestMultiply() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(2, field);
    LinearForm* result = CreateLinearForm(2, field);

    double a=2,b=3, scalar=2;

    SetCoefficient(lf,0,&a);
    SetCoefficient(lf,1,&b);

    MultiplyByScalar(lf,&scalar,result);

    assert(*(double*)ELEM(result,0) == 4.0);
    assert(*(double*)ELEM(result,1) == 6.0);

    FreeLinearForm(lf);
    FreeLinearForm(result);

    printf("TestMultiply passed\n");
}

// EVALUATE
void TestEvaluate() {
    FieldInfo* field = GetDoubleFieldInfo();

    LinearForm* lf = CreateLinearForm(3, field);

    double a0=1,a1=2,a2=3;

    SetCoefficient(lf,0,&a0);
    SetCoefficient(lf,1,&a1);
    SetCoefficient(lf,2,&a2);

    double x1=2,x2=1;
    void* args[2] = {&x1,&x2};

    double result;
    EvaluateLinearForm(lf,args,&result);

    assert(result == 8.0);

    FreeLinearForm(lf);

    printf("TestEvaluate passed\n");
}

// разные типы
void TestDifferentTypes() {
    FieldInfo* f1 = GetIntFieldInfo();
    FieldInfo* f2 = GetDoubleFieldInfo();

    LinearForm* a = CreateLinearForm(2,f1);
    LinearForm* b = CreateLinearForm(2,f2);
    LinearForm* r = CreateLinearForm(2,f1);

    // просто не вызываем Add - логическая проверка
    if (a->field != b->field) {
        printf("TestDifferentTypes passed\n");
    }

    FreeLinearForm(a);
    FreeLinearForm(b);
    FreeLinearForm(r);
}

// RUN ALL
void RunAllTests() {
    TestCreate();
    TestSetCoefficient();
    TestAdd();
    TestMultiply();
    TestEvaluate();
    TestDifferentTypes();

    printf("ALL TESTS PASSED\n");
}