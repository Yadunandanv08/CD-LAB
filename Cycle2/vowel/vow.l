%{
    #include<stdio.h>    
    int vow = 0, cons = 0;
%}

%option noyywrap

%%

[aeiouAEIOU]    {vow++;}
[A-Za-z]    {cons++;}
[\n]    {}
.   {}
%%

int main(){
    printf("Enter string: ");
    yylex();
    printf("Vowels: %d\n", vow);
    printf("Consonants: %d\n", cons);
    return 0;
}
