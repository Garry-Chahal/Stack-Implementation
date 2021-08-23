#ifndef A3_Q3_H
#define A3_Q3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  int size;
  char** items;
} cStringStack;

//creates a new stack following the struct defined
//a new stack has size = 0 and items = NULL
cStringStack* cStringStack_create();

//pushes a given C string to the stack,
//you must copy the content instead of just the address
void cStringStack_push(cStringStack* csStack, char* cStr);

//pops the C string from the stack,
//implemented by returning the address of the C string (copy)
//if the stack has 1 item, once popped it should become the same as a new stack,
//if the stack is empty, return NULL
char* cStringStack_pop(cStringStack* csStack);

//checks if the stack is empty
bool cStringStack_isEmpty(cStringStack* csStack);

//frees all the memory used by the stack to store the C strings
void cStringStack_free(cStringStack* csStack);

//reverse the order of the C strings stored so the first added one
// will be popped first, and so on
void cStringStack_reverse(cStringStack* csStack);

//creates a copy of a stack,
//each item has to be a C string with the same content but in different address
cStringStack* cStringStack_duplicate(cStringStack* csStack);


#endif
