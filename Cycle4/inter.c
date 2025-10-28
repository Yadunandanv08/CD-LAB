#include<stdio.h>
#include<string.h>

char expression[10], reg;

void generate_code_for_operator(char operator){
	int i=0, newlen=-1;
	char newexp[10];
	while(expression[i]!='\0'){
		if(expression[i]==operator){
			printf("%c\t%c\t%c\t%c\n", operator, reg, newexp[newlen], expression[i+1]);
			i+=2;
			newexp[newlen] = reg;
			reg--;
		}
		else{
			newexp[++newlen] = expression[i];
			i++;
		}	
	}
	newexp[++newlen]='\0';
	strcpy(expression, newexp);
}

void generate_code_for_expression(){
	reg = 'z';

	generate_code_for_operator('/');
	generate_code_for_operator('*');
	generate_code_for_operator('+');
	generate_code_for_operator('-');
	generate_code_for_operator('=');
}

void main(){
	printf("Enter expression: ");
	scanf("%s", expression);

	generate_code_for_expression();
}