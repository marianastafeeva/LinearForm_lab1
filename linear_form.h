#ifndef LINEAR_FORM_H
#define LINEAR_FORM_H

#include "field_info.h"

typedef struct {
    void* coeffs;
    int size;
    FieldInfo* field;
} LinearForm;

LinearForm* lf_create(int size, FieldInfo* field_info);
void lf_destroy(LinearForm* lf);
void lf_set_coeff(LinearForm* lf, int index, const void* value);
void* lf_get_coeff_ptr(const LinearForm* lf, int index);

void lf_add(const LinearForm* a, const LinearForm* b, LinearForm* result);
void lf_sub(const LinearForm* a, const LinearForm* b, LinearForm* result);
void lf_mul_scalar(const LinearForm* lf, const void* scalar, LinearForm* result);
void lf_eval(const LinearForm* lf, const void** args, void* result);

#endif

