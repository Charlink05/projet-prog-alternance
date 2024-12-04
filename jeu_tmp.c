#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"
#include "vider_buffer.h"
#include "mlv.h"
#include "menu.h"

void jeu(tableau *ta, cases *c){
    int ok = 1,
        cases_vides,
        sauvegarde_effectue = 1,
        prec_cases_vides,
        nb_fusion,
        game_over,
        victoire,
        fini = 1;
    tableau prec;
    MLV_Keyboard_button touche;

    srand(time(NULL));
    MLV_clear_window(MLV_COLOR_GREY);
    /* aff_2048(); */
    
    spawn_2_cases(ta, c);
    cases_vides = 14;
    prec_cases_vides = 14;

    /* aff_tableau(*ta); */
    aff_tableau_mlv(*ta);
    
    while (ok == 1) {
        /* printf("Nombre de cases vides : %d \n", cases_vides); */

        victoire = check_victoire(ta);
        if(fini == 1){
            if(victoire == 0){
                /* printf("Bravo vous avez gagné ! \n"); */
                fini = 0;
                MLV_actualise_window();
                MLV_wait_seconds(2);
            }
        }

        game_over = check_game_over(ta);
        if (game_over && peux_bouger(ta, &prec) == 0 && cases_vides == 0){
            /* printf("Vous avez perdu ! \n"); */
            MLV_draw_text(300, 200, "Vous avez perdu !", MLV_COLOR_RED);
            MLV_actualise_window();
            MLV_wait_seconds(2);
            exit(EXIT_FAILURE);
        }

        /* if (sauvegarde_effectue == 1) { */
        /*     printf("Entrez une direction (z/q/s/d) pour déplacer et a pour quitter : "); */
        /* } else { */
        /*     printf("Entrez une direction (z/q/s/d) pour déplacer, r pour revenir en arrière et a pour quitter : "); */
        /* } */

        MLV_wait_keyboard(&touche, NULL, NULL);
        
        if((MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED)){
            /* printf("Au revoir ! \n"); */
            ok = 0;
        }
        else if(touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_RIGHT){
            sauvegarde_tableau(ta, &prec);
            prec_cases_vides = cases_vides;
            nb_fusion = 0;
            if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED) {
                deplacement_en_haut(ta);
                nb_fusion = fusion_haut(ta);
                
            } else if ((MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)) {
                deplacement_a_gauche(ta);
                nb_fusion = fusion_gauche(ta);
                
            } else if  ((MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)){
                deplacement_en_bas(ta);
                nb_fusion = fusion_bas(ta);           
                
            } else if ((MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)) {
                deplacement_a_droite(ta);
                nb_fusion = fusion_droite(ta);
            }

            /* printf("nb_fusion : %d \n", nb_fusion); */

            if (peux_bouger(ta, &prec) == 0) {
                spawn_1_cases(ta, c);
                aff_tableau_mlv(*ta);
                /* aff_tableau(*ta); */
                if (nb_fusion == 0) {
                    cases_vides -= 1;
                } else {
                    cases_vides += nb_fusion - 1;
                }
            }
            /* else { */
            /*     printf("Pas de mouvements possibles \n \n"); */
            aff_tableau_mlv(*ta);
            /*     aff_tableau(*ta); */
            /* } */
            
            sauvegarde_effectue = 0;
            
        } else if (((MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)) && sauvegarde_effectue == 0) {
            /* printf("Tableau précédent \n \n"); */
            retour_arriere(ta, &prec);
            cases_vides = prec_cases_vides;
            /* aff_tableau(*ta); */
            aff_tableau_mlv(*ta);
            /* } else if (((MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)) && sauvegarde_effectue == 1) { */
            /* printf("Vous ne pouvez pas revenir en arrière si vous n'avez pas joué de coups. \n"); */
            /* } else { */
            /*     printf("Mauvaise direction : entrez bien 'z', 'q', 's', ou 'd' \n"); */
            /*     aff_tableau(*ta); */
            /*     aff_tableau_mlv(*ta); */
            /* } */
        }
        MLV_actualise_window();
    }
    MLV_free_window();
    exit(EXIT_SUCCESS);
}

            

 /*        /\* if(touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_RIGHT){ *\/ */
/*         deplacement(&ta, &prec, &c, a_bouge); */
/*         sauvegarde_tableau(&ta, &prec); */
/*         prec_cases_vides = cases_vides; */
        
        
/*         if(peux_bouger(&ta, &prec) == 0){ */
/*         spawn_1_cases(&c, &ta); */
/*         if(nb_fusion == 0){ */
/*             cases_vides -= 1; */
/*         } else { */
/*             cases_vides += nb_fusion - 1; */
/*         } */
/*     } */
/*         MLV_actualise_window(); */
      /*    /\* int a_bouger, nb_fusion, cases_vides, prec_cases_vides; *\/ */
/*    /\*  a_bouger = 0; *\/ */
/*    /\*  nb_fusion = 0; *\/ */