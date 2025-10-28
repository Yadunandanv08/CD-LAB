#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char keywords[][10] = {"if", "else", "while", "return", "int", "float", "void"};
char operators[] = "+-*/=";
char delimiters[] = ",;(){}[]";
int num_keywords = 7, num_operators = 6, num_delimiters = 12;

int iskeyword(char str[]){
    for(int i=0; i<num_keywords; i++){
        if(strcmp(str, keywords[i])==0)
            return 1;
    }
    return 0;
}

int isoperator(char ch){
    for(int i=0; i<num_operators; i++){
        if(ch == operators[i])
            return 1;
    }
    return 0;
}

int isdelimiter(char ch){
    for(int i=0; i<num_delimiters; i++){
        if(ch == delimiters[i])
            return 1;
    }
    return 0;
}

void main(){
    FILE *f = fopen("test.txt", "r");
    char ch, str[100];
    int i=0;

    while((ch=fgetc(f))!=EOF){
        if(isalpha((ch))){
            str[i++] = ch;
            while((ch=fgetc(f))!=EOF && (isalnum(ch))){
                str[i++] = ch;
            }
            ungetc(ch, f);
            str[i] = '\0';
            i=0;
            if(iskeyword(str)){
                printf("%s : keyword\n", str);
            } else {
                printf("%s : identifier\n", str);
            }
        }
        else if(isdigit(ch)){
            str[i++] = ch;
            while((ch=fgetc(f))!=EOF && isdigit(ch)){
                str[i++] = ch;
            }
            ungetc(ch, f);
            str[i] = '\0';
            i=0;
            printf("%s : number\n", str);
        }
        else if(isoperator(ch)){
            printf("%c : operator\n", ch);
        }
        else if(isdelimiter(ch)){
            printf("%c : delimiter\n", ch);
        }
        else if(isspace(ch)){
            continue;
        }
    }
}
