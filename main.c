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
#include "jeu.h"

int main(){

    int n = 4, m = 4;
    tableau ta;
    cases c;
    
    srand(time(NULL));

    MLV_create_window("2048", "2048", LX, LY);

    initialisation_tableau(n, m);
    initialisation_cases(&c);
    
    fonctionnement();
    jeu(&ta, &c);

    MLV_wait_seconds(7);
    MLV_free_window();
    exit(EXIT_SUCCESS);
}