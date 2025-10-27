#include<stdio.h>

typedef struct{
	int from;
	char sym;
	int to;
}Transition;

int contains(int state, int list[10], int count){
	for(int i = 0;i < count; i++)
		if (list[i]==state)
			return 1;
	return 0;
}

void eclosure(int state, int closure[10], int *count, int transitioncount, Transition transitions[]){
	if (contains(state, closure, *count)==0){		
		closure[*count] = state;
		(*count)++;	
	}
 
	for(int i = 0;i < transitioncount; i++){
		if(transitions[i].from == state && transitions[i].sym == 'e'){
			eclosure(transitions[i].to, closure, count, transitioncount, transitions);
		}
	}
}

void main(){
	int statecount, transitioncount, states[10];
	Transition transitions[10];
	int closure[10][10];
    FILE *fp = fopen("test.txt", "r");
	
	printf("Enter number of states: ");
	scanf("%d", &statecount);
	
	printf("Enter number of transitions:");
	scanf("%d", &transitioncount);
	
	for(int i=0;i<transitioncount;i++)
		fscanf(fp, "%d %c %d", &transitions[i].from, &transitions[i].sym, &transitions[i].to);
		
	for(int i=0;i<statecount;i++){
		int count = 0;
		eclosure(i, closure[i], &count, transitioncount, transitions);
		printf("Closure of state q%d: ", i);
		for(int j=0;j<count;j++)
			printf("q%d\t", closure[i][j]);
		printf("\n");
	}
}
