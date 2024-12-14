#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"
#include "mlv.h"
#include "menu.h"
#include "score.h"

void jeu(tableau *ta, cases *c, joueur *j){
    int partie, cases_vides, prec_cases_vides, nb_fusion, compte_fusion = 0, game_over, victoire,text_width, text_height, fini, prec_score;
    tableau prec;
    MLV_Keyboard_button touche;
    MLV_Font *police;
    
    srand(time(NULL));
    MLV_clear_window(MLV_rgba(123, 99, 82, 255));
    
    cases_vides = calculer_cases_vides(ta);
    spawn_2_cases(ta, c);
    cases_vides -= 2;
    prec_cases_vides = cases_vides;
    compte_fusion = 0;

    nb_fusion = 0;
    partie = 1;
    fini = 1;
    compte_fusion = 0;
    prec_score = compte_fusion;

    charger_meilleurs_score("meilleurs_score.txt", j);

    aff_tableau_mlv(*ta, *j);
    
    while (partie == 1) {

        if(sauvegarde_jeu(j, ta) == 0){
            return ;
        }
        
        cases_vides = calculer_cases_vides(ta);
        
        victoire = check_victoire(ta);
        if(fini == 1){
            if(victoire == 0){
                fini = 0;
                MLV_actualise_window();
                MLV_wait_seconds(2);
            }
        }
        
        game_over = check_game_over(ta);
        if (game_over && peux_bouger(ta, &prec) == 0 && cases_vides <= 0){
            
            police = MLV_load_font("Woodcut.ttf", 100);
            MLV_get_size_of_adapted_text_box_with_font("VOUS AVEZ PERDU !", police, 10, &text_width, &text_height);
            
            MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, 25, "VOUS AVEZ PERDU !", police, MLV_ALPHA_TRANSPARENT, 0, MLV_COLOR_BLACK, MLV_rgba(235, 193, 132, 255), MLV_TEXT_CENTER);
            MLV_free_font(police);
            MLV_actualise_window();
            MLV_wait_seconds(2);
            exit(EXIT_FAILURE);
        }

        MLV_wait_keyboard(&touche, NULL, NULL);

        /* if((MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED)){ */
        /*     MLV_clear_window(MLV_rgba(235, 193, 132, 255)); */
        /*     menu_save(t_bouton_save); */
        /*     pressed = clic_bouton(t_bouton_save, 4); */
        /*     if(pressed == 0){ */
        /*         gestion_save(j, ta, pressed);                */
        /*     } */
        /*     else if(pressed == 1){ */
        /*         gestion_save(j, ta, pressed); */
        /*     } */
        /*     else if(pressed == 2){ */
        /*         gestion_save(j, ta, pressed); */
        /*     } */
        /*     else if(pressed == 3){ */
        /*         partie = 0; */
        /*     } */
        /* } */
        
        if(touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_RIGHT){
            sauvegarde_tableau(ta, &prec);
            prec_cases_vides = cases_vides;          
            prec_score = j -> score;
            
            if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED){
                nb_fusion = deplacement_en_haut(ta, j, compte_fusion);
                
            } else if ((MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)){
                nb_fusion = deplacement_a_gauche(ta, j, compte_fusion);
                
            } else if  ((MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)){
                nb_fusion = deplacement_en_bas(ta, j, compte_fusion);
                
            } else if ((MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)) {
                nb_fusion = deplacement_a_droite(ta, j, compte_fusion);
            }
            j -> score += compte_fusion;

            
            if(j -> score > j -> meilleur_score){
                j -> meilleur_score = j -> score;
                save_meilleurs_score("meilleurs_score.txt", j);
            }

            if (peux_bouger(ta, &prec) == 0){             
                spawn_1_cases(ta, c);
                aff_tableau_mlv(*ta, *j);
                cases_vides = calculer_cases_vides(ta);
                
                if (nb_fusion == 0) {
                    cases_vides -= 1;
                } else {
                    cases_vides += nb_fusion - 1;
                }
            }
            aff_tableau_mlv(*ta, *j);
            
        } else if (MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED){
            retour_arriere(ta, &prec);
            cases_vides = prec_cases_vides;
            j -> score = prec_score;            
            aff_tableau_mlv(*ta, *j);
        }

        MLV_actualise_window();
    }
    MLV_free_window();
    exit(EXIT_SUCCESS);
}