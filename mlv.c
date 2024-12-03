#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>

#define CASES 100
#define ESPACEMENT 15
#define RAYON_ARROONDIS 15

void aff_2048(){
    MLV_clear_window(MLV_COLOR_GREY);
    /* MLV_draw_filled_rectangle(150, 150, CASES, CASES, MLV_COLOR_GOLD); */
}

void aff_tableau_mlv(tableau ta){
    int i, j, val, x, y;
    char text[10];
    MLV_Color color;
    MLV_Color text_color;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_DARK_GREY);

    police = MLV_load_font("Seven_Segment.ttf", 100);

    MLV_draw_adapted_text_box_with_font( LX / 3, 50, "2048", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BEIGE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_draw_filled_rectangle(180, 180, ta.m * (CASES + ESPACEMENT) + 30, ta.n * (CASES + ESPACEMENT) + 30 ,MLV_COLOR_BEIGE);
    
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){

            x = 200 + j * (CASES + ESPACEMENT);
            y = 200 + i * (CASES + ESPACEMENT);
            
            val = ta.tab[i][j];

            if(val == 0){
                MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_COLOR_WHITE);
            }

            switch(val){
            case 2:
                color = MLV_rgba(250, 212, 255, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 4:
                color = MLV_rgba(104, 145, 188, 255);
                 text_color = MLV_COLOR_WHITE;
                 break;
            case 8:
                color = MLV_rgba(93, 130, 169, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 16:
                color = MLV_rgba(83, 116, 151, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 32:
                color = MLV_rgba(73, 101, 132, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 64:
                color = MLV_rgba(62, 87, 113, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 128:
                color = MLV_rgba(52, 72, 94, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 256:
                color = MLV_rgba(41, 58, 75, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 512:
                color = MLV_rgba(31, 43, 56, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 1024:
                color = MLV_rgba(21, 29, 38, 255);
                text_color = MLV_COLOR_WHITE;
                break;
            case 2048:
                color = MLV_COLOR_BLACK;
                text_color = MLV_COLOR_WHITE;
                break;
            default:
                color = MLV_COLOR_BLACK;
                text_color = MLV_COLOR_WHITE;
                break;
            }

            MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_BLACK);

            if(val > 0){
                sprintf(text, "%d", val);
                MLV_draw_text_box(x,
                                  y,
                                  CASES - 1,
                                  CASES - 1,
                                  text,
                                  10,
                                  text_color,
                                  MLV_ALPHA_TRANSPARENT,
                                  color,
                                  MLV_TEXT_CENTER,
                                  MLV_HORIZONTAL_CENTER,
                                  MLV_VERTICAL_CENTER);
            }
        }
    }
    MLV_actualise_window();
}