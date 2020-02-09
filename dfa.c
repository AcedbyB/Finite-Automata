#include<stdio.h>
#include"dfa.h"
#include<stdlib.h>

/* Begin setting up DFA*/

typedef struct DFA* DFA;

struct DFA {
    int transitionBoard[500][500];
    bool accept[500];
    int nstates;
};

DFA new_DFA(int nstates) {
    DFA this = (struct DFA*)malloc(sizeof(struct DFA));
    if (this == NULL) {
        return NULL; 
    }
    this->nstates = nstates;
    for(int i = 0; i < 499 ;i++) this -> accept[i] = false;
    return this;
}

void DFA_free(DFA this) {
    free(this);
}

int DFA_get_size(DFA this) {
    return this -> nstates;
}

int DFA_get_transition(DFA dfa, int src, char sym) {
    return dfa -> transitionBoard[src][(int)sym];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    dfa ->transitionBoard[src][(int)sym] = dst;
}

void DFA_set_transition_all(DFA dfa, int src, int dst) {
    for(int i = 1; i < 128; i++ ) {
        dfa -> transitionBoard[src][i] = dst;
    }
}

void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa -> accept[state] = value;
}

bool DFA_get_accepting(DFA dfa, int state) {
    return dfa -> accept[state];
}

bool DFA_execute(DFA dfa, char *input) {
    int curState = 0;
    for (char *i = input; *i; i++) {
        curState = DFA_get_transition(dfa, curState, *i);
    }
    return dfa -> accept[curState];
}

void unlimitedRunningInput(DFA dfa) {
    char input[500] = "hey";
    char compare[500] = "exit";
    printf("%s", "Type in a string or type exit to exit: ");
    scanf("%s", input);
    while(strcmp(input,compare)) {
        int cur = DFA_execute(dfa, input);
        if(cur == 1) printf("%s\n", "True");
        else printf("%s\n", "False");
        printf("%s", "Type in a string or type exit to exit: ");
        scanf("%s", input);
    }
    printf("\n");
}


void TestComputerDFA() {
    printf("%s\n", "Testing computer DFA right now:");
    DFA dfa = new_DFA(100);
    dfa -> accept[8] = 1;
    for(int i = 0; i <=8; i++) DFA_set_transition_all(dfa, i, 404);
    DFA_set_transition_all(dfa, 404, 404);
    char str[] = "computer";
    for(int i = 0; i < 8; i++) DFA_set_transition(dfa, i, str[i], i+1);
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}

void TestRoflDFA() {
    printf("%s\n", "Testing begins with rofl DFA right now:");
    DFA dfa = new_DFA(100);
    dfa -> accept[4] = 1;
    for(int i = 0; i <= 3; i++) DFA_set_transition_all(dfa, i, 404);
    DFA_set_transition_all(dfa, 4, 4);
    DFA_set_transition_all(dfa, 404, 404);
    char str[] = "rofl";
    for(int i = 0; i < 4; i++) DFA_set_transition(dfa, i, str[i], i+1);
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}

void TestOddZerosDFA() {
    printf("%s\n", "Testing Odd Zeros DFA right now:");
    DFA dfa = new_DFA(100);
    dfa -> accept[1] = 1;
    DFA_set_transition_all(dfa, 0, 404);
    DFA_set_transition_all(dfa, 1, 404);
    DFA_set_transition_all(dfa, 404, 404);
    DFA_set_transition(dfa, 0, '0', 1);
    DFA_set_transition(dfa, 1, '0', 0);
    DFA_set_transition(dfa, 1, '1', 1);
    DFA_set_transition(dfa, 0, '1', 0);
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}

void TestOddZerosAndOnesDFA() {
    printf("%s\n", "Testing Odd Zeros and Ones DFA right now:");
    DFA dfa = new_DFA(100);
    dfa -> accept[3] = 1;
    for(int i = 0; i <= 4; i++) DFA_set_transition_all(dfa, i, 404);
    DFA_set_transition_all(dfa, 404, 404);
    DFA_set_transition(dfa, 0, '0', 1);
    DFA_set_transition(dfa, 0, '1', 2);
    DFA_set_transition(dfa, 1, '0', 0);
    DFA_set_transition(dfa, 1, '1', 3);
    DFA_set_transition(dfa, 2, '1', 0);
    DFA_set_transition(dfa, 2, '0', 3);
    DFA_set_transition(dfa, 3, '1', 1);
    DFA_set_transition(dfa, 3, '0', 2);
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}

void TestILove173() {
    printf("%s\n", "Testing begins with ilove173 DFA right now:");
    DFA dfa = new_DFA(100);
    dfa -> accept[8] = 1;
    for(int i = 0; i < 8; i++) DFA_set_transition_all(dfa, i, 404);
    DFA_set_transition_all(dfa, 404, 404);
    char str[] = "ilove173";
    for(int i = 0; i < 8; i++) DFA_set_transition(dfa, i, str[i], i+1);
    DFA_set_transition_all(dfa, 8, 8);
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}