#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void aff_tableau(tableau ta){
    int i, j;
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){
            printf("| ");
            printf("%d ", ta.tab[i][j]);
        }
        printf("\n");
    }
}

tableau initialisation_tableau(int n, int m){
    int i, j;
    tableau ta;
    ta.n = n;
    ta.m = m;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            ta.tab[i][j] = 0;
        }
    }
    return ta;
}