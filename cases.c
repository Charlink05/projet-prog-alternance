#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "tableau.h"

void aff_cases(cases *c){
    printf("le x : %d et le y : %d \n", c -> x, c -> y);
}

void initialisation_cases(cases *c){
    /* la couleur se fera selon le score qui va apparaître lors du spawn des pièces, soit 2 soit 4 */
    c -> x = 0;
    c -> y = 0;
    c -> valeur = 0;
}

/* pour l'apparition des 2 premières cases au début du jeu (sera appelé qu'une fois) */
void spawn_2_cases(tableau *ta, cases *c){
    float chance;
    int k, i, j, bonne_pos;
    k = 0;
    while(k < 2){
        bonne_pos = 0; /*vérifie si la case est bien de 0 (vide) sinon recommence sur une autre */
        while(bonne_pos == 0){
           
            i = rand() % N;
            j = rand() % N;
            
            if(ta -> tab[i][j] == 0){
                bonne_pos = 1;
            }
        }

        chance = (float)rand() / RAND_MAX;
        if(chance < 0.9){
            ta -> tab[i][j] = 2;
        }
        else{
            ta -> tab[i][j] = 4;
        }

        c -> x = i;
        c -> y = j;

        /* printf("La case %d apparait en (%d, %d) avec la valeur : %d \n", k + 1, i, j,  ta -> tab[i][j]); */
        k++;
    }
    /* aff_tableau(*ta); */
}


/* pour l'appararition d'une case après un déplacement */ 
void spawn_1_cases(tableau *ta, cases *c){ 
    float chance;
    int i, j, bonne_pos;
    bonne_pos = 0; /*vérifie si la case est bien de 0 (vide) sinon recommence sur une autre */
    while(bonne_pos == 0){
        i = rand() % N;
        j = rand() % N;

        if(ta -> tab[i][j] == 0){
            bonne_pos = 1;
        }
    }

    chance = (float)rand()/RAND_MAX;
    if(chance < 0.9){
        ta -> tab[i][j] = 2;
    }
    else{
        ta -> tab[i][j] = 4;
    }

    c -> x = i;
    c -> y = j;

}

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


void deplacement_a_droite(tableau *ta) {
    int i, j, k;
    if((MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)){
        for (i = 0; i < ta -> n; i++) {
            for (j = ta -> m - 1; j >= 0; j--) {
                if (ta -> tab[i][j] != 0) {
                    k = j;
                    while (k < ta -> m - 1 && ta -> tab[i][k + 1] == 0) {
                        ta -> tab[i][k + 1] = ta -> tab[i][k];
                        ta -> tab[i][k] = 0;
                        k++;
                    }
                }
            }
        }
    }
}

     
void deplacement_a_gauche(tableau *ta){
    int i, j, k;
    if((MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)){
        for(i = 0; i < ta -> n; i++){
            for(j = 1; j < ta -> m ; j++){
                k = j;
                if(ta -> tab[i][j] != 0){
                    while(k > 0 && ta -> tab[i][k - 1] == 0){ /* on regarde si case de gauche = 0 */
                        ta -> tab[i][k - 1] = ta -> tab[i][k]; /* la case de gauche devient la case d'avant (déplacement à gauche) */
                        ta -> tab[i][k] = 0; /* initialisation de l'ancienne case à 0 */
                        k--;
                    }
                }
            }
        }
    }
}

void deplacement_en_bas(tableau *ta){
    int i, j, k;
    if((MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)){
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
}

void deplacement_en_haut(tableau *ta){
    int i, j, k;
    if((MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)){
        for(i = 0; i < ta -> n; i++){
            for(j = ta -> m - 1; j >= 0; j--){
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
}

void pause(){
    if((MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED)){
        printf("Jeu en pause ! \n");
    }
}

int fusion_droite(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    deplacement_a_droite(ta);
    for(i = 0; i < ta -> n; i++){
        for(j = ta -> m - 1; j > 0; j--){
            if(ta -> tab[i][j] == ta -> tab[i][j - 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j] *= 2;
                ta -> tab[i][j - 1] = 0;
                nb_fusion += 1;
            }
        }
    }
    deplacement_a_droite(ta);
    return nb_fusion;
}

int fusion_gauche(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    deplacement_a_gauche(ta);
    for(i = 0; i < ta -> n; i++){
        for(j = 1; j < ta -> m ; j++){
            if(ta -> tab[i][j] == ta -> tab[i][j - 1] && ta -> tab[i][j] != 0){
                ta -> tab[i][j - 1] *= 2;
                ta -> tab[i][j] = 0;
                nb_fusion += 1;
            }
        }
    }
    deplacement_a_gauche(ta);
    return nb_fusion;
}

int fusion_haut(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    deplacement_en_haut(ta);
    for(j = 0; j < ta -> m; j++){
        for(i = 1; i < ta -> n; i++){
            if(ta -> tab[i][j] == ta -> tab[i - 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i - 1][j] *= 2;
                ta -> tab[i][j] = 0;
                nb_fusion += 1;
            }
        }
    }
    deplacement_en_haut(ta);
    return nb_fusion;
}

int fusion_bas(tableau *ta){
    int i, j, nb_fusion;
    nb_fusion = 0;
    deplacement_en_bas(ta); 
    for(j = 0; j < ta -> m; j++){
        for(i = ta -> n - 2; i >= 0; i--){
            if(ta -> tab[i][j] == ta -> tab[i + 1][j] && ta -> tab[i][j] != 0){
                ta -> tab[i + 1][j] *= 2;
                ta -> tab[i][j] = 0;
                nb_fusion += 1;
            }
        }
    }
    deplacement_en_bas(ta);
    return nb_fusion;
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

void retour_coup(tableau *ta, tableau *prec, int a_bouge){
    a_bouge = 1;
    if(((MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)) && a_bouge == 0){
        printf("Tableau précédent : \n");
        retour_arriere(ta, prec);
    } else if((( MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)) && a_bouge == 1){
        printf("Vous ne pouvez pas revenir en arrière si vous n'avez pas joué de coups. \n");
    }
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
    MLV_Font *police;
    int i, j, text_width, text_height;
    police = MLV_load_font("Seven_Segment.ttf", 125);
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){
            if(ta -> tab[i][j] == 2048){
                MLV_get_size_of_adapted_text_box_with_font("VOUS AVEZ GAGNE !", police, 10, &text_width, &text_height);
                MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, (LY - text_width) / 2, "VOUS AVEZ GAGNE !", police, MLV_ALPHA_TRANSPARENT, 0, MLV_COLOR_BLACK, MLV_COLOR_CADETBLUE4, MLV_TEXT_CENTER);
                return 0;
            }
        }
    }
    return 1;
}

