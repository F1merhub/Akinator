#include "akinator.h"
#include "stack.h"

int verificator(Stack *stk)
{

    int error = 0;

    if (stk == NULL)
        error = STK_NULL_POINTER;

    if (stk->data == NULL)
        error = STK_OUT_MEMORY;

    if (stk->size < 0)
        error = STK_BAD_SIZE;

    if (stk->capacity <= 0)
        error = STK_BAD_CAPACITY;

    if (stk->size > stk->capacity)
        error = STK_SIZE_LARGER_CAPACITY;

    if (stk->data[0] != CANARY)
        error = BAD_CANARY_1;

    if (stk->data[stk->capacity + 1] != CANARY)
        error = BAD_CANARY_2;

    return error;
}

const char* decoder(int error) {

    if (error == STK_OUT_MEMORY)
        return "memory allocation error\n";
    if (error == STK_NULL_POINTER)
        return "Stackpointer is null\n";
    if (error == STK_BAD_SIZE)
        return "Stacksize < 0\n";
    if (error == STK_BAD_CAPACITY)
        return "Stackcapacity <= 0\n";
    if (error == STK_SIZE_LARGER_CAPACITY)
        return "size > capacity\n";
    if (error == BAD_CANARY_1)
        return "canary1 was changed\n";
    if (error == BAD_CANARY_2)
        return "canary2 was changed\n";
    else
        return NULL;
    };


void stk_assert(Stack *stk) {
    int error = verificator(stk);
    if (error) {
        printf("%s", decoder(error));
        assert(0);
    }
}


int stk_null_check(Stack *stk) {  // много раз встречается
    if (stk == NULL) {
        printf("stk pointer is NULL\n");
        assert(0);
    }
    return 0;
}

int put_canary(Stack *stk) {
    stk_null_check(stk);
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}


int stack_destructor(Stack* stk) {
    stk_null_check(stk);
    for (int i = 0; i < stk ->capacity + 1; ++i)
        stk->data[i] = POISON;
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;

    return 0;
}


int stack_constructor(Stack* stk, int capacity) {

    stk_null_check(stk);

    if (capacity <= 0) {
        printf("capacity is not positive\n");
        assert(0);
    }

    stk->data = (stack_elem *)calloc(capacity + 2, sizeof(stack_elem));
    if (stk->data == NULL) {
        printf("memory allocation error\n");
        assert(0);
    }

    stk->size = 0;
    stk->capacity = capacity;
    put_canary(stk);
    // stk_assert(stk);

    return 0;
}


int stack_push(Stack *stk, stack_elem value) {  // добавить с реалоком
    stk_assert(stk);
        if (stk->size  == stk->capacity) {
        printf("size bigger than capacity\n");
        assert(0);
    }

    stk->data[stk->size + 1] = value;
    (stk->size)++;
    stk_assert(stk);

    return 0;
}

// ПОПРАВИЛ ФУНКЦИЮ, ЧТОБЫ НЕ ВОЗВРАЩАЛА ЭЛЕМЕНТ
// int stack_pop(struct stack*stk, stack_elem *pop_elem)
int stack_pop(Stack *stk) { // добавить реаллок вниз
    stk_assert(stk);
    if (stk->size  == 0) {
        printf("empty stack\n");
        assert(0);
    }
    stk->size--;
    // *pop_elem = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;
    stk_assert(stk);

    return 0;
}


int stack_dump(Stack *stk) {
    stk_assert(stk);
    for (int i = 1; i < (stk->size) + 1; ++i) {
        printf("%p ", stk->data[i]);
    }
    printf("\n"
           "%d - capacity\n"
           "%d - size\n"
           "%p - pointer on data\n",
           stk->capacity, stk->size, stk->data);

    return 0;
}

int realloc_up(Stack *stk) {
    stk_assert(stk);
    if (INCREASE_COEFFICIENT <= 0) {
        printf("change increase_coefficient\n"); // TODO исправить на возврат ошибки
        assert(0);
    }
    stack_elem *new_ptr = (stack_elem *)realloc(stk->data, (stk -> capacity + 2 + INCREASE_COEFFICIENT) * sizeof(stack_elem));
    if(new_ptr == NULL) {
        printf("memory reallocation error\n");
        assert(0);
    }
    stk->data = new_ptr;
    stk->capacity = stk->capacity + INCREASE_COEFFICIENT;
    stk->data[stk->capacity + 1] = CANARY;
    return 0;
}
