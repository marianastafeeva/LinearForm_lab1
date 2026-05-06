#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>


// Все операции записывают результат в заранее выделенную память 'res'
typedef void (*OpBinary)(const void* a, const void* b, void* res);
typedef void (*OpUnary)(const void* a, void* res);
typedef void (*OpCopy)(const void* src, void* dst);
typedef void (*OpInit)(void* dst);

// Структура, описывающая поведение типа данных
typedef struct {
    size_t element_size;

    OpBinary add;
    OpBinary sub;
    OpBinary mul;
    OpCopy copy;

    OpInit init_zero;
    OpInit init_one;
    OpUnary neg;
} FieldInfo;

FieldInfo* GetIntFieldInfo(void);
FieldInfo* GetDoubleFieldInfo(void);

#endif
