#include "field_info.h"

void int_add(void* a, void* b, void* r) {
    *(int*)r = *(int*)a + *(int*)b;
}

void int_sub(void* a, void* b, void* r) {
    *(int*)r = *(int*)a - *(int*)b;
}

void int_mul(void* a, void* b, void* r) {
    *(int*)r = *(int*)a * *(int*)b;
}

void int_copy(void* src, void* dst) {
    *(int*)dst = *(int*)src;
}

FieldInfo* GetIntFieldInfo() {
    static FieldInfo info;

    info.size = sizeof(int);
    info.add = int_add;
    info.sub = int_sub;
    info.mul = int_mul;
    info.copy = int_copy;

    return &info;
}


void double_add(void* a, void* b, void* r) {
    *(double*)r = *(double*)a + *(double*)b;
}

void double_sub(void* a, void* b, void* r) {
    *(double*)r = *(double*)a - *(double*)b;
}

void double_mul(void* a, void* b, void* r) {
    *(double*)r = *(double*)a * *(double*)b;
}

void double_copy(void* src, void* dst) {
    *(double*)dst = *(double*)src;
}

FieldInfo* GetDoubleFieldInfo() {
    static FieldInfo info;

    info.size = sizeof(double);
    info.add = double_add;
    info.sub = double_sub;
    info.mul = double_mul;
    info.copy = double_copy;

    return &info;
}