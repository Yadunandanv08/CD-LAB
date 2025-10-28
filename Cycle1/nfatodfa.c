#include<stdio.h>

typedef struct{
	int from;
	char sym;
	int to;
}Transition;

void sort(int array[], int size){
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-i-1;j++){
			if(array[j]>array[j+1]){
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

int isduplicate(int arr1[], int arr2[], int size1, int size2){
	if(size1!=size2) return 0;
	sort(arr1, size1);
	sort(arr2, size2);
	for(int i=0;i<size1;i++)
		if(arr1[i]!=arr2[i]) return 0;
	return 1;
}

int alreadyexists(int array[], int value, int size){
    for(int i=0;i<size;i++){
        if(array[i]==value) return 1;
    }
    return 0;
}

int dfastates[10][10], statecount[10], curstate, numnewstates, numtrans, start, numfinal, finalstates[10], numsym;
char symbols[10];
Transition transitions[10];

void main(){

	printf("Enter number of symbols: ");
	scanf("%d", &numsym);
	
	printf("Enter symbols: ");
	scanf("%s", symbols);
	
	printf("Enter number of transitions: ");
	scanf("%d", &numtrans);
	
	printf("Enter start state: ");
	scanf("%d", &start);
	
	printf("Enter number of final states:: ");
	scanf("%d", &numfinal);
	
	printf("Enter final states:\n");
	for(int i=0;i<numfinal;i++) scanf("%d", &finalstates[i]);
	
	FILE *f = fopen("test.txt", "r");
	for(int i=0;i<numtrans;i++)
		fscanf(f, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);
	
	dfastates[0][0] = start;
	numnewstates=1;
	statecount[0]=1;
	curstate = 0;
	
	while(curstate<numnewstates){
		for(int i=0;i<numsym;i++){
			int result[10];
			int rescount = 0;
			for(int j=0;j<statecount[curstate];j++){
				for(int k=0;k<numtrans;k++){
					if(transitions[k].from == dfastates[curstate][j] && transitions[k].sym == symbols[i]){
                        if(!alreadyexists(result, transitions[k].to, rescount))
						    result[rescount++] = transitions[k].to;
					}
				}
			}
			
			int duplicate = 0;
			for(int l=0;l<numnewstates;l++){
				if(isduplicate(result, dfastates[l], rescount, statecount[l])){
					duplicate = 1;
					break;
				}
			}
			if(!duplicate && rescount>0){
				for(int l=0;l<rescount;l++){
					dfastates[numnewstates][l] = result[l];
				}
				statecount[numnewstates] = rescount;
				numnewstates++;
			}
			
		}
		curstate++;
	}
	printf("\nNew DFA States:");
	for(int i=0;i<numnewstates;i++){
		printf("[");
		for(int j=0;j<statecount[i];j++) printf("q%d", dfastates[i][j]);
		printf("]\n");
	}
}