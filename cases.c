#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"

void aff_cases(cases *c){
    printf("la couleur : %d, le x : %d et le y : %d \n", c -> couleur, c -> x, c -> y);
}

void initialisation(cases *c){
    /* la couleur se fera selon le score qui va apparaître lors du spawn des pièces, soit 2 soit 4 */
    c -> couleur = (rand()%2)+1;
    c -> x = 0;
    c -> y = 0;
}

/* pour l'apparition des 2 premières cases au début du jeu (sera appelé qu'une fois) */
void spawn_2_cases(cases *c, tableau *ta){
    float chance;
    int k, i, j, bonne_pos;
    k = 0;
    while(k < 2){
        bonne_pos = 0; /*vérifie si la case est bien de 0 (vide) sinon recommence sur une autre */
        while(bonne_pos == 0){
            i = rand() % ta -> n;
            j = rand() % ta -> m;
            
            if(ta -> tab[i][j] == 0){
                bonne_pos = 1;
            }
        }

        chance = (float)rand()/RAND_MAX;
        if(chance < 0.9){
            c -> couleur = 2;
        }
        else{
            c -> couleur = 4;
        }
        
        ta -> tab[i][j] = c -> couleur;
        printf("La case %d apparait en (%d, %d) avec la valeur : %d \n", k + 1, i, j, c -> couleur);
        k++;
    }
}


/* pour l'appararition d'une case après un déplacement */ 
void spawn_1_cases(cases *c, tableau *ta){ 
    float chance;
    int i, j, bonne_pos;
    bonne_pos = 0; /*vérifie si la case est bien de 0 (vide) sinon recommence sur une autre */
    while(bonne_pos == 0){
        i = rand() % ta -> n;
        j = rand() % ta -> m;

        if(ta -> tab[i][j] == 0){
            bonne_pos = 1;
        }
    }

    chance = (float)rand()/RAND_MAX;
    if(chance < 0.9){
        c -> couleur = 2;
    }
    else{
        c -> couleur = 4;
    }
        
    ta -> tab[i][j] = c -> couleur;
}

void deplacement_a_droite(tableau *ta){
    int i, j, k;
    for(i = 0; i < ta -> n; i++){
        for(j = ta -> m - 1; j >= 0; j--){
            k = j;
            if(ta -> tab[i][j] != 0){
                while(k + 1 < ta-> m  && ta -> tab[i][k + 1] == 0){ /* on regarde si case de droite = 0 */
                    ta -> tab[i][k + 1] = ta -> tab[i][k]; /* la case de droite devient la case d'avant (déplacement à droite) */
                    ta -> tab[i][k] = 0; /* initialisation de l'ancienne case à 0 */
                    k++;
                }
            }
        }
    }
}

void deplacement_a_gauche(tableau *ta){
    int i, j, k;
    for(i = 0; i < ta -> n; i++){
        for(j = 1; j < ta -> m ; j++){
            k = j;
            if(ta -> tab[i][j] != 0){
                while(k - 1 >= 0 && ta -> tab[i][k - 1] == 0){ /* on regarde si case de gauche = 0 */
                    ta -> tab[i][k - 1] = ta -> tab[i][k]; /* la case de gauche devient la case d'avant (déplacement à gauche) */
                    ta -> tab[i][k] = 0; /* initialisation de l'ancienne case à 0 */
                    k--;
                }
            }
        }
    }
}

void deplacement_en_bas(tableau *ta){
    int i, j, k;
    for(i = ta -> n - 1; i >= 0; i--){
        for(j = 0; j < ta -> m; j++){
            k = i;
            if(ta -> tab[i][j] != 0){
                while(k + 1 < ta -> n && ta -> tab[k + 1][j] == 0){
                    ta -> tab[k + 1][j] = ta -> tab[k][j];
                    ta -> tab[k][j] = 0;
                    k++;
                }
            }
        }
    }
}

void deplacement_en_haut(tableau *ta){
    int i, j, k;
    for(i = 1; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            k = i;
            if(ta -> tab[i][j] != 0){
                while(k - 1 >= 0 && ta -> tab[k - 1][j] == 0){
                    ta -> tab[k - 1][j] = ta -> tab[k][j];
                    ta -> tab[k][j] = 0;
                    k--;
                }
            }
        }
    }
}

void deplacement(tableau *ta, char dir){ /* pour les déplacement sur le terminal, on verra le MLV après */
    switch(dir){
    case 'z':
        deplacement_en_haut(ta);
        break;
    case 'q':
        deplacement_a_gauche(ta);
        break;
    case 's':
        deplacement_en_bas(ta);
        break;
    case 'd':
        deplacement_a_droite(ta);
        break;
    }
}

int fusion_droite(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    for(i = 0; i < ta -> n; i++){
        for(j = ta -> m - 1; j > 0; j--){
            if(ta -> tab[i][j] == ta -> tab[i][j - 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i][j - 1] = 0;
                nb_fusion += 1;
            }
        }
    }
    /* deplacement_a_droite(ta); */
    return nb_fusion;
}

int fusion_gauche(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m ; j++){
            if(ta -> tab[i][j] == ta -> tab[i][j + 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i][j + 1] = 0;
                nb_fusion += 1;
            }
        }
    }
    /* deplacement_a_gauche(ta); */
    return nb_fusion;
}

int fusion_haut(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0; 
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == ta -> tab[i + 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i + 1][j] = 0;
                nb_fusion += 1;
            }
        }
    }
    /* deplacement_en_haut(ta); */
    return nb_fusion;
}

int fusion_bas(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    for(i = ta -> n - 1; i > 0; i--){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == ta -> tab[i - 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i - 1][j] = 0;
                nb_fusion += 1;
            }
        }
    }
    /* deplacement_en_bas(ta); */
    return nb_fusion;
}


int compter_fusions_droite(tableau *ta) {
    int i, j, nb_fusion = 0;
    for (i = 0; i < N; i++) {
        for (j = N - 1; j > 0; j--) {
            if (ta->tab[i][j] == ta->tab[i][j - 1] && ta->tab[i][j] != 0) {
                nb_fusion++;
            }
        }
    }
    return nb_fusion;
}

int compter_fusions_gauche(tableau *ta){
    int i, j, nb_fusion = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N - 1; j++){
            if (ta->tab[i][j] == ta->tab[i][j + 1] && ta->tab[i][j] != 0) {
                nb_fusion++;
            }
        }
    }
    return nb_fusion;
}

int compter_fusions_haut(tableau *ta) {
    int i, j, nb_fusion = 0;
    for (j = 0; j < N; j++) {
        for (i = 0; i < N - 1; i++) {
            if (ta->tab[i][j] == ta->tab[i + 1][j] && ta->tab[i][j] != 0) {
                nb_fusion++;
            }
        }
    }
    return nb_fusion;
}

int compter_fusions_bas(tableau *ta) {
    int i, j, nb_fusion = 0;
    for (j = 0; j < N; j++) {
        for (i = N - 1; i > 0; i--) { 
            if (ta->tab[i][j] == ta->tab[i - 1][j] && ta->tab[i][j] != 0) {
                nb_fusion++;
            }
        }
    }
    return nb_fusion;
}


/* la fonction va permettre la remise en place du tableau après une fusion (pour économiser de la place dans le main) */
/* int deplacement_et_fusion(tableau *ta, char dir){ */
/*     int nb_fusion; */
/*     nb_fusion = 0; */
/*     switch(dir){ */
/*     case 'z': */
/*         deplacement_en_haut(ta); */
/*         nb_fusion = fusion_haut(ta); */
/*         deplacement_en_haut(ta); */
/*         break; */
/*     case 'q': */
/*         deplacement_a_gauche(ta); */
/*         nb_fusion = fusion_gauche(ta); */
/*         deplacement_a_gauche(ta); */
/*         break; */
/*     case 's': */
/*         deplacement_en_bas(ta); */
/*         nb_fusion = fusion_bas(ta); */
/*         deplacement_en_bas(ta); */
/*         break; */
/*     case 'd': */
/*         deplacement_a_droite(ta); */
/*         nb_fusion =fusion_droite(ta); */
/*         deplacement_a_droite(ta); */
/*         break; */
/*     } 
    return nb_fusion;
    } */

/* permet d'enregistrer dans un tableau le tableau tab de base(de jeu) */
void sauvegarde_tableau(tableau *ta, tableau *prec){
    int i, j;
    prec -> n = ta -> n;
    prec -> m = ta -> m;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            prec -> tab[i][j] = ta -> tab[i][j];
        }
    }
}

/* permet de définir le tableau de jeu comme étant le tableau enregistré avant (donc le précédent) */
void retour_arriere(tableau *ta, tableau *prec){
    int i, j;
    ta -> n = prec -> n;
    ta -> m = prec -> m;
    for(i = 0; i < prec -> n; i++){
        for(j = 0; j < prec -> m; j++){
            ta -> tab[i][j] = prec -> tab[i][j];
        }
    }
}

int peux_bouger_droite(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = ta -> m - 1; j >= 0; j--){
            if(ta -> tab[i][j] != 0){
                if(ta -> tab[i][j + 1] == 0 || ta -> tab[i][j + 1] == ta -> tab[i][j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int peux_bouger_gauche(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 1; j < ta -> m; j++){
            if(ta -> tab[i][j] != 0){
                if(ta -> tab[i][j - 1] == 0 || ta -> tab[i][j - 1] == ta -> tab[i][j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int peux_bouger_bas(tableau *ta){
    int i, j;
    for(j = 0; j < ta -> m; j++){
        for(i = ta -> n - 1; i >= 0; i--){
            if(ta -> tab[i][j] != 0){
                if(ta -> tab[i + 1][j] == 0 || ta -> tab[i + 1][j] == ta -> tab[i][j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int peux_bouger_haut(tableau *ta){
    int i, j;
    for(j = 0; j < ta -> m; j++){
        for(i = 1; i < ta -> n; i++){
            if(ta -> tab[i][j] != 0){
                if(ta -> tab[i - 1][j] == 0 || ta -> tab[i - 1][j] == ta -> tab[i][j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}
         
        
         
                

int peux_bouger(tableau *ta, tableau *ta2){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] != ta2 -> tab[i][j]){
                return 0;
            }                
        }
    }
    return 1;
}

int check_game_over(tableau *ta) {
    int i, j;
    for (i = 0; i < ta->n; i++) {
        for (j = 0; j < ta->m; j++) {
            if (ta-> tab[i][j] == 0) {
                return 0;
            }
            if ((i < ta->n - 1 && ta->tab[i][j] == ta->tab[i+1][j]) || 
                (j < ta->m - 1 && ta->tab[i][j] == ta->tab[i][j+1])) {
                return 0;
            }
        }
    }
    return 1;
}

int check_victoire(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == 2048){
                printf("Bravo vous avez gagné ! \n");
                return 0;
            }
        }
    }
    return 1;
}