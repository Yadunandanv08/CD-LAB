%{
    #include<stdio.h>
%}

%option noyywrap

%%

abc   {printf("123");}    
.   {printf("%s", yytext);}

%%

int main(){
    printf("Enter input string: ");
    yylex();
    return 0;
}
