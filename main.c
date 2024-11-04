#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"

int main(){
    int n = 4, m = 4, ok;
    tableau ta;
    cases c;
    char dir;

    srand(time(NULL));

    ta = initialisation_tableau(n, m);
    spawn_2_cases(&c, &ta);
    aff_tableau(ta);
    ok = 1;
    while(ok == 1){
        printf("Entrez une direction (z/q/s/d pour déplacer, a pour quitter): ");

        dir = getchar();
        while(getchar() != '\n');

        if(dir == 'a'){
            printf("Au revoir ! \n");
            ok = 0;
        }
        else if(dir == 'z' || dir == 'q' || dir == 's' || dir == 'd'){
            deplacement_et_fusion(&ta, dir);
            spawn_1_cases(&c, &ta);
            aff_tableau(ta);
        }
        else{
            printf("Mauvaise direction : entrez bien 'z', 'q', 's', ou 'd' \n");
        }
    }
    exit(EXIT_SUCCESS);
}
    