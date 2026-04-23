#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stdlib.h>

// размер типа и операции над ним
typedef struct {
    size_t size;

// результат записывается в уже выделенную память result
    void (*add)(void*, void*, void*);
    void (*sub)(void*, void*, void*);
    void (*mul)(void*, void*, void*);

    void (*copy)(void*, void*); // копирование значения
} FieldInfo;

FieldInfo* GetIntFieldInfo();
FieldInfo* GetDoubleFieldInfo();

#endif