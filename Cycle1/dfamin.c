#include<stdio.h>

typedef struct{
    int from;
    char sym;
    int to;
} Transition;

int inarray(int arr[], int size, int val){
    for(int i=0;i<size;i++){
        if(arr[i]==val)
            return 1;
    }
    return 0;
}

int findsplit(int statesets[][10], int statesetcount[], int state, int splittablecount){
    for(int i=0;i<splittablecount;i++){
        for(int j=0;j<statesetcount[i];j++){
            if(statesets[i][j]==state)
                return i;
        }
    }
    return -1;
}

int splitidentical(int stategroupsmap[][10], int rows, int numsymbols, int statesets[][10], int statesetcount[], int splittablecount, int curstate){
    int groups[10][10], groupcounts[10], groupnum = 0;
    for(int i=0;i<10;i++)
        groupcounts[i]=0;

    groups[0][0] = 0;
    groupcounts[0] = 1;
    groupnum++;

    for(int i=1;i<rows;i++){
        int newgroupflag = 1;
        for(int j=0;j<groupnum;j++){
            int identical=1;
            for(int k=0;k<numsymbols;k++){
                if(stategroupsmap[i][k] != stategroupsmap[groups[j][0]][k]){
                    identical=0;
                    break;
                }
            }
            if(identical){
                groups[j][groupcounts[j]] = i;
                groupcounts[j]++;
                newgroupflag=0;
                break;
            }
        }
        if(newgroupflag){
            groups[groupnum][0] = i;
            groupcounts[groupnum] = 1;
            groupnum++;
        }
    }

    for(int i=0;i<statesetcount[curstate];i++)
        statesets[curstate][i] = -1;

    for(int i=0;i<groupcounts[0];i++)
        statesets[curstate][i] = groups[0][i];

    for(int i=1;i<groupnum;i++){
        for(int j=0;j<groupcounts[i];j++)
            statesets[splittablecount][j] = groups[i][j];
        statesetcount[splittablecount] = groupcounts[i];
        splittablecount++;
    }

    return splittablecount;
}

int main(){
    int numstates, numsymbols, numtransitions, numfinal, finalstates[10], statesets[10][10];
    int statesetcount[10], splittable[10], splittablecount;
    int stategroupsmap[10][10];
    char symbols[10];
    Transition transitions[20];
    FILE *f = fopen("test.txt", "r");

    printf("Enter number of states, symbols and transitions: ");
    scanf("%d %d %d", &numstates, &numsymbols, &numtransitions);

    printf("Enter the symbols:\n");
    for(int i=0;i<numsymbols;i++)
        scanf(" %c",&symbols[i]);

    for(int i=0;i<numtransitions;i++)
        fscanf(f,"%d %c %d",&transitions[i].from,&transitions[i].sym,&transitions[i].to);

    printf("Enter number of final states: ");
    scanf("%d",&numfinal);

    printf("Enter final states: ");
    for(int i=0;i<numfinal;i++)
        scanf("%d",&finalstates[i]);

    for(int i=0;i<numfinal;i++)
        statesets[0][i] = finalstates[i];
    statesetcount[0] = numfinal;

    int idx=0;
    for(int i=0;i<numstates;i++){
        if(!inarray(finalstates,numfinal,i))
            statesets[1][idx++] = i;
    }
    statesetcount[1] = idx;

    splittable[0] = splittable[1] = 1;
    for(int i=2;i<numstates;i++)
        splittable[i]=0;

    int curstate=0;
    splittablecount = 2;

    while(curstate<splittablecount){
        int rows = statesetcount[curstate];
        for(int i=0;i<rows;i++){
            for(int j=0;j<numsymbols;j++){
                int transitionfound=0;
                for(int k=0;k<numtransitions;k++){
                    if(transitions[k].from==statesets[curstate][i] && transitions[k].sym==symbols[j]){
                        stategroupsmap[i][j] = findsplit(statesets,statesetcount,transitions[k].to,splittablecount);
                        transitionfound=1;
                        break;
                    }
                }
                if(!transitionfound)
                    stategroupsmap[i][j] = -1;
            }
        }
        splittablecount = splitidentical(stategroupsmap, rows, numsymbols, statesets, statesetcount, splittablecount, curstate);
        curstate++;
    }

    printf("Minimized DFA groups:\n");
    for(int i=0;i<splittablecount;i++){
        printf("Group %d: ", i);
        for(int j=0;j<statesetcount[i];j++)
            printf("%d ", statesets[i][j]);
        printf("\n");
    }
}
