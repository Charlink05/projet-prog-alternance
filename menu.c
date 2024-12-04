#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "cases.h"
#include "mlv.h"
#include "tableau.h"
#include "vider_buffer.h"
#include "jeu.h"

#define SOIST 60
#define CENT 100

int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}

void cree_bouton(bouton *bouton, char *message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2 + 1;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

void afficher_text(bouton bouton , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}

void menu_depart(bouton t_bouton_m[4]){
    char *nom_bouton[4] = {"START", "SAVE", "SCORE", "EXIT"};
    MLV_Font *police;
    int text_width, text_height, i;
    
    MLV_clear_window(MLV_COLOR_GREY);

    police = MLV_load_font("Woodcut.ttf", 100);

    MLV_get_size_of_adapted_text_box_with_font("-- 2048 --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "-- 2048 --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    police = MLV_load_font("Woodcut.ttf", 60);

    for(i = 0; i < 4; i++){
        cree_bouton(&t_bouton_m[i], nom_bouton[i], LX / 2, 200 + i * 100, police);
        afficher_text(t_bouton_m[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}




void menu_save(bouton t_bouton_s[4]){
    char *nom_bouton[4]= {"SAVE 1", "SAVE 2", "SAVE 3", "HOME"};
    MLV_Font *police;
    int text_width, text_height, i;
    
    MLV_clear_window(MLV_COLOR_GREY);

    police = MLV_load_font("Woodcut.ttf", 100);

    MLV_get_size_of_adapted_text_box_with_font("-- SAVE --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height - 100, "-- SAVE --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("Woodcut.ttf", 70);
    
    for(i = 0; i < 4; i++){
        cree_bouton(&t_bouton_s[i], nom_bouton[i], LX / 2, 200 + i * 100, police);
        afficher_text(t_bouton_s[i], police);
    } 

    MLV_free_font(police);
    MLV_actualise_window();
}




int charger(char *nom, joueur *jo, tableau *ta){
    FILE * f;
    int i, j;
    if((f = fopen(nom, "r")) == NULL){
        printf("Erreur ouverture f \n");
        return -1;
    }

    if (fscanf(f, "%s\n%d", jo -> pseudo, &jo -> score) != 2){
        printf("Erreur : lecture pseudo ou score \n");
        fclose(f);
        return -1;
    }
    
    if(fscanf(f, "%d %d", &ta -> n, &ta -> m) != 2){
        printf("Erreur lecture dimension grille \n");
        fclose(f);
        return -1;
    }

    for( i = 0; i < ta -> n; i++){
        for( j = 0; j < ta -> m; j++){
            if(fscanf(f, "%d,", &ta -> tab[i][j]) != 1){
                printf("Erreur lecture case \n");
                fclose(f);
                return -1;
            }
        }
    }

    if(fscanf(f, "%d", &ta -> cases_vides) != 1){
        printf("Erreur lecture nb cases vides \n");
        fclose(f);
        return -1;
    }
        
    fclose(f);
    return 1;
}


int save_p(char *nom, joueur *jo, tableau *ta){
    FILE *f;
    int i, j;

    for (i = 0; i < ta -> n; i++) {
        for (j = 0; j < ta -> m; j++) {
            if (ta -> tab[i][j] == 0) {
                ta -> cases_vides++;
            }
        }
    }

    if((f = fopen(nom, "w")) == NULL){
        return -1;
    }

    fprintf(f, "%s\n", jo -> pseudo);
    fprintf(f, "%d\n", jo -> score);

    fprintf(f, "%d %d\n", ta -> n, ta -> m);

    for( i = 0; i < ta -> n; i++){
        for( j = 0; j < ta -> m; j++){
            fprintf(f, "%d ", ta -> tab[i][j]);
        }
        fprintf(f, "\n");
    }

    fprintf(f ,"%d\n",ta -> cases_vides);
    
    fclose(f);
    return 1;
}


void menu_score(bouton *retour){
    MLV_Font *police;
    char *t_nom[10] = {"1ST", "2ND", "3TH", "4TH", "5TH", "6TH", "7TH", "8TH", "9TH", "10TH"};
    int scores[10] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    char affichage[100];
    char *pseudos[10] = {"J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9", "J10"};
    char *nom_bouton_retour[1] = {"RETOUR"};
    int text_width, text_height, i, k;
    
    MLV_clear_window(MLV_COLOR_GREY);

    police = MLV_load_font("Woodcut.ttf", 50);

    MLV_get_size_of_adapted_text_box_with_font("-- SCORE --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "-- SCORE --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("Woodcut.ttf", 30);

    k = 0;

    for(i = 0; i < 10; i++){
        sprintf(affichage, "%s | Score : %d | Pseudo = %s", t_nom[i], scores[i], pseudos[i]);
         MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &text_width, &text_height);
         MLV_draw_adapted_text_box_with_font( LX/ 5, text_height / 3 + 80 + k, affichage, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
         k += 60;
    }

    police = MLV_load_font("Woodcut.ttf", 30);

    cree_bouton(retour, nom_bouton_retour[0], 60, 1, police);
    afficher_text(*retour, police);

    MLV_free_font(police); 
    MLV_actualise_window();
}

int clic_bouton(bouton bout[], int lng) {
    int s_x, s_y, i;
    MLV_wait_mouse(&s_x, &s_y);
    for (i = 0; i < lng; i++) {
        if (verif(bout[i], s_x, s_y)) {
            return i;
        }
    }
    return -1;
}

void fonctionnement(){
    bouton t_bouton_m[4], t_bouton_s[4];
    bouton retour;
    int pressed;
    int n = 4, m = 4, ok = 1;
    int retour_menu_p = 1;
    tableau ta;
    cases c;
    joueur j;
    
    menu_depart(t_bouton_m);

    while (ok == 1){
        menu_depart(t_bouton_m);
        pressed = clic_bouton(t_bouton_m, 4);

        switch(pressed){
        case 0:
            ta = initialisation_tableau(n, m);
            initialisation_cases(&c);
            jeu(&ta, &c);
            break;

        case 1:
            printf("Menu save \n");
            menu_save(t_bouton_s);
            while(retour_menu_p == 1){
                pressed = clic_bouton(t_bouton_s, 4);
                MLV_actualise_window();

                if(pressed == 0){
                    if(charger("save1.txt", &j, &ta) == 1){
                        jeu(&ta, &c);
                    }
                }
                else if(pressed == 1){
                    if(charger("save2.txt", &j, &ta) == 1){
                        jeu(&ta, &c);
                    }
                }
                else if(pressed == 2){
                    if(charger("save3.txt", &j, &ta) == 1){
                        jeu(&ta, &c);
                    }
                }
                else if(pressed == 3){
                    retour_menu_p = 0;
                }
            }
            break;

        case 2:
            menu_score(&retour);
            while(retour_menu_p == 1){
                pressed = clic_bouton(&retour, 1);
                if(pressed == 0){
                    retour_menu_p = 0;
                }
            }
            break;

        case 3:
            printf("au revoir \n");
            MLV_free_window();
            exit(EXIT_SUCCESS);
                
        }
        retour_menu_p = 1;
    }
    MLV_free_window();
}