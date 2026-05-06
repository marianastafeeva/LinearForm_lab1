#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "tests.h"
#include "linear_form.h"
#include "field_info.h"

#define EPSILON 1e-9

static int double_equals(double a, double b) {
    return fabs(a - b) < EPSILON;
}

// 1. Test Create
void TestCreate() {
    printf("1. TestCreate... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* lf = lf_create(3, f);
    assert(lf != NULL && "Failed to create");
    assert(lf->size == 3 && "Wrong size");
    lf_destroy(lf);
    printf("PASSED\n");
}

// 2. Test Set Coefficient
void TestSetCoefficient() {
    printf("2. TestSetCoefficient... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* lf = lf_create(2, f);

    double val = 123.456;
    lf_set_coeff(lf, 1, &val);

    double* retrieved = (double*)lf_get_coeff_ptr(lf, 1);
    assert(retrieved != NULL && "Pointer is NULL");
    assert(double_equals(*retrieved, 123.456) && "Value mismatch");

    lf_destroy(lf);
    printf("PASSED\n");
}

// 3. Test Add
void TestAdd() {
    printf("3. TestAdd... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* a = lf_create(2, f);
    LinearForm* b = lf_create(2, f);
    LinearForm* r = lf_create(2, f);

    double v1 = 1.0, v2 = 2.0;
    double v3 = 3.0, v4 = 4.0;

    lf_set_coeff(a, 0, &v1); lf_set_coeff(a, 1, &v2);
    lf_set_coeff(b, 0, &v3); lf_set_coeff(b, 1, &v4);

    lf_add(a, b, r);

    assert(double_equals(*(double*)lf_get_coeff_ptr(r, 0), 4.0) && "Add error idx 0");
    assert(double_equals(*(double*)lf_get_coeff_ptr(r, 1), 6.0) && "Add error idx 1");

    lf_destroy(a); lf_destroy(b); lf_destroy(r);
    printf("PASSED\n");
}

// 4. Test Multiply by Scalar
void TestMultiply() {
    printf("4. TestMultiply... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* a = lf_create(2, f);
    LinearForm* r = lf_create(2, f);

    double v1 = 2.0, v2 = 3.0;
    double scalar = 5.0;

    lf_set_coeff(a, 0, &v1);
    lf_set_coeff(a, 1, &v2);

    lf_mul_scalar(a, &scalar, r);

    assert(double_equals(*(double*)lf_get_coeff_ptr(r, 0), 10.0) && "Mul error idx 0");
    assert(double_equals(*(double*)lf_get_coeff_ptr(r, 1), 15.0) && "Mul error idx 1");

    lf_destroy(a); lf_destroy(r);
    printf("PASSED\n");
}

// 5. Test Evaluate
void TestEvaluate() {
    printf("5. TestEvaluate... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* lf = lf_create(3, f); // a0 + a1*x1 + a2*x2

    double a0 = 1.0, a1 = 2.0, a2 = 3.0;
    lf_set_coeff(lf, 0, &a0);
    lf_set_coeff(lf, 1, &a1);
    lf_set_coeff(lf, 2, &a2);

    double x1 = 2.0, x2 = 1.0;
    const void* args[2] = { &x1, &x2 };

    double result;
    lf_eval(lf, args, &result);

    // 1 + 2*2 + 3*1 = 8.0
    assert(double_equals(result, 8.0) && "Eval error");

    lf_destroy(lf);
    printf("PASSED\n");
}

// 6. Negative Test: Different Sizes
void TestNegativeDifferentSizes() {
    printf("6. TestNegDiffSizes... ");
    FieldInfo* f = GetDoubleFieldInfo();
    LinearForm* a = lf_create(2, f);
    LinearForm* b = lf_create(3, f); // Different size
    LinearForm* r = lf_create(2, f);

    lf_add(a, b, r);

    assert(double_equals(*(double*)lf_get_coeff_ptr(r, 0), 0.0) && "Result changed unexpectedly");

    lf_destroy(a); lf_destroy(b); lf_destroy(r);
    printf("PASSED\n");
}

// 7. Negative Test: Different Types
void TestNegativeDifferentTypes() {
    printf("7. TestNegDiffTypes... ");
    FieldInfo* f_int = GetIntFieldInfo();
    FieldInfo* f_double = GetDoubleFieldInfo();

    LinearForm* a = lf_create(2, f_int);
    LinearForm* b = lf_create(2, f_double); // Different type
    LinearForm* r = lf_create(2, f_int);

    lf_add(a, b, r);

    assert(*(int*)lf_get_coeff_ptr(r, 0) == 0 && "Result changed unexpectedly");

    lf_destroy(a); lf_destroy(b); lf_destroy(r);
    printf("PASSED\n");
}

void RunAllTests() {
    printf("\n=== STARTING 7 AUTOMATED TESTS ===\n");
    TestCreate();
    TestSetCoefficient();
    TestAdd();
    TestMultiply();
    TestEvaluate();
    TestNegativeDifferentSizes();
    TestNegativeDifferentTypes();
    printf("=== ALL 7 TESTS PASSED ===\n\n");
}
