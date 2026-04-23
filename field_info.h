#ifndef UNTITLED6_FIELD_INFO_H
#define UNTITLED6_FIELD_INFO_H

#include <stdlib.h>

typedef struct {
    size_t size;

    void* (*add)(void*, void*);
    void* (*sub)(void*, void*);
    void* (*mul)(void*,void*);

    void* (*copy)(void*);
    void (*free)(void*);
} FieldInfo;

FieldInfo* GetIntFieldInfo();

FieldInfo* GetDoubleFieldInfo();

#endif
