%{
    #include<stdio.h>
    #include<math.h> 

    void yyerror(const char *s);
    int yylex(void);   
%}

%token PLUS MINUS MUL DIV PERC LPAREN RPAREN POW NUMBER
%%

input:  /*empty*/
     |  input expr {printf("Result = %d", $2);}
     ;

expr:   NUMBER
    |   LPAREN expr RPAREN  {$$ = $2;}
    |   expr PLUS expr  {$$ = $1+$3;}
    |   expr MINUS expr {$$ = $1-$3;}
    |   expr MUL expr   {$$ = $1*$3;}
    |   expr DIV expr   {$$ = $1/$3;}
    |   expr POW expr   {$$ = pow($1, $3);}
    |   expr PERC expr  {$$ = ($1/$3)*100;}
    ;

%%

void yyerror(const char *s){
    fprintf(stderr, "Error %s\n", s);
}

int main(){
    printf("Enter expression: ");
    yyparse();
    return 0;
}
