#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "cases.h"
#include "tableau.h"
#include "jeu.h"

int charg_ms(char *nom, joueur *j){

    FILE *f;
    
    if((f = fopen(nom, "r")) == NULL){
        printf("Erreur ouverture f \n");
        return -1;
    }

    if(fscanf(f, "%d", &j -> score) != 1){
        printf("Erreur : lecture score \n");
        fclose(f);
        return -1;
    }
    
    fclose(f);
    return 1;
}

int save_ms(char *nom, joueur *j){

    FILE *f;
    
    if((f = fopen(nom, "w")) == NULL){
        return -1;
    }

    fprintf(f, "%d", j -> score);

    fclose(f);
    return 1;
}

/* void compte_score(joueur *j){ */
/*     int score_t = 0; */
/*     j -> score += score_t; */
/* } */