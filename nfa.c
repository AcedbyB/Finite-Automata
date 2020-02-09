#include<stdio.h>
#include<stdlib.h>
#include"Set.h"
#include"IntHashSet.c"
#include"nfa.h"

/* Begin setting up NFA*/

typedef struct NFA *NFA;

struct NFA {
    Set transitionBoard[400][400];
    bool accept[400];
    int nstates;
};

NFA new_NFA(int nstates) {
    NFA this = (struct NFA*)malloc(sizeof(struct NFA));
    if (this == NULL) {
        return NULL; 
    }
    this->nstates = nstates;
    for(int i =0; i < 300; i++) {
        for(int j =0; j<300;j++) this -> transitionBoard[i][j] = new_Set(100);
        this -> accept[i] = false;
    }
    return this;
}

void NFA_free(NFA nfa) {
    for(int i = 0;i<300;i++) {
        for(int j = 0; j<300;j++) Set_free(nfa -> transitionBoard[i][j]);
    }
    free(nfa);
}

int NFA_get_size(NFA nfa) {
    return nfa -> nstates;
}


Set NFA_get_transitions(NFA nfa, int state, char sym) {
    return nfa -> transitionBoard[state][(int)sym];
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst) {
    Set_insert(nfa -> transitionBoard[src][(int)sym], dst);
}

void NFA_add_transition_all(NFA nfa, int src, int dst) {
    for(int i = 1; i < 128; i++ ) {
        Set_insert(nfa -> transitionBoard[src][i], dst);
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value) {
    nfa -> accept[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state) {
    return nfa -> accept[state];
}

bool NFA_execute(NFA nfa, char *input) {
    Set curStates = new_Set(100);
    Set_insert(curStates, 0);
    for (char *i = input; *i; i++) {
        Set temp = new_Set(100);
        SetIterator cak = Set_iterator(curStates);
        while(SetIterator_hasNext(cak)) {
            int next =  SetIterator_next(cak);
            if(nfa -> transitionBoard[next][(int)*i] == NULL) continue;
            else Set_union(temp, nfa -> transitionBoard[next][(int)*i]);
        }
        Set_free(curStates);
        curStates = NULL;
        curStates = new_Set(100);
        free(cak);
        cak = NULL;
        cak = Set_iterator(temp);
        while(SetIterator_hasNext(cak)) {
            int next =  SetIterator_next(cak);
            Set_insert(curStates,next);
        }
        Set_free(temp);
        temp = NULL;
        free(cak);
    }
    bool flag = false;
    SetIterator cak = Set_iterator(curStates);
    while(SetIterator_hasNext(cak)) {
        int next =  SetIterator_next(cak);
        if(nfa -> accept[next]) flag =true;
    }
    free(cak);
    Set_free(curStates);
    return flag;
}

void unlimitedRunningInputNFA(NFA nfa) {
    char input[500];
    printf("%s", "Type in a string or type exit to exit: ");
    scanf("%s", input);
    while(strcmp(input,"exit")) {
        if(NFA_execute(nfa, input)) printf("%s\n", "True");
        else printf("%s\n", "False");
        printf("%s", "Type in a string or type exit to exit: ");
        scanf("%s", input);
    }
    printf("\n");
}

/**
 * Print the given NFA to System.out.
 */
extern void NFA_print(NFA nfa);

/*Done setting up NFA */

NFA EmbEndingNFA() {
    NFA nfa = new_NFA(100);
    nfa -> accept[3] = 1;
    nfa -> nstates = 4;
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'e', 1);
    NFA_add_transition(nfa, 1, 'm', 2);
    NFA_add_transition(nfa, 2, 'b', 3);
    return nfa;
}

NFA ContainsEmbNFA() {
    NFA nfa = new_NFA(100);
    nfa -> accept[3] = 1;
    nfa -> nstates = 4;
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'e', 1);
    NFA_add_transition(nfa, 1, 'm', 2);
    NFA_add_transition(nfa, 2, 'b', 3);
    NFA_add_transition_all(nfa, 3, 3);
    return nfa;
}

void TestEmbEndingNFA() {
    printf("%s\n", "Testing emb ending NFA right now:");
    NFA nfa = EmbEndingNFA();
    unlimitedRunningInputNFA(nfa);
    NFA_free(nfa);
}

void TestEmbContainsNFA() {
    printf("%s\n", "Testing contains emb NFA right now:");
    NFA nfa = ContainsEmbNFA();
    unlimitedRunningInputNFA(nfa);
    NFA_free(nfa);
}

void TestNotWashingtonNFA() {
    printf("%s\n", "Testing not washington NFA right now:");
    NFA nfa = new_NFA(100);
    for(int i = 2; i<= 19;i++) {
        if((i < 10 && i%2 == 0) || (i>10&& i%2==1)) {
            nfa -> accept[i] = 1;
            NFA_add_transition_all(nfa,i,i);
        }
    }
    NFA_add_transition_all(nfa, 0, 0);
    for(int i = 1; i<= 18;i++) {
        if((i < 10 && i%2==1) || (i>10&& i%2==0))  NFA_add_transition_all(nfa,i,i);
    }
    NFA_add_transition(nfa, 0, 'a', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition(nfa, 0, 'g', 3);
    NFA_add_transition(nfa, 3, 'g', 4);
    NFA_add_transition(nfa, 0, 'h', 5);
    NFA_add_transition(nfa, 5, 'h', 6);
    NFA_add_transition(nfa, 0, 'i', 7);
    NFA_add_transition(nfa, 7, 'i', 8);
    NFA_add_transition(nfa, 0, 'n', 9);
    NFA_add_transition(nfa, 9, 'n', 10);
    NFA_add_transition(nfa, 10, 'n', 11);
    NFA_add_transition(nfa, 0, 'o', 12);
    NFA_add_transition(nfa, 12, 'o', 13);
    NFA_add_transition(nfa, 0, 's', 14);
    NFA_add_transition(nfa, 14, 's', 15);
    NFA_add_transition(nfa, 0, 't', 16);
    NFA_add_transition(nfa, 16, 't', 17);
    NFA_add_transition(nfa, 0, 'w', 18);
    NFA_add_transition(nfa, 18, 'w', 19);
    unlimitedRunningInputNFA(nfa);
    NFA_free(nfa);
}

void TestILove173NFA() {
    printf("%s\n", "Testing contains ilove173 NFA right now:");
    NFA nfa = new_NFA(100);
    nfa -> accept[8] = 1;
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'i', 1);
    NFA_add_transition(nfa, 1, 'l', 2);
    NFA_add_transition(nfa, 2, 'o', 3);
    NFA_add_transition(nfa, 3, 'v', 4);
    NFA_add_transition(nfa, 4, 'e', 5);
    NFA_add_transition(nfa, 5, '1', 6);
    NFA_add_transition(nfa, 6, '7', 7);
    NFA_add_transition(nfa, 7, '3', 8);
    NFA_add_transition_all(nfa, 8, 8);
    unlimitedRunningInputNFA(nfa);
    NFA_free(nfa);
}

