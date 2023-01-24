#include <stdio.h>

struct element
{
    int dana;
    struct element * pop;

};

typedef struct element elem;

int empty(elem * stos)
{
    if(stos == NULL)
    {
        return 1; /// 1 - oznacza ze stos jest pusty
    }

    return 0; /// 0 -stos a elementy
}

void push(elem **stos, int wartosc)
{
    elem *nowy=malloc(sizeof(elem));
    nowy->pop=*stos;
    *stos=nowy;
    nowy->dana=wartosc;
}

void print(elem *stos)
{
    while(stos)
    {
        printf(" %d\n",stos->dana);
        stos=stos->pop;
    }
}

void pop(elem **stos, int *wartosc)
{
    elem *pom=*stos;
    *stos=(*stos)->pop;
    *wartosc=pom->dana;
    free(pom);
}

void inicjuj(elem **stos)
{
    *stos=NULL;
}

int main()
{
    elem *szczyt;
    inicjuj(&szczyt);
    int el;
    printf("fun empty %d\n",empty(szczyt));
    push(&szczyt,5);
    push(&szczyt,2);
    push(&szczyt,4);
    push(&szczyt,1);
    print(szczyt);
    pop(&szczyt,&el);
     printf("................\n");
    print(szczyt);
    return 0;
}
