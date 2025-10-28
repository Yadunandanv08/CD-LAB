#include<stdio.h>

typedef struct{
	int from;
	char sym;
	int to;
}Transition;

Transition transitions[10];
int closure[10][10], closurecount[10], statecount, transitioncount;

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
		if(transitions[i].from == curstate && transitions[i].sym == 'e'){
			eclosure(state, transitions[i].to);
		}
	}
}

void main(){
	printf("Enter number of states: ");
	scanf("%d", &statecount);
	printf("Enter number of transitions: ");
	scanf("%d", &transitioncount);

	FILE *f = fopen("test.txt", "r");
	for(int i=0;i<transitioncount;i++)
		fscanf(f, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);

	for(int i=0;i<statecount;i++)
		closurecount[i] = 0;

	for(int i=0;i<statecount;i++){
		eclosure(i, i);
		printf("E-Closure of state q%d: {", i);
		for(int j=0;j<closurecount[i];j++)
			printf("q%d ", closure[i][j]);
		printf("}\n");
	}	
}
