#include <stdio.h>
#include <string.h>

char operators[5] = {'+', '-', '*', '/', '$'};
char table[5][5], stack[20], expression[20], opstack[20];
int top=-1, optop=-1;

void read_precedence_table(){
	FILE *f = fopen("test.txt", "r");
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
            		char ch;
			fscanf(f, " %c", &table[i][j]);
		}
	}
	printf("\t");
	for(int i=0;i<5;i++)
		printf("%c\t", operators[i]);
	printf("\n");
	for(int i=0;i<5;i++){
		printf("%c\t", operators[i]);
		for(int j=0;j<5;j++){
          		printf("%c\t", table[i][j]);
		}
		printf("\n");
	}
}

int isoperator(char c){
	for(int i=0;i<5;i++)
		if(operators[i]==c)
			return 1;
	return 0;
}

void push(char c, char stack[], int *top){
	stack[++(*top)]=c;
}

char pop(char stack[], int *top){
	return stack[(*top)--];
}

int indexof(char c){
	for(int i=0;i<5;i++)
		if(operators[i]==c)
			return i;
	return -1;
}

void parse(){
	int i=0;
	while(opstack[optop]!='$' || expression[i]!='$'){
		char input = expression[i];
		char topoperator = opstack[optop];

		if(!isoperator(input)){
            if(!isoperator(stack[top])){
                printf("Error in parsing\n");
                return;
            }
			push(input, stack, &top);
			printf("Shifted %c\n", input);
            i++;
		}
		else{
            if(isoperator(stack[top])){
                printf("Error in parsing\n");
                return;
            }
			char action = table[indexof(topoperator)][indexof(input)];
			if(action == '<'){
				push(input, stack, &top);
				push(input, opstack, &optop);
				printf("Shifted %c\n", input);
                i++;
			}
			else if(action == '>'){
				while(table[indexof(topoperator)][indexof(input)]=='>'){
					pop(opstack, &optop);
					topoperator = opstack[optop];
					char op2 = pop(stack, &top);
					char oper = pop(stack, &top);
					char op1 = stack[top];
					printf("Reduced: %c%c%c\n", op1, oper, op2);
				}
			}
		}	
	}
    if(opstack[optop]=='$'){
        printf("Parsed successfully\n");
    }
    else
        printf("Error in parsing\n");
}

void main(){

	stack[++top] = '$';
	opstack[++optop] = '$';
	
	printf("Enter expression: ");
	scanf("%s", expression);
	expression[strlen(expression)]='$';
	expression[strlen(expression)]='\0';
	
	read_precedence_table();
	parse();
}
