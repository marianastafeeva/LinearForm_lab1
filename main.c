#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "field_info.h"
#include "linear_form.h"

#define ELEM_RAW(ptr, size, i) ((char*)(ptr) + i*(size))


FieldInfo* chooseField() {
    int t;
    printf("1-int 2-double: ");
    scanf("%d",&t);
    return (t==1)?GetIntFieldInfo():GetDoubleFieldInfo();
}

//записывает число в память
void inputValue(FieldInfo* f, void* dst) {
    if (f->size == sizeof(int)) {
        scanf("%d",(int*)dst);
    } else {
        scanf("%lf",(double*)dst);
    }
}

void printValue(FieldInfo* f, void* v) {
    if (f->size == sizeof(int)) {
        printf("%d\n",*(int*)v);
    } else {
        printf("%lf\n",*(double*)v);
    }
}

// операции
void runOp(int op) {
    FieldInfo* f = chooseField();

    void* a = malloc(f->size);
    void* b = malloc(f->size);
    void* r = malloc(f->size);

    printf("Enter a: "); inputValue(f,a);
    printf("Enter b: "); inputValue(f,b);

    if(op==1) f->add(a,b,r);
    if(op==2) f->sub(a,b,r);
    if(op==3) f->mul(a,b,r);

    printf("Result: ");
    printValue(f,r);

    free(a); free(b); free(r);
}

// линейная форма
void runLinear() {
    FieldInfo* f = chooseField();

    int n;
    printf("size: ");
    scanf("%d",&n);

    LinearForm* lf = CreateLinearForm(n,f);

    for(int i=0;i<n;i++){
        printf("a%d: ",i);
        void* tmp = malloc(f->size);
        inputValue(f,tmp);
        SetCoefficient(lf,i,tmp);
        free(tmp);
    }

    if(n>1){
        void** args = malloc((n-1)*sizeof(void*));

        for(int i=0;i<n-1;i++){
            args[i] = malloc(f->size);
            printf("x%d: ",i+1);
            inputValue(f,args[i]);
        }

        void* res = malloc(f->size);

        EvaluateLinearForm(lf,args,res);

        printf("Result: ");
        printValue(f,res);

        for(int i=0;i<n-1;i++) free(args[i]);
        free(args);
        free(res);
    }

    FreeLinearForm(lf);
}

void menu() {
    printf("\n1-tests\n2-add\n3-sub\n4-mul\n5-linear\n0-exit\n");
}

int main() {
    int c;

    while(1){
        menu();
        scanf("%d",&c);

        if(c==1) RunAllTests();
        if(c==2) runOp(1);
        if(c==3) runOp(2);
        if(c==4) runOp(3);
        if(c==5) runLinear();
        if(c==0) break;
    }

    return 0;
}