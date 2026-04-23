#ifndef LINEAR_FORM_H
#define LINEAR_FORM_H

#include "field_info.h"

typedef struct {
    void* coeffs; // массив значений подряд
    int size; // количество коэффициентов
    FieldInfo* field; // тип
} LinearForm;

LinearForm* CreateLinearForm(int size, FieldInfo* field);
void SetCoefficient(LinearForm* lf, int index, void* value);

void AddLinearForm(LinearForm* a, LinearForm* b, LinearForm* result);
void MultiplyByScalar(LinearForm* lf, void* scalar, LinearForm* result);

void EvaluateLinearForm(LinearForm* lf, void** x, void* result);

void FreeLinearForm(LinearForm* lf);

#endif