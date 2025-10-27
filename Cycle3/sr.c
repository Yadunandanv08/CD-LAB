#include<stdio.h>
#include <stdlib.h>

char stack[100];
char buffer[100];
int top = -1,reduced = 1;

void push(char value) {
    stack[++top] = value;
}

char pop() {
    return stack[top--];
}

void reduce(){
	
	if(stack[top] == 'i'){
		reduced = 1;
		stack[top] = 'S';
		return;
	}
	if (top > 1 && (stack[top] == 'S' && stack[top-1] == '+' && stack[top-2] == 'S')){
		reduced = 1;
		for(int i = 0; i < 2;i++) pop();
		return;
	}
	if (top > 1 && (stack[top] == 'S' && stack[top-1] == '*' && stack[top-2] == 'S')){
		reduced = 1;
		for(int i = 0; i < 2;i++) pop();
		return;
	}
    if (top > 1 && (stack[top] == ')' && stack[top-1] == 'S' && stack[top-2] == '(')){
		reduced = 1;
		for(int i = 0; i < 2;i++) pop();
		return;
	}
}

int main(){
    char expression[100];
    printf("Enter the expression: ");
    scanf("%s", expression);

    int i = 0;
    while(expression[i] != '\0'){
        char c = expression[i];

	while (reduced){
		reduced = 0;
		reduce();
	}
	
	reduced =1;
	push(c);
	i++; 
    }
    
    while(reduced){
    	reduced = 0;
    	reduce();
    }
    
    if (top == 0 && stack[top] == 'S'){
        printf("The expression is accepted.\n");
    } else {
        printf("The expression is not accepted.\n");
    }

}
