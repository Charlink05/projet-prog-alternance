#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void aff_tableau(tableau ta){
    int i, j;
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){
            printf("| %d ", ta.tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

tableau initialisation_tableau(int n, int m){
    int i, j;
    tableau ta;
    ta.n = n;
    ta.m = m;
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){
            ta.tab[i][j] = 0;
        }
    }
    ta.cases_vides = n * m;
    return ta;
}