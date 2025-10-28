%{
    #include<stdio.h>    
    int words = 0, newlines = 0, spaces = 0;
%}

%option noyywrap

%%

[ ]     {spaces++;}
[\n]    {newlines++;}
[a-zA-Z]+   {words++;}

%%

int main(){
    printf("Enter input string: ");
    yylex();

    printf("words: %d\n", words);
    printf("newlines: %d\n", newlines);
    printf("spaces: %d\n", spaces);
    return 0;
}