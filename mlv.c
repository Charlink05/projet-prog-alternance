#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#define CASES 100

void aff_2048(){
    MLV_clear_window(MLV_COLOR_GREY);
    /* MLV_draw_filled_rectangle(150, 150, CASES, CASES, MLV_COLOR_GOLD); */
}

void aff_tableau_mlv(tableau ta){
    int i, j, val;
    char text[10];
    MLV_Color color;
    MLV_Color text_color;

    MLV_clear_window(MLV_COLOR_GREY);
    
    for(i = 0; i < ta.n; i++){
        for(j = 0; j < ta.m; j++){
            val = ta.tab[i][j];
            switch(val){
            case 0:
                color = MLV_COLOR_WHITE;
                text_color = MLV_COLOR_WHITE;
                break;
            case 2:
                color = MLV_COLOR_YELLOW3;
                text_color = MLV_COLOR_WHITE;
                break;
            case 4:
                 color = MLV_COLOR_ORANGE;
                 text_color = MLV_COLOR_WHITE;
                 break;
            case 8:
                color = MLV_COLOR_RED;
                text_color = MLV_COLOR_WHITE;
                break;
            case 16:
                color = MLV_COLOR_BLUE;
                text_color = MLV_COLOR_WHITE;
                break;
            case 32:
                color = MLV_COLOR_GREEN;
                text_color = MLV_COLOR_WHITE;
                break;
            case 64:
                color = MLV_COLOR_CYAN;
                text_color = MLV_COLOR_WHITE;
                break;
            case 128:
                color = MLV_COLOR_PINK;
                text_color = MLV_COLOR_WHITE;
                break;
            case 256:
                color = MLV_COLOR_PURPLE;
                text_color = MLV_COLOR_WHITE;
                break;
            case 512:
                color = MLV_COLOR_MAGENTA;
                text_color = MLV_COLOR_WHITE;
                break;
            case 1024:
                color = MLV_COLOR_BROWN;
                text_color = MLV_COLOR_WHITE;
                break;
            case 2048:
                color = MLV_COLOR_WHITE;
                text_color = MLV_COLOR_BLACK;
                break;
            default:
                color = MLV_COLOR_GREY;
                text_color = MLV_COLOR_GREY;
                break;
            }
            MLV_draw_rectangle(150 + j * CASES, 150 + i * CASES, CASES, CASES, MLV_COLOR_BLACK);
            MLV_draw_filled_rectangle( 150 + j * CASES, 150 + i * CASES, CASES - 1, CASES - 1, color);
            if(val > 0){
                sprintf(text, "%d", val);
                MLV_draw_adapted_text_box(200 + i * CASES, 200 * CASES + j, text, 10, MLV_ALPHA_TRANSPARENT, text_color, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
            }
        }
    }
    MLV_update_window();
}