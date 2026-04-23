#include "linear_form.h"
#include <stdlib.h>
#include <string.h>

// макрос для получения i-го элемента
#define ELEM(lf, i) ((char*)lf->coeffs + i * lf->field->size)

// создание формы
LinearForm* CreateLinearForm(int size, FieldInfo* field) {
    LinearForm* lf = malloc(sizeof(LinearForm));

    lf->size = size;
    lf->field = field;
    // выделяем память под все коэффициенты сразу
    lf->coeffs = calloc(size, field->size);

    return lf;
}

void SetCoefficient(LinearForm* lf, int index, void* value) {
    // копируем значение в нужную позицию
    lf->field->copy(value, ELEM(lf, index));
}

void AddLinearForm(LinearForm* a, LinearForm* b, LinearForm* result) {
    for (int i = 0; i < a->size; i++) {
        a->field->add(ELEM(a,i), ELEM(b,i), ELEM(result,i));
    }
}

void MultiplyByScalar(LinearForm* lf, void* scalar, LinearForm* result) {
    for (int i = 0; i < lf->size; i++) {
        lf->field->mul(ELEM(lf,i), scalar, ELEM(result,i));
    }
}

void EvaluateLinearForm(LinearForm* lf, void** x, void* result) {
    // result = a0
    lf->field->copy(ELEM(lf,0), result);

    char temp[64]; // временная память

    for (int i = 1; i < lf->size; i++) {
        // temp = ai * xi
        lf->field->mul(ELEM(lf,i), x[i-1], temp);
        // result = result + temp
        lf->field->add(result, temp, result);
    }
}

void FreeLinearForm(LinearForm* lf) {
    free(lf->coeffs);
    free(lf);
}