/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "../../stack.h"



int main(void) {
    Stack stk = newStack(sizeof(char));
    char str[] = "hello world this is a test of a stack";
    char temp;
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i) {
        assert(stk.push(&stk, &(str[i])) != -1);
    }

    for (int i = len - 1; i >= 0; --i) {
        assert(stk.pop(&stk, &temp) != -1);
        assert(temp == str[i]);
    }
    stk.free(&stk);
}