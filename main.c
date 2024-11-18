#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"
#include "vider_buffer.h"
#include "mlv.h"

int main() {
    int n = 4,
        m = 4,
        ok,
        sauvegarde_effectue = 1,
        cases_vides,
        prec_cases_vides,
        nb_fusion,
        game_over,
        victoire,
        fini = 1;
    tableau ta, prec;
    cases c;
    char dir;

    srand(time(NULL));
    MLV_create_window("2048", "2048", 800, 800);
    MLV_clear_window(MLV_COLOR_YELLOW3);
    /* aff_2048(); */

    cases_vides = 16;
    prec_cases_vides = 16;
    ta = initialisation_tableau(n, m);
    spawn_2_cases(&c, &ta);
    cases_vides = 14;
    prec_cases_vides = 14;
    
    aff_tableau(ta);
    ok = 1;

    while (ok == 1) {
        printf("Nombre de cases vides : %d \n", cases_vides);

        victoire = check_victoire(&ta);
        if(fini == 1){
            if(victoire == 0){
                printf("Bravo vous avez gagné ! \n");
                fini = 0;
            }
        }

        game_over = check_game_over(&ta);
        if (game_over && peux_bouger(&ta, &prec) == 0 && cases_vides == 0){
            printf("Vous avez perdu ! \n");
            exit(EXIT_FAILURE);
        }

        if (sauvegarde_effectue == 1) {
            printf("Entrez une direction (z/q/s/d) pour déplacer et a pour quitter : ");
        } else {
            printf("Entrez une direction (z/q/s/d) pour déplacer, r pour revenir en arrière et a pour quitter : ");
        }

        dir = getchar();
        viderBuffer();

        if (dir == 'a') {
            printf("Au revoir ! \n");
            ok = 0;
        } else if (dir == 'z' || dir == 'q' || dir == 's' || dir == 'd') {
            sauvegarde_tableau(&ta, &prec);
            prec_cases_vides = cases_vides;
            

            if (dir == 'z') {
                deplacement_en_haut(&ta);
                nb_fusion = fusion_haut(&ta);
                deplacement_en_haut(&ta);
            } else if (dir == 'q') {
                deplacement_a_gauche(&ta);
                nb_fusion = fusion_gauche(&ta);
                deplacement_a_gauche(&ta);
            } else if (dir == 's') {
                deplacement_en_bas(&ta);
                nb_fusion = fusion_bas(&ta);
                deplacement_en_bas(&ta);
            } else if (dir == 'd') {
                deplacement_a_droite(&ta);
                nb_fusion = fusion_droite(&ta);
                deplacement_a_droite(&ta);
            }

            printf("nb_fusion : %d \n", nb_fusion);

            if (peux_bouger(&ta, &prec) == 0) {
                spawn_1_cases(&c, &ta);
                aff_tableau(ta);
                if (nb_fusion == 0) {
                    cases_vides -= 1;
                } else {
                    cases_vides += nb_fusion - 1;
                }
            }
            else {
                printf("Pas de mouvements possibles \n \n");
                aff_tableau(ta);
            }
            
            sauvegarde_effectue = 0;
            
        } else if (dir == 'r' && sauvegarde_effectue == 0) {
            printf("Tableau précédent \n \n");
            retour_arriere(&ta, &prec);
            cases_vides = prec_cases_vides;
            aff_tableau(ta);
        } else if (dir == 'r' && sauvegarde_effectue == 1) {
            printf("Vous ne pouvez pas revenir en arrière si vous n'avez pas joué de coups. \n");
        } else {
            printf("Mauvaise direction : entrez bien 'z', 'q', 's', ou 'd' \n");
            aff_tableau(ta);
        }
    }

    MLV_wait_seconds(10);
    MLV_free_window();
    exit(EXIT_SUCCESS);
}
