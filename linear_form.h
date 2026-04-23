#ifndef LINEAR_FORM_H
#define LINEAR_FORM_H

#include "field_info.h"

typedef struct {
    void** coeffs;
    int size;
    FieldInfo* field;
} LinearForm;

LinearForm* CreateLinearForm(int size, FieldInfo* field);

void SetCoefficient(LinearForm* lf, int index, void* value);

LinearForm* AddLinearForm(LinearForm* a, LinearForm* b);

LinearForm* MultiplyByScalar(LinearForm* lf, void* scalar);

void* EvaluateLinearForm(LinearForm* lf, void** x);

void FreeLinearForm(LinearForm* lf);

#endif