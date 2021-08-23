#include "stack.h"
bool cStringStack_isEmpty(cStringStack *csStack);

// Create a new stack following the struct defined
cStringStack *cStringStack_create()
{
  // Allocate memory for the new stack based on the size of the stack
  cStringStack *stack = malloc(sizeof(cStringStack));

  // If memory failed to allocate for the stack, exit
  if (stack == NULL)
  {
    puts("Error: Cannot create empty stack.");
    exit(0);
  }
  else
  {
    // New stack has size 0
    stack->size = 0;

    // All items in the new stack are initialized as NULL;
    stack->items = NULL;
    return stack;
  }
}

// Push a given cstring to the stack
void cStringStack_push(cStringStack *csStack, char *cStr)
{
  // Increment the size of the stack
  int increased_size = ++csStack->size;

  // Reallocate the array so that it is a size larger
  // This function call is over 2 lines to keep it under 80 characters.
  csStack->items = realloc(csStack->items,
                           increased_size * sizeof(csStack->items));

  // If memory failed to reallocate for the stack, exit
  if (csStack->items == NULL)
  {
    puts("Error: Cannot reallocate within push function.");
    exit(0);
  }
  else
  {
    unsigned int last_index = csStack->size - 1;
    // Allocate memory in the last index to store characters of the string
    csStack->items[last_index] = malloc((strlen(cStr) + 1) * sizeof(char *));

    // If memory failed to allocate for the stack, exit
    if (csStack->items[last_index] == NULL)
    {
      puts("Error: Cannot push item to stack.");
      exit(0);
    }
    else
    {
      // We must copy the content of the cstring instead of the address
      strcpy(csStack->items[last_index], cStr);
    }
  }
}

// Pop the cstring from the stack
char *cStringStack_pop(cStringStack *csStack)
{
  // Return NULL if the stack is empty
  if (cStringStack_isEmpty(csStack))
  {
    return NULL;
  }

  // Reduce the size and return the last item in the array
  int decreased_size = --csStack->size;
  return csStack->items[decreased_size];
}

// Check if the stack is empty (size 0)
bool cStringStack_isEmpty(cStringStack *csStack)
{
  return csStack->size == 0;
}

// Frees all the memory used by the stack to store the cstrings
void cStringStack_free(cStringStack *csStack)
{
  // Go through the array, freeing the memory at each index
  for (unsigned int i = 0; i < csStack->size; i++)
  {
    free(csStack->items[i]);
    csStack->items[i] = NULL;
  }
  // Free the array, set the pointer to NULL, and size back to 0
  free(csStack->items);
  csStack->items = NULL;
  free(csStack);
  csStack = NULL;
}

// Reverse the order of the cstrings based on FIFO
// First In, First out
void cStringStack_reverse(cStringStack *csStack)
{
  int length = csStack->size;

  // Index decrementation starting from the last element
  int j = length - 1;

  /*
  Loop through the first half of the array, as we don't 
  want the array to be swapped back into the original again
  */
  for (unsigned int i = 0; i < length / 2; i++)
  {
    // Swap the current item with the item from the back
    char *temp = csStack->items[j];
    csStack->items[j] = csStack->items[i];
    csStack->items[i] = temp;
    j--;
  }
}
// Creates a duplicate copy of a stack,
cStringStack *cStringStack_duplicate(cStringStack *csStack)
{
  cStringStack *duplicateStack = cStringStack_create();
  /*
  Increment through the original stack and push 
  the elements to the duplicate stack
  */
  for (int i = 0; i < csStack->size; i++)
  {
    // Push function ensures we are copying the string, not the address
    cStringStack_push(duplicateStack, csStack->items[i]);
  }
  return duplicateStack;
}