#include<stdio.h>
#include<stdlib.h>
#include"dfa.c"
#include"nfa.c"
#include"Set.h"

DFA convertNFAtoDFA(NFA nfa) {
    DFA dfa = new_DFA(500);
    int curStateIndex = 0;
    int nextPosition = 1;
    Set State[500];
    State[0] = new_Set(100);
    Set_insert(State[0], 0);
    while(curStateIndex < nextPosition) {
        //printf("\n%d\n", curStateIndex);
        for(int i = 1; i < 119; i++) {
            SetIterator cak = Set_iterator(State[curStateIndex]);
            Set tmp = new_Set(100);
            while(SetIterator_hasNext(cak)) {
                int lul =  SetIterator_next(cak);
                if(nfa -> transitionBoard[lul][i] != NULL) {
                    // printf("lol");
                    Set_union(tmp, nfa -> transitionBoard[lul][i]);
                }
            }
            // printf("%d %d \n", i, curStateIndex);
            int pos = -1;
            for(int i = 0; i <= curStateIndex; i++) {
                if(Set_equals(tmp, State[i]) == true) {
                    pos = i;
                    break;
                }
            }
            if(pos == -1)  {
                //printf("%d", nextPosition);
                State[nextPosition] = new_Set(100);
                Set_union(State[nextPosition], tmp);
                DFA_set_transition(dfa, curStateIndex, (char)i,nextPosition);
                nextPosition++;
            } 
            else {
                //printf("%d\n", pos);
                DFA_set_transition(dfa, curStateIndex, (char)i, pos);
            }
            Set_free(tmp);
        }
        curStateIndex++;
    }
    dfa -> nstates = curStateIndex;
    for(int i = 0; i < curStateIndex; i++) {
        SetIterator cak = Set_iterator(State[i]);
        while(SetIterator_hasNext(cak)) {
            int next =  SetIterator_next(cak);
            if(nfa -> accept[next] == 1) dfa -> accept[i] = 1;
        }
        Set_free(State[i]);
    }
    return dfa;
}

void main() {
    printf("%s\n \n","");
    printf("%s\n \n", "CSC173 Project 1 by Bao Tran");
    // Testing DFA;
    TestComputerDFA();
    TestRoflDFA();
    TestOddZerosDFA();
    TestOddZerosAndOnesDFA();
    // this is my part: starts with ilove173 dfa
    TestILove173();

    // Testing NFA;
    TestEmbEndingNFA();
    TestEmbContainsNFA();
    TestNotWashingtonNFA();
    // this is my part: contains ilove173 nfa;
    TestILove173NFA();

    //Converting NFA to DFA;
    printf("%s\n", "Currently converting emb ending NFA to a DFA");
    DFA dfa = convertNFAtoDFA(EmbEndingNFA());
    printf("%s\n", "Done!");
    printf("%s\n", "Start testing it:");
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
    dfa = NULL;

    printf("%s\n", "Currently converting contains emb NFA to a DFA");
    dfa = convertNFAtoDFA(ContainsEmbNFA());
    printf("%s\n", "Done!");
    printf("%s\n", "Start testing it:");
    unlimitedRunningInput(dfa);
    DFA_free(dfa);
}