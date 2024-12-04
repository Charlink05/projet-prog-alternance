#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>

#define CASES 100
#define ESPACEMENT 15

void aff_2048(){
    MLV_clear_window(MLV_COLOR_GREY);
    /* MLV_draw_filled_rectangle(150, 150, CASES, CASES, MLV_COLOR_GOLD); */
}

void aff_tableau_mlv(tableau ta){
    int i, j, val, x, y, text_width, text_height, l_mat, h_mat;
    char text[10];
    MLV_Color color;
    MLV_Color contour_case;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(123, 99, 82, 255));

    police = MLV_load_font("Woodcut.ttf", 100);

    l_mat = ta.m * (CASES + ESPACEMENT) + ESPACEMENT;
    h_mat = ta.n * (CASES + ESPACEMENT) + ESPACEMENT;

    MLV_get_size_of_adapted_text_box_with_font("-- 2048 --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "-- 2048 --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BEIGE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /*MLV_draw_filled_rectangle( ((LX - l_mat) / 2) - ESPACEMENT, ((LX - h_mat) / 2) - ESPACEMENT, l_mat, h_mat, MLV_COLOR_CADETBLUE4);*/
    
    
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){

            x = ((LX - l_mat) / 2) + j * (CASES + ESPACEMENT);
            y = ((LX - h_mat) / 3) + i * (CASES + ESPACEMENT);
            
            val = ta.tab[i][j];

            if(val == 0){
                MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_rgba(255, 239, 210, 255));
            }

            switch(val){
            case 2:
                color = MLV_rgba(233, 209, 193, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 4:
                color = MLV_rgba(206, 188, 171, 255);
                 contour_case = MLV_COLOR_BLACK;
                 break;
            case 8:
                color = MLV_rgba(179, 166, 149, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 16:
                color = MLV_rgba(156, 143, 127, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 32:
                color = MLV_rgba(133, 120, 104, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 64:
                color = MLV_rgba(122, 96, 82, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 128:
                color = MLV_rgba(110, 71, 59, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 256:
                color = MLV_rgba(93, 61, 48, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 512:
                color = MLV_rgba(76, 50, 37, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 1024:
                color = MLV_rgba(59, 39, 26, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            case 2048:
                color = MLV_rgba(41, 28, 14, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            default:
                color = MLV_rgba(22, 17, 2, 255);
                contour_case = MLV_COLOR_BLACK;
                break;
            }

            MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_BLACK);

            if(val > 0){
                sprintf(text, "%d", val);
                
                police = MLV_load_font("Woodcut.ttf", 30);

                MLV_draw_text_box_with_font(
                    x, y, CASES - 1, CASES - 1, text, police, 10, contour_case, (val < 2048) ? MLV_COLOR_BLACK : MLV_COLOR_WHITE, color, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

                MLV_free_font(police);
            
            
            }
        }
    }
    MLV_actualise_window();
}