#include "field_info.h"
#include <stdlib.h>
#include <stdio.h>



static void int_add(const void* a, const void* b, void* res) {
    *(int*)res = *(const int*)a + *(const int*)b;
}

static void int_sub(const void* a, const void* b, void* res) {
    *(int*)res = *(const int*)a - *(const int*)b;
}

static void int_mul(const void* a, const void* b, void* res) {
    *(int*)res = *(const int*)a * *(const int*)b;
}

static void int_copy(const void* src, void* dst) {
    *(int*)dst = *(const int*)src;
}

static void int_init_zero(void* dst) {
    *(int*)dst = 0;
}

static void int_init_one(void* dst) {
    *(int*)dst = 1;
}

static void int_neg(const void* a, void* res) {
    *(int*)res = -(*(const int*)a);
}

static FieldInfo IntFieldInfo = {
        .element_size = sizeof(int),
        .add = int_add,
        .sub = int_sub,
        .mul = int_mul,
        .copy = int_copy,
        .init_zero = int_init_zero,
        .init_one = int_init_one,
        .neg = int_neg
};

FieldInfo* GetIntFieldInfo(void) {
    return &IntFieldInfo;
}


static void double_add(const void* a, const void* b, void* res) {
    *(double*)res = *(const double*)a + *(const double*)b;
}

static void double_sub(const void* a, const void* b, void* res) {
    *(double*)res = *(const double*)a - *(const double*)b;
}

static void double_mul(const void* a, const void* b, void* res) {
    *(double*)res = *(const double*)a * *(const double*)b;
}

static void double_copy(const void* src, void* dst) {
    *(double*)dst = *(const double*)src;
}

static void double_init_zero(void* dst) {
    *(double*)dst = 0.0;
}

static void double_init_one(void* dst) {
    *(double*)dst = 1.0;
}

static void double_neg(const void* a, void* res) {
    *(double*)res = -(*(const double*)a);
}

static FieldInfo DoubleFieldInfo = {
        .element_size = sizeof(double),
        .add = double_add,
        .sub = double_sub,
        .mul = double_mul,
        .copy = double_copy,
        .init_zero = double_init_zero,
        .init_one = double_init_one,
        .neg = double_neg
};

FieldInfo* GetDoubleFieldInfo(void) {
    return &DoubleFieldInfo;
}
