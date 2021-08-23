#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

#define MAX_CHAR_NUMBER 128

//prints the content of the stack
//not really appropriate for a stack but makes marking/testing easier
void cStringStack_print(cStringStack *csStack)
{
  //terminate function if csStack is NULL
  if (csStack == NULL)
  {
    puts("Error: stack pointer is NULL");
    return;
  }

  if (csStack->size == 0)
  {
    puts("Stack is empty.");
  }
  else
  {
    puts("---");
    for (int i = 0; i < csStack->size; i++)
    {
      printf("%s\n", csStack->items[i]);
    }
    puts("---");
  }
}

int main()
{
  //assume each user input has no more than 127 characters
  char userInput[MAX_CHAR_NUMBER];
  //request a stack struct
  cStringStack *inputStack = cStringStack_create();
  if (inputStack == NULL)
  {
    puts("Error: cannot create stack");
    exit(0);
  }

  //keep asking for user input and put it to the stack, stop if input is "quit"
  bool userQuits = false;
  while (!userQuits)
  {
    puts("\nInput a command and press enter,");
    puts("use \"undo\" to remove previous,");
    puts("or \"quit\" to quit:");
    //read a line and include space, need to remove the trailing \n
    if (fgets(userInput, MAX_CHAR_NUMBER, stdin) != NULL)
    {
      //replace the trailing \n with \0
      userInput[strcspn(userInput, "\n")] = '\0';
      if (strcmp(userInput, "quit") == 0)
      {
        userQuits = true;
      }
      else if (strcmp(userInput, "undo") == 0)
      {
        char *popped = cStringStack_pop(inputStack);
        if (popped == NULL)
        {
          puts("Stack is empty, nothing to pop.");
        }
        else
        {
          printf("Previous being removed: %s\n", popped);
          free(popped); //need to free this memory here otherwise it will be lost
        }
      }
      else
      {
        cStringStack_push(inputStack, userInput);
      }
    }
  }

  cStringStack_print(inputStack); //prints the user input from oldest to latest
  cStringStack *inputStack_copy = cStringStack_duplicate(inputStack);
  cStringStack_print(inputStack_copy); //print should be the same as above
  cStringStack_reverse(inputStack);
  cStringStack_print(inputStack);      //prints the user input from latest to oldest
  cStringStack_print(inputStack_copy); //print should remain the same

  cStringStack_free(inputStack);
  cStringStack_free(inputStack_copy);

  return 0;
}
