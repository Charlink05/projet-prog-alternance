#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#define CASES 150

void aff_2048(){
    MLV_clear_window(MLV_COLOR_YELLOW3);
}

void aff_jeu(tableau *ta, joueur j){
    int i, j;
    for(i = 0; i < ta -> n; i++){
        for(j = 0; j < ta -> m; j++){