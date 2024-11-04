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

void fusion_droite(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = ta -> m - 1; j > 0; j--){
            if(ta -> tab[i][j] == ta -> tab[i][j - 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i][j - 1] = 0;
            }
        }
    }
    deplacement_a_droite(ta);
}

void fusion_gauche(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m ; j++){
            if(ta -> tab[i][j] == ta -> tab[i][j + 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i][j + 1] = 0;
            }
        }
    }
    deplacement_a_gauche(ta);
}

void fusion_haut(tableau *ta){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == ta -> tab[i + 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i + 1][j] = 0;
            }
        }
    }
    deplacement_en_haut(ta);
}

void fusion_bas(tableau *ta){
    int i, j;
    for(i = ta -> n - 1; i > 0; i--){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == ta -> tab[i - 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i - 1][j] = 0;
            }
        }
    }
    deplacement_en_bas(ta);
}

/* la fonction va permettre la remise en place du tableau après une fusion (pour économiser de la place dans le main) */
void deplacement_et_fusion(tableau *ta, char dir){  
    switch(dir){
    case 'z':
        deplacement_en_haut(ta);
        fusion_haut(ta);
        deplacement_en_haut(ta);
        break;
    case 'q':
        deplacement_a_gauche(ta);
        fusion_gauche(ta);
        deplacement_a_gauche(ta);
        break;
    case 's':
        deplacement_en_bas(ta);
        fusion_bas(ta);
        deplacement_en_bas(ta);
        break;
    case 'd':
        deplacement_a_droite(ta);
        fusion_droite(ta);
        deplacement_a_droite(ta);
        break;
    }
}