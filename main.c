#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"
#include "mlv.h"
#include "menu.h"
#include "jeu.h"
#include "score.h"

int main(){
    
    srand(time(NULL));

    MLV_create_window("2048", "2048", LX, LY);
    
    fonctionnement();
    
    MLV_free_window();
    exit(EXIT_SUCCESS);
}