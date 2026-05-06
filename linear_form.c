#include "linear_form.h"
#include <stdlib.h>
#include <string.h>

// Макрос для удобного доступа к i-му элементу массива coeffs
// Возвращает указатель на i-й элемент в непрерывном блоке памяти
#define ELEM(lf, i) ((char*)(lf)->coeffs + (i) * (lf)->field->element_size)

LinearForm* lf_create(int size, FieldInfo* field_info) {
    if (!field_info || size <= 0) return NULL;

    LinearForm* lf = malloc(sizeof(LinearForm));
    if (!lf) return NULL;

    lf->size = size;
    lf->field = field_info;

    // Выделяем непрерывный блок памяти под все коэффициенты
    lf->coeffs = calloc(size, field_info->element_size);
    if (!lf->coeffs) {
        free(lf);
        return NULL;
    }

    return lf;
}

void lf_destroy(LinearForm* lf) {
    if (lf) {
        free(lf->coeffs);
        free(lf);
    }
}

void lf_set_coeff(LinearForm* lf, int index, const void* value) {
    if (!lf || index < 0 || index >= lf->size) return;
    // Копируем значение из value в ячейку памяти коэффициента
    lf->field->copy(value, ELEM(lf, index));
}

void* lf_get_coeff_ptr(const LinearForm* lf, int index) {
    if (!lf || index < 0 || index >= lf->size) return NULL;
    return ELEM(lf, index);
}

void lf_add(const LinearForm* a, const LinearForm* b, LinearForm* result) {
    if (!a || !b || !result) return;
    if (a->size != b->size || a->size != result->size) return;
    // Проверка типов: указатели на FieldInfo должны совпадать
    if (a->field != b->field || a->field != result->field) return;

    for (int i = 0; i < a->size; i++) {
        a->field->add(ELEM(a, i), ELEM(b, i), ELEM(result, i));
    }
}

void lf_sub(const LinearForm* a, const LinearForm* b, LinearForm* result) {
    if (!a || !b || !result) return;
    if (a->size != b->size || a->size != result->size) return;
    if (a->field != b->field || a->field != result->field) return;

    for (int i = 0; i < a->size; i++) {
        a->field->sub(ELEM(a, i), ELEM(b, i), ELEM(result, i));
    }
}

void lf_mul_scalar(const LinearForm* lf, const void* scalar, LinearForm* result) {
    if (!lf || !result || lf->size != result->size) return;
    if (lf->field != result->field) return;

    for (int i = 0; i < lf->size; i++) {
        lf->field->mul(ELEM(lf, i), scalar, ELEM(result, i));
    }
}

void lf_eval(const LinearForm* lf, const void** args, void* result) {
    if (!lf || !result || !args) return;

    FieldInfo* f = lf->field;

    // Инициализируем результат свободным членом a0
    f->copy(ELEM(lf, 0), result);

    // Создаем временную переменную для промежуточных вычислений
    void* temp = malloc(f->element_size);
    if (!temp) return;

    for (int i = 1; i < lf->size; i++) {
        // temp = ai * xi
        f->mul(ELEM(lf, i), args[i - 1], temp);

        // result = result + temp
        f->add(result, temp, result);
    }

    free(temp);
}
