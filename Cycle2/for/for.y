%{
    #include<stdio.h>

    void yyerror(const char *s);
    int yylex(void);
%}


%token FOR LPAREN RPAREN GT LT EQ LTE GTE ASSIGN NUMBER ID INC DEC SEMICOLON

%%

input: FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN {printf("Valid\n");}

expr: NUMBER
    | expr relop expr
    | expr INC
    | expr DEC
    | ID
    ;

relop: EQ
     | LT
     | GT
     | GTE
     | LTE
     | ASSIGN
     ;


%%

void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}

int main(){
    printf("Enter loop: ");
    yyparse();
    return 0;
}