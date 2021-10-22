/* Tina Tami
 *
 * This file contains the data structure described
 * in the stack.h file. */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define STACK_SIZE 100

/* These are the variables we will need. */
struct stack {
	int pushes;
	int pops;
	int maxSize;
	int currentSize;
	int myStack[STACK_SIZE]; 
};


/* Setting all the variables to zero. */
struct stack *stack_init() {
    struct stack* s = malloc(sizeof(struct stack));
	s -> pushes = 0;
	s -> pops = 0;
	s -> maxSize = 0;
	s -> currentSize = 0;
    return s;
}

/* Printing the stats and cleaning the stack. */
void stack_cleanup(struct stack* s) {
	int pushesInt = s -> pushes;
	int popsInt = s -> pops;
	int maxSizeInt = s -> maxSize;
	fprintf(stderr, "Statistics: %d %d %d\n", pushesInt, popsInt, maxSizeInt);
    free(s);
}

/* Pushes the element on to the stack if there is room left 
 * in the stack. */
int stack_push(struct stack *s, int c) {
	if (s -> currentSize < STACK_SIZE) {
		s -> myStack[s -> currentSize] = c;
		s -> currentSize++;
		s -> pushes++;
		if (s -> currentSize > s -> maxSize) {
			s -> maxSize = s -> currentSize;
		}
		return 0;
	}
    return 1;
}

/* Pops the element from the stack if the stack is not empty. */
int stack_pop(struct stack *s) {
	if (s -> currentSize == 0) {
		return -1;
	}
	s -> pops++;
	s -> currentSize--;
	return s -> myStack[s -> currentSize];
}

/* Returns the top element if the stack is not empty. */
int stack_peek(struct stack *s) {
	if (s -> currentSize == 0) {
		return -1;
	}
	return s -> myStack[s -> currentSize - 1]; 
}

/* Checks if the stack is empty by checking its size. */
int stack_empty(struct stack *s) {
	if (s -> currentSize == 0) {
		return 1;
	}
   	return 0;
}
