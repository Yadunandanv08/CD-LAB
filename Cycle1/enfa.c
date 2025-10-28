#include<stdio.h>

typedef struct{
    int from;
    char sym;
    int to;
}Transition;

int closure[10][10], table[10][10][10], closurecount[10], transitioncount, symcount, numstates, tablecount[10][10];
Transition transitions[20];
char symbols[10];

int contains(int state, int closure[], int count){
    for(int i=0;i<count;i++)
        if(closure[i]==state)
            return 1;
    return 0;
}

void eclosure(int state, int curstate){
    if(!contains(curstate, closure[state], closurecount[state])){
        closure[state][closurecount[state]++] = curstate;
    }

    for(int i=0;i<transitioncount;i++){
        if(transitions[i].from == curstate && transitions[i].sym=='e'){
            eclosure(state, transitions[i].to);
        }
    }
}

void main(){
    printf("Enter number of states: ");
    scanf("%d", &numstates);
    printf("Enter number of symbols: ");
    scanf("%d", &symcount);
    printf("Enter symbols: ");
    for(int i=0;i<symcount;i++)
        scanf(" %c", &symbols[i]);
    printf("Enter number of transitions: ");
    scanf("%d", &transitioncount);

    FILE *f = fopen("test.txt", "r");
    for(int i=0;i<transitioncount;i++)
        fscanf(f, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);

    for(int i=0;i<numstates;i++)
        closurecount[i] = 0;
    for(int i=0;i<numstates;i++)
        eclosure(i, i);
    
    for(int i=0;i<numstates;i++){
        for(int j=0;j<symcount;j++){
            int finalres[10];
            int finalcount = 0;
            for(int k=0;k<closurecount[i];k++){
                int result[10];
                int rescount = 0;
                for(int l=0;l<transitioncount;l++){
                    if(transitions[l].from == closure[i][k] && transitions[l].sym == symbols[j]){
                        result[rescount++] = transitions[l].to;
                    }
                }

                for(int m=0;m<rescount;m++){
                    for(int n=0;n<closurecount[result[m]];n++){
                        if(!contains(closure[result[m]][n], finalres, finalcount)){
                            finalres[finalcount++] = closure[result[m]][n];
                        }
                    }
                }
                for(int m=0;m<finalcount;m++){
                    table[i][j][m] = finalres[m];
                }
                tablecount[i][j] = finalcount;
            }   
        }
    }


    printf("Final States:\n");
    for(int i=0;i<numstates;i++){
        for(int j=0;j<symcount;j++){
            printf("δ(q%d, %c) = { ", i, symbols[j]);
            for(int k=0;k<tablecount[i][j];k++){
                if(table[i][j][k]!=0 || k==0)
                    printf("%d ", table[i][j][k]);  
            }
            printf("}\n");
        }
    }
}




































































// #include<stdio.h>
// #include<string.h> 

// typedef struct{
// 	int from;
// 	char sym;
// 	int to;
// }Transition;

// int contains(int state, int closure[10], int count){
// 	for(int i=0;i<count;i++)
// 		if(closure[i]==state)
// 			return 1;
// 	return 0;
// }

// void eclosure(int state, int closure[10], int numtrans, int *count, Transition transitions[]){
// 	if(!contains(state, closure, *count)){
// 		closure[*count]=state;
// 		(*count)++;
// 	}
	
// 	for(int i=0;i<numtrans;i++)
// 		if(transitions[i].from == state && transitions[i].sym=='e')
// 			eclosure(transitions[i].to, closure, numtrans, count, transitions);	
// }

// void main(){
// 	int numstates, numtrans, closure[10][10], closurecounts[10], numsyms;
// 	Transition transitions[10];
//     char symbols[10];

//     int table[10][10][10], tablecounts[10][10];
	
// 	printf("Enter number of states: ");
// 	scanf("%d", &numstates);

//     printf("Enter number of symbols: ");
// 	scanf("%d", &numsyms);
//     printf("Enter symbols: ");
//     for(int i=0;i<numsyms;i++)
//         scanf(" %c", &symbols[i]);

// 	printf("\nEnter number of transitions: ");
// 	scanf("%d", &numtrans);
	
// 	FILE *f = fopen("test.txt", "r");
// 	for(int i=0;i<numtrans;i++)
// 		fscanf(f, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);
	
// 	for(int i=0;i<numstates;i++){
// 		int count = 0;
// 		eclosure(i, closure[i], numtrans, &count, transitions);
//         closurecounts[i] = count;   
// 	}

//     for(int i=0;i<numstates;i++)
//         for(int k=0;k<numsyms;k++){ 
//             int finalres[10] = {0};
//             int finalcount = 0;
//             for(int j=0;j<closurecounts[i];j++){
//                 int result[10] = {0};
//                 int rescount = 0;
//                 for(int l=0;l<numtrans;l++){
//                     if(transitions[l].from == closure[i][j] && transitions[l].sym == symbols[k])
//                         result[rescount++] = transitions[l].to;
//                 }
                
//                 for(int m=0;m<rescount;m++)
//                     eclosure(result[m], finalres, numtrans, &finalcount, transitions);
                
//                 for(int n=0;n<finalcount;n++)
//                     table[i][k][n] = finalres[n];
//                 tablecounts[i][k] = finalcount;
//             }
//         }
    
//     printf("Final States:\n");
//     for(int i=0;i<numstates;i++){
//         for(int j=0;j<numsyms;j++){
//             printf("δ(q%d, %c) = { ", i, symbols[j]);
//             for(int k=0;k<tablecounts[i][j];k++){
//                 if(table[i][j][k]!=0 || k==0)
//                     printf("%d ", table[i][j][k]);
//             }
//         printf("}\n");
//         }
//     }
// }
