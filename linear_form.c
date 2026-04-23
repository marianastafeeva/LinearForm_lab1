#include <stdlib.h>
#include "../include/linear_form.h"

LinearForm* CreateLinearForm(int size, FieldInfo* field){
    LinearForm* lf = malloc(sizeof(LinearForm)); //создаем массив коэфф

    lf->size = size;
    lf->field = field;

    lf->coeffs = malloc(size * sizeof(void*));

    for (int i = 0; i < size; i++){
        lf->coeffs[i] = NULL;
    }
    return lf;
}

//установка коэффицента
void SetCoefficient(LinearForm* lf, int index, void* value){
    //освобождаем память
    if (lf->coeffs[index] != NULL){
        lf->field->free(lf->coeffs[index]);
    }
    lf->coeffs[index] = lf->field->copy(value); //копируем значение
}

LinearForm* AddLinearForm(LinearForm* a, LinearForm* b){
    if (a->size != b->size || a->field != b->field){ //проверка типа и размера
        return NULL;
    }

    LinearForm* result = CreateLinearForm(a->size, a->field);
//складываем поэлементно
    for (int i = 0; i < a->size; i++){
        result->coeffs[i] = a->field->add(a->coeffs[i],b->coeffs[i]);
    }
    return result;
}

LinearForm* MultiplyByScalar(LinearForm* lf, void* scalar){
    LinearForm* result = CreateLinearForm(lf->size, lf->field);

    for (int i= 0; i < lf->size; i++){
        result->coeffs[i] = lf->field->mul(lf->coeffs[i], scalar);
    }
    return result;
}
//вычисление значения
void* EvaluateLinearForm(LinearForm* lf, void** x){
    void* result = lf->field->copy(lf->coeffs[0]);

    for (int i = 1; i < lf->size; i++){
        void* temp = lf->field->mul(lf->coeffs[i], x[i-1]);

        void* new_result = lf->field->add(result, temp);

        lf->field->free(result);
        lf->field->free(temp);

        result = new_result;
    }
    return result;
}

//освобождаем
void FreeLinearForm(LinearForm* lf) {
    for (int i = 0; i < lf->size; i++) {
        if (lf->coeffs[i] != NULL) {
            lf->field->free(lf->coeffs[i]);
        }
    }

    free(lf->coeffs);
    free(lf);
}