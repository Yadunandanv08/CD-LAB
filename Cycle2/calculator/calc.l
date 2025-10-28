%{
    #include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+  {yylval = atoi(yytext); return NUMBER;}
[ \t\n]     { /* ignore whitespace */ }
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"^" {return POW;}
"%" {return PERC;}
"(" {return LPAREN;}
")" {return RPAREN;}
.   {return yytext[0];}

%%
