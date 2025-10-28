%{
    #include "y.tab.h"  
%}
%option noyywrap

%%

"for"   {return FOR;}
"("   {return LPAREN;}
")"   {return RPAREN;}
"<"   {return LT;}
">"   {return GT;}
"<="   {return LTE;}
">="   {return GTE;}
"="   {return ASSIGN;}
"=="   {return EQ;}
"++"   {return INC;}
"--"   {return DEC;}
";"   {return SEMICOLON;}
[0-9]   {return NUMBER;}
.    {return ID;}

%%




