/* Tina Tami
 *
 * This file takes as input an expression in infix
 * notation, and returns that expression in reverse
 * Polish notation. */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

/* This is a list of the precedence of each operator. */
int checkPrec(char operator) {
	switch (operator) {
		case '+':
			return 5;
			break; 
		case '-':
			return 5;
			break; 
		case '*':
			return 4;
			break; 
		case '/':
			return 4;
			break;
		case '^':
			return 3;
			break;  
		case '~':
			return 2;
			break; 
		case 'F':
			return 1;
			break; 
		case 'f':
			return 1;
			break; 
		default:
			return 0;
			break;
	}
}

/* This is a list of the association of each operator. 
 * Here, 9 means left and 8 means right. */ 
int checkAssoc(char operator) {
	switch (operator) {
		case '*':
			return 9;
			break; 
		case '/':
			return 9;
			break;
		case '+':
			return 9;
			break; 
		case '-':
			return 9;
			break; 
		case '^':
			return 9;
			break;  
		case '~':
			return 8;
			break; 
		case 'F':
			return 9;
			break; 
		case 'f':
			return 9;
			break; 
		default:
			return 0;
			break;
	}
}

/* A check to know if something is an operator. */
int checkOper(char operator) {
	switch (operator) {
		case '*':
			return 1;
			break; 
		case '/':
			return 1;
			break;
		case '+':
			return 1;
			break; 
		case '-':
			return 1;
			break; 
		case '^':
			return 1;
			break;  
		case '~':
			return 1;
			break; 
		default:
			return 0;
			break;
	}
}

/* Checks if expression is valid by checking if there are digits. Firstly,
 * the programme handles digits, then functions, and then operators. After
 * this is done, it handles left and right brackets. Finally, it empties
 * the stack. */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }
    char *input = argv[1];
    struct stack* s = stack_init();
    int digits = 0;
    int len = (int)strlen(input);
    for (int i = 0; i < len; i++) {
        if (isdigit(input[i])) {
            digits++;
        }
    }
    if (digits == 0) {
        return 1;
    }
	int currentChar = input[0];
	int reader = 0;
	while (currentChar != 0) {
		/* Handling digits. */
		if (isdigit(currentChar)) {
			printf("%c", currentChar);
			if (!isdigit(input[reader + 1])) {
				printf("%c", ' ');
			}
		}

		/* Handling functions. */
		else if (currentChar == 'f' || currentChar == 'F') {
			stack_push(s, currentChar);
		}

		/* Handling operators. */
		else if (checkOper((char)currentChar) == 1) {
			char peek = (char)stack_peek(s);
			while (checkOper(peek) == 1 && (stack_empty(s) != 1) && 
			(checkPrec((char)peek) < checkPrec((char)currentChar) ||
			(checkPrec((char)peek) == checkPrec((char)currentChar) && 
			checkAssoc(peek) == 9))) {
				printf("%c ", stack_pop(s));
				peek = (char)stack_peek(s);
			}
			stack_push(s, currentChar);
		}

		/* Handling left brackets. */
		else if (currentChar == '(') {
			stack_push(s, currentChar);
			
		}

		/* Handling right brackets. */
		else if (currentChar == ')') {
			while (stack_peek(s) != '(' && !(stack_empty(s))) {
				printf("%c ", stack_pop(s));
			}
			if (stack_empty(s) == 1) {
                    printf("Parentheses do not match\n");
                    return 1;
            }
			stack_pop(s);
		}
		reader++;
		currentChar = input[reader];
	}

	/* Empty stack when done. */
	while (stack_empty(s) == 0) {
		if ((stack_peek(s) == '(') || (stack_peek(s) == ')')) {
            printf("Parentheses do not match\n");
            return 1;
        }
		printf("%c ", stack_pop(s));
	}
	printf("\n");
    stack_cleanup(s);
    return 0;
}
