#include<stdio.h>

typedef struct {
    int from;
    char sym;
    int to;
} Transition;

void sort(int arr[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int check_duplicate(int arr1[], int arr2[], int s1, int s2){
    sort(arr1, s1);
    sort(arr2, s2);
    if(s1 != s2) return 0;
    for(int i = 0; i < s1; i++){
        if(arr1[i] != arr2[i]) return 0;
    }
    return 1;
}

int ifexists(int array[10], int value, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == value) return 1;
    }
    return 0;
}

void main(){
    int numstates, numsyms, states, numtrans, start, numfinal, finalstates[10], newstates[10][10], numnewstates, statesinnew[10];
    char symbols[10];
    Transition transitions[10];

    printf("Enter number of states: ");
    scanf("%d", &numstates);
    printf("Enter number of symbols: ");
    scanf("%d", &numsyms);
    printf("Enter symbols: ");
    for(int i = 0; i < numsyms; i++){
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &numtrans);
    printf("Enter transitions (from symbol to):\n");
    FILE *f = fopen("test.txt", "r");
    for(int i = 0; i < numtrans; i++){
        fscanf(f, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);
    }

    printf("Enter start state: ");
    scanf("%d", &start);    
    printf("Enter number of final states: ");
    scanf("%d", &numfinal);
    printf("Enter final states: ");
    for(int i = 0; i < numfinal; i++){
        scanf("%d", &finalstates[i]);
    }

    printf("Start state: %d\n", start);

    newstates[0][0] = start;
    statesinnew[0] = 1;
    numnewstates = 1;
    int curstate = 0;

    while(curstate<numnewstates){
        for(int j=0;j<numsyms;j++){
            int result[10];
            int resultsize=0;
            for(int k=0;k<statesinnew[curstate];k++){
                for(int l=0;l<numtrans;l++){
                    if(newstates[curstate][k]==transitions[l].from && symbols[j]==transitions[l].sym){
                        int tostate = transitions[l].to;
                        int found=ifexists(result, tostate, resultsize);
                        if(!found){
                            result[resultsize++]=tostate;
                        }
                    }
                }
            }
            int duplicate=0;
            for(int m=0;m<numnewstates;m++){
                if(check_duplicate(result, newstates[m], resultsize, statesinnew[m])){
                    duplicate=1;
                    break;
                }
            }
            if(!duplicate && resultsize>0){
                for(int m=0;m<resultsize;m++){
                    newstates[numnewstates][m]=result[m];
                }
                statesinnew[numnewstates]=resultsize;
                numnewstates++;
            }
        }
        curstate++;
    }

    printf("New States:\n");
    for(int i=0;i<numnewstates;i++){
        printf("State %d: { ", i);
        for(int j=0;j<statesinnew[i];j++){
            printf("%d ", newstates[i][j]);
        }
        printf("}\n");
    }
}