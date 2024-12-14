#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "score.h"
#include "menu.h"
#include <string.h>

#define CASES 98
#define ESPACEMENT 15

void aff_tableau_mlv(tableau ta, joueur jo){
    int i, j, val, x, y, text_width, text_height, l_mat, h_mat; /* image_width, image_height; */
    char text[12];
    char texte_meilleur_score[50];
    char texte_score_actuel[50];
    MLV_Color color;
    MLV_Font *police;
    /* MLV_Image *i_score; */

    charger_meilleurs_score("meilleurs_score.txt", &jo);

    MLV_clear_window(MLV_rgba(123, 99, 82, 255));

    police = MLV_load_font("Woodcut.ttf", 100);

    l_mat = ta.m * (CASES + ESPACEMENT) + ESPACEMENT;
    h_mat = ta.n * (CASES + ESPACEMENT) + ESPACEMENT;

    MLV_get_size_of_adapted_text_box_with_font("-- 2048 --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "-- 2048 --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    MLV_free_font(police);
    
    police =  MLV_load_font("Woodcut.ttf", 60);

    sprintf(texte_meilleur_score, "Meilleur score : %d", jo.meilleur_score);
    MLV_draw_text_with_font(810, 150, texte_meilleur_score, police, MLV_COLOR_BLACK);
    
    sprintf(texte_score_actuel, "Score : %d", jo.score);
    MLV_draw_text_with_font(810, 250, texte_score_actuel, police, MLV_COLOR_BLACK);
    
    MLV_free_font(police);

    /* i_score = MLV_load_image("mur_bois3.jpg"); */
    
    /* MLV_get_image_size(i_score, &image_width, &image_height); */

    /* MLV_resize_image_with_proportions(i_score, 1600, 720); */

    /* MLV_draw_image(i_score, 0, 0); */
    /* MLV_free_image(i_score); */

    /* i_score = MLV_load_image("cadre.jpg"); */
    
    /* MLV_get_image_size(i_score, &image_width, &image_height); */

    /* MLV_resize_image_with_proportions(i_score, 543, 541); */

    /* MLV_draw_image(i_score, 115, 101); */
    /* MLV_free_image(i_score); */

    /* MLV_draw_filled_rectangle(161, 149, 447, 447,(MLV_rgba(235, 193, 132, 255))); */
      
    /* i_score = MLV_load_image("oui-r.png"); */
    
    /* MLV_get_image_size(i_score, &image_width, &image_height); */

    /* MLV_resize_image_with_proportions(i_score, 300, 300); */

    /* MLV_draw_image(i_score, 700, 140); */
    /* MLV_free_image(i_score); */
    
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){

            x = ((LX - 200 - l_mat) / 2) + j * (CASES + ESPACEMENT);
            y = ((LY + 300 - h_mat) / 3) + i * (CASES + ESPACEMENT);
            
            val = ta.tab[i][j];

            if(val == 0){
                MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_rgba(255, 239, 210, 255));
            }

            switch(val){
            case 2:
                color = MLV_rgba(233, 209, 193, 255);
                break;
            case 4:
                color = MLV_rgba(206, 188, 171, 255);
                 break;
            case 8:
                color = MLV_rgba(179, 166, 149, 255);
                break;
            case 16:
                color = MLV_rgba(156, 143, 127, 255);
                break;
            case 32:
                color = MLV_rgba(133, 120, 104, 255);
                break;
            case 64:
                color = MLV_rgba(122, 96, 82, 255);
                break;
            case 128:
                color = MLV_rgba(110, 71, 59, 255);
                break;
            case 256:
                color = MLV_rgba(93, 61, 48, 255);
                break;
            case 512:
                color = MLV_rgba(76, 50, 37, 255);
                break;
            case 1024:
                color = MLV_rgba(59, 39, 26, 255);
                break;
            case 2048:
                color = MLV_rgba(41, 28, 14, 255);
                break;
            default:
                color = MLV_rgba(22, 17, 2, 255);
                break;
            }

            MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_BLACK);

            if(val > 0){
                sprintf(text, "%d", val);
                
                police = MLV_load_font("Woodcut.ttf", 30);

                MLV_draw_text_box_with_font(
                    x, y, CASES - 1, CASES - 1, text, police, 10, MLV_ALPHA_TRANSPARENT, (val < 1024) ? MLV_COLOR_BLACK : MLV_COLOR_WHITE, color, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

                MLV_free_font(police);
            
            
            }
        }
    }
    MLV_actualise_window();
    
}