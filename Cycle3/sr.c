#include<stdio.h>
#include<string.h>

typedef struct{
	char lhs;
	char rhs[10];
} Rule;

char expression[10], stack[10], input;
int top = -1, numrules = 8;
Rule rules[8];

void push(char c){
	stack[++top] = c;
}

int pop(){
	return stack[top--];
}

int reduce(){
	for(int i=0;i<numrules;i++){
		char rhs[10];
		strcpy(rhs, rules[i].rhs);
		
		if(top>=strlen(rhs)-1){
			char temp[10];
			for(int j=0;j<strlen(rhs);j++) temp[j]=stack[top-strlen(rhs)+1+j];
			temp[strlen(rhs)] = '\0';
			if(strcmp(temp, rhs)==0){
				for(int j=0;j<strlen(rhs);j++) pop();
				push(rules[i].lhs);
				for(int i=0;i<=top;i++) printf("%c", stack[i]);
				printf("\tReduced %c --> %s\n", rules[i].lhs, rules[i].rhs);
				return 1;
			} 
		}
	}
	return 0;
}

void main(){
	printf("Enter Expression: ");
	scanf("%s", expression);
	
	FILE *f = fopen("grammar.txt", "r");

	for(int i=0;i<numrules;i++){
		fscanf(f, " %c --> %s", &rules[i].lhs, rules[i].rhs);
	}
	
	for(int i=0;expression[i]!='\0';i++){
		input = expression[i];
		if(top == -1) {
			push(input);
			for(int i=0;i<=top;i++) printf("%c", stack[i]);
			printf("\tShifted %c\n", input);
		}
		else{
			while(reduce());
			push(input);
			for(int i=0;i<=top;i++) printf("%c", stack[i]);
			printf("\tShifted %c\n", input);
		}
	}
	while(reduce());

	printf("Final Stack: ");
	for(int i=0;i<=top;i++) printf("%c", stack[i]);
	
	if(top==0) printf("Parsed\n");
	else printf("rejected\n");
}   
