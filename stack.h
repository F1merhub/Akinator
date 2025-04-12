#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef char* stack_elem;

const int INCREASE_COEFFICIENT = 10;

const int STACK_CAPACITY = 100;

typedef struct Stack
{
    stack_elem *data;
    int size;
    int capacity;
} Stack;

enum errorcode
{
    STK_OK =                        0,  // все ок
    STK_OUT_MEMORY =                1,  // calloc не дал память
    STK_NULL_POINTER =              2,  // date = 0
    STK_BAD_SIZE =                  3,  // size < 0
    STK_BAD_CAPACITY =              4,  // capacity <= 0
    STK_SIZE_LARGER_CAPACITY =      5,  // вышли за размер стэка
    REALLOCK_FAIL =                 6,  // не получилось расширить стэк
    BAD_CANARY_1 =                  7,  // левая канарейка
    BAD_CANARY_2 =                  8,  // правая канарейка
};

int verificator(struct stack *stk);

const char* decoder(int error);

void stk_assert(struct stack *stk);

int stk_null_check(struct stack *stk);

int put_canary(struct stack *stk);

int stack_destructor(struct stack* stk);

int stack_constructor(struct stack * stk, int capacity);

int stack_push(struct stack*stk, stack_elem value);

int stack_pop(struct stack*stk);

int stack_dump(struct stack*stk);

int realloc_up(struct stack *stk);

const stack_elem CANARY = (stack_elem)0xBADC0FFEE;

const stack_elem POISON = (stack_elem)0xBAD1ABA;

#endif
