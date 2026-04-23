#include <stdlib.h>
#include <stddef.h>
#include "../include/field_info.h"

void* int_add(void* a, void* b);
void* int_sub(void* a, void* b);
void* int_mul(void* a, void* b);
void* int_copy(void* a);
void int_free(void* a);

FieldInfo* GetIntFieldInfo(){
    static FieldInfo* info = NULL;

    if (info == NULL){
        info = malloc(sizeof(FieldInfo));

        info->size = sizeof(int);
        info->add = int_add;
        info->sub = int_sub;
        info->mul = int_mul;
        info->copy = int_copy;
        info->free = int_free;
    }
    return info;
}

void* int_add(void* a, void* b) {
    int* result = malloc(sizeof(int));
    *result = (*(int*)a) + (*(int*)b);
    return result;
}

void* int_sub(void* a, void* b) {
    int* result = malloc(sizeof(int));
    *result = (*(int*)a) - (*(int*)b);
    return result;
}

void* int_mul(void* a, void* b) {
    int* result = malloc(sizeof(int));
    *result = (*(int*)a) * (*(int*)b);
    return result;
}

void* int_copy(void* a) {
    int* result = malloc(sizeof(int));
    *result = *(int*)a;
    return result;
}

void int_free(void* a) {
    free(a);
}
void* double_add(void* a, void* b){
    double* result = malloc(sizeof(double));
    *result = (*(double*)a) + (*(double*)b);
    return result;
}

void* double_sub(void* a, void* b){
    double* result = malloc(sizeof(double));
    *result = (*(double*)a) - (*(double*)b);
    return result;
}

void* double_mul(void* a, void* b){
    double* result = malloc(sizeof(double));
    *result = (*(double*)a) * (*(double*)b);
    return result;
}

void* double_copy(void* a){
    double* result = malloc(sizeof(double));
    *result = *(double*)a;
    return result;
}

void double_free(void* a){
    free(a);
}

FieldInfo* GetDoubleFieldInfo(){
    static FieldInfo* info = NULL;

    if (info == NULL){
        info = malloc(sizeof(FieldInfo));

        info->size = sizeof(double);
        info->add = double_add;
        info->sub = double_sub;
        info->mul = double_mul;
        info->copy = double_copy;
        info->free = double_free;
    }
    return info;
}