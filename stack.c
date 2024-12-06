/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MIN_STACK_SIZE 16
#define STACK_REDUCE_TRIGGER 4 // stack will realloc() when num_elements < space / STACK_REDUCE_TRIGGER && space > MIN_STACK_SIZE
#define STACK_REDUCE_MULTIPLIER 2 // stack will be reduced to a size of space / STACK_REDUCE_MULTIPLIER when necessary
#define STACK_GROW_MULTIPLIER 2 // stack will grow to a size of space * STACK_GROW_MULTIPLIER when necessary

/* Public */
int push(Stack *stack, void *obj);
int pop(Stack *stack, void *buf);
int peek(Stack *stack, void *buf);
void stack_free(Stack *stack);

/* Private */
int realloc_stack(Stack *stack, size_t new_size); // new_size is a number of elements, not a size in bytes!



/* Constructor */
Stack newStack(size_t element_size) {
    Stack new = {
        .data_arr = NULL,
        .num_elements = 0,
        .element_size = element_size,
        .space = MIN_STACK_SIZE, // number of elements, not number of bytes
        .push = &push,
        .pop =  &pop,
        .peek = &peek,
        .free = &stack_free
    };
    new.data_arr = malloc(new.element_size * new.space); // user must check this for NULL
    return new;
}

/* Public */

int push(Stack *stack, void *obj) {
    if (stack->num_elements >= stack->space) {
        if (realloc_stack(stack, stack->space * STACK_GROW_MULTIPLIER) == -1) {
            return -1;
        }
    }

    ++(stack->num_elements);

    memcpy((char *)stack->data_arr + stack->num_elements * stack->element_size, obj, stack->element_size);
    return 0;
}

int pop(Stack *stack, void *buf) {

    if (stack->peek(stack, buf) == -1) {
        return -1;
    }
    
    --(stack->num_elements);
    if ((stack->num_elements < stack->space / STACK_REDUCE_TRIGGER) && stack->space > MIN_STACK_SIZE) {
        return realloc_stack(stack, stack->space / STACK_REDUCE_MULTIPLIER);
    }
    return 0;
}

int peek(Stack *stack, void *buf) {
    if (stack->num_elements == 0) {
        return -1;
    }
    memcpy(buf, (char *)stack->data_arr + stack->num_elements * stack->element_size, stack->element_size);
    return 0;
}

void stack_free(Stack *stack) {
    free(stack->data_arr);
    stack->data_arr = NULL;
    stack->space = 0;
    stack->num_elements = 0;
}

/* Private */
int realloc_stack(Stack *stack, size_t new_size) {

    if (stack->num_elements > stack->space) {
        return -1;
    }

    void *new_ptr = realloc(stack->data_arr, new_size * stack->element_size);

    // checking for memory allocation issues
    if (new_ptr == NULL) {
        stack->free(stack);
        return -1;
    }

    stack->data_arr = new_ptr;
    stack->space = new_size;
    return 0;
}