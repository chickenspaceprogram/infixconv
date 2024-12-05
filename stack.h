/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct stack Stack;

// apologies for the function pointers, OOP was natural here
struct stack {
    // fields
    void *data_arr;
    size_t num_elements;
    const size_t element_size;
    size_t space;

    // methods
    int (*push)(Stack *stack, void *obj); // pushes an object onto the stack, returns success/failure code
    int (*pop)(Stack *stack, void *buf); // copies the top object into `buf`, then pops it off the stack
    void (*peek)(Stack *stack, void *buf); // copies the top object into `buf`
    void (*free)(Stack *stack); // frees the stack
};

Stack newStack(size_t element_size);

#endif