#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "cases.h"
#include "mlv.h"
#include "tableau.h"
#include "jeu.h"
#include "score.h"

#define SOIST 60
#define CENT 100

int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}


int clic_bouton(bouton bout[], int lng) {
    int s_x, s_y, i;
    
    MLV_wait_mouse(&s_x, &s_y);
    for (i = 0; i < lng; i++) {
        if (verif(bout[i], s_x, s_y) == 1) {
            return i;
        }
    }
    return i;
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
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}

void afficher_box(char *text){
    int text_width, text_height;
    MLV_Font *police;

    police = MLV_load_font("Woodcut.ttf", 50);
    MLV_get_size_of_adapted_text_box_with_font(text, police, 10, &text_width, &text_height);

    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, (LY - text_height) / 3, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_BEIGE, MLV_TEXT_CENTER);

    MLV_actualise_window();
    MLV_wait_seconds(3);
}

void menu_depart(bouton t_bouton_m[4]){
    char *nom_bouton[4] = {"START", "SAVE", "RULES", "EXIT"};
    MLV_Font *police;
    int text_width, text_height, i, k;
    
    MLV_clear_window(MLV_rgba(123, 99, 82, 255));

    police = MLV_load_font("Woodcut.ttf", 120);

    MLV_get_size_of_adapted_text_box_with_font("-- 2048 --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "-- 2048 --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    police = MLV_load_font("Woodcut.ttf", 80);

    k = 0;

    for(i = 0; i < 4; i++){
        cree_bouton(&t_bouton_m[i], nom_bouton[i], LX / 2, 225 + i * 100 + k, police);
        afficher_text(t_bouton_m[i], police);
        k += 30;
    }

    MLV_free_font(police);
    MLV_actualise_window();
}


void menu_save(bouton t_bouton_s[4]){
    char *nom_bouton[4]= {"SAVE 1", "SAVE 2", "SAVE 3", "HOME"};
    MLV_Font *police;
    int text_width, text_height, i, k;
    
    MLV_clear_window(MLV_rgba(123, 99, 82, 255));

    police = MLV_load_font("Woodcut.ttf", 120);

    MLV_get_size_of_adapted_text_box_with_font("-- SAVE --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height - 100, "-- SAVE --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("Woodcut.ttf", 70);

    k = 0;
    
    for(i = 0; i < 4; i++){
        cree_bouton(&t_bouton_s[i], nom_bouton[i], LX / 2, 225 + i * 100 + k, police);
        afficher_text(t_bouton_s[i], police);
        k += 30;
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


    if (fscanf(f, "%d %d", &jo -> score, &jo -> meilleur_score) != 2){
        printf("Erreur : lecture meilleur_score ou score \n");
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

    ta -> cases_vides = 0;
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
    
    fprintf(f, "%d %d\n", jo -> score, jo -> meilleur_score);

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

int save_meilleurs_score(char *nom_fichier, joueur *j) {
    FILE *f;

    if(j -> score > j -> meilleur_score){
        j -> meilleur_score = j -> score;
    }

    if ((f = fopen(nom_fichier, "w")) == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
        return -1;
    }

    fprintf(f, "%d\n", j->meilleur_score);
    fclose(f);
    return 1;
}

int charger_meilleurs_score(char *nom_fichier, joueur *j) {
    FILE *f;

    if ((f = fopen(nom_fichier, "r")) == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
        j->meilleur_score = 0;
        save_meilleurs_score(nom_fichier, j);
        return 1;
    }

    if (fscanf(f, "%d", &j->meilleur_score) != 1) {
        printf("Erreur de lecture du meilleur score\n");
        j->meilleur_score = 0;
        fclose(f);
        save_meilleurs_score(nom_fichier, j);
        return 1;
    }

    fclose(f);
    return 1;
}


void menu_rules(bouton *retour){
    MLV_Font *police;
    char affichage[600];
    char *nom_bouton_retour[1] = {"BACK"};
    int text_width, text_height;

    MLV_clear_window(MLV_rgba(123, 99, 82, 255));

    police = MLV_load_font("Woodcut.ttf", 80);

    MLV_get_size_of_adapted_text_box_with_font("-- RULES --", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 20, "-- RULES --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    police = MLV_load_font("Woodcut.ttf", 30);

    sprintf(affichage, "TOUCHE DE JEU : \n DEPLACEMENT : FLECHES DIRECTIONNELLES \n REVENIR EN ARRIERE : R \n QUITTER LE JEU : A \n \n  BUT : FUSIONNER 2 CASES DE MEME VALEUR \n \n SI VALEUR EGALE ALORS LA NOUVELLE CASES SERA LA PUISSANCE DE 2 SUPERIEUR. \n \n OBJECTIF : ATTEINDRE 2048 \n ATTENTION SI VOUS NE POUVEZ PLUS BOUGER ALORS VOUS PERDEZ \n \n BONNE CHANCE !");
    MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 50, affichage, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("Woodcut.ttf", 35);

    cree_bouton(retour, nom_bouton_retour[0], 60, 1, police);
    afficher_text(*retour, police);

    MLV_free_font(police);
    MLV_actualise_window();
}

int ecrasement_save(){
    MLV_Keyboard_button touche;

    MLV_clear_window(MLV_COLOR_BEIGE);
    MLV_draw_text(LX / 2, LY / 3, "Ecraser la sauvegarde ? (o/n)", MLV_COLOR_BLACK);
    MLV_actualise_window();
    MLV_wait_keyboard(&touche, NULL, NULL);
        
    if(touche == MLV_KEYBOARD_o){
        return 1;
    }
    else if(touche  == MLV_KEYBOARD_n){
        return 0;
    }
    return -1;
}

void gestion_save(joueur *j, tableau *ta, int pressed){
    char *nom_save[4] = {"save1.txt", "save2.txt", "save3.txt"};
    int ecrase;
    FILE *f;

    f = fopen(nom_save[pressed], "r");

    if(f == NULL){
        if(save_p(nom_save[pressed], j, ta) == 1){
            printf("Partie bien sauvegardé \n");
        }
    }
    else{
        fclose(f);
        ecrase = ecrasement_save();
        if(ecrase == 1){
            if(save_p(nom_save[pressed], j, ta) == 1){
                printf("Partie bien sauvegardé après confirmation d'écrasement \n");
            }
        }
        else if(ecrase == 0){
            printf("Annulation de l'écrasement \n");
        }
        else{
            printf("Mauvaise touche \n");
        }
    }
} 

void menu_pause(bouton t_bouton_pause[3]){
    char *nom_bouton_pause[3] = {"RESUME", "SAVE", "QUIT"};
    MLV_Font *police;
    int text_width, text_height, i;

    MLV_clear_window(MLV_rgba(123, 99, 82, 255));
    police = MLV_load_font("Woodcut.ttf", 80);

    MLV_get_size_of_adapted_text_box_with_font("PAUSE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "PAUSE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    police = MLV_load_font("Woodcut.ttf", 50);
     
    /* bouton pause */
    for( i = 0 ; i < 3 ; i++){
        cree_bouton(&t_bouton_pause[i], nom_bouton_pause[i], LX / 2, 150 + i * 100, police);
        afficher_text(t_bouton_pause[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

int sauvegarde_jeu(joueur *j, tableau *ta){
    MLV_Keyboard_button touche;
    bouton t_bouton_pause[3], t_bouton_save[5];
    int pressed;

    if(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_KEY){
        if(touche == MLV_KEYBOARD_s){
            while(1){
                menu_pause(t_bouton_pause);
                pressed = clic_bouton(t_bouton_pause, 3);
                switch(pressed){
                case 0:
                    printf("Le jeu se relance \n");
                    return 1;
                    break;

                case 1:
                    menu_save(t_bouton_save);
                    pressed = clic_bouton(t_bouton_save, 4);

                    if(pressed < 3){
                        gestion_save(j, ta, pressed);
                    }
                    else if(pressed == 3){
                        printf("Retour menu principal \n");
                    }
                    
                    /* if(pressed == 0){ /\* save 1 *\/ */
                    /*     gestion_save_pause(t_bouton_save, je, ta); */
                    /* } */
                    /* else if(pressed == 1){ /\* save 2 *\/ */
                    /*     gestion_save_pause(t_bouton_save, je, ta); */
                    /* } */
                    /* else if(pressed == 2){ /\* save 3 *\/ */
                    /*     gestion_save_pause(t_bouton_save, je, ta); */
                    /* } */
                    /* else if(pressed == 3){ */
                    /*     printf("Retour menu principal \n"); */
            
                    /* }     */                
                    break;
                case 2:
                    printf("Menu \n");
                    return 0;
                    break;
                }
            }
        }
    }
    return 1;
}
    
    

/* void menu_score(bouton *retour){ */
/*     MLV_Font *police; */
/*     char *t_nom[10] = {"1ST", "2ND", "3TH", "4TH", "5TH", "6TH", "7TH", "8TH", "9TH", "10TH"}; */
/*     int scores[10] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048}; */
/*     char affichage[100]; */
/*     char *pseudos[10] = {"J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9", "J10"}; */
/*     char *nom_bouton_retour[1] = {"RETOUR"}; */
/*     int text_width, text_height, i, k; */
    
/*     MLV_clear_window(MLV_COLOR_GREY); */

/*     police = MLV_load_font("Woodcut.ttf", 50); */

/*     MLV_get_size_of_adapted_text_box_with_font("-- SCORE --", police, 10, &text_width, &text_height); */
/*     MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "-- SCORE --", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); */

/*     police = MLV_load_font("Woodcut.ttf", 30); */

/*     k = 0; */

/*     for(i = 0; i < 10; i++){ */
/*         sprintf(affichage, "%s | Score : %d | Pseudo = %s", t_nom[i], scores[i], pseudos[i]); */
/*          MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &text_width, &text_height); */
/*          MLV_draw_adapted_text_box_with_font( LX/ 5, text_height / 3 + 80 + k, affichage, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); */
/*          k += 60; */
/*     } */

/*     police = MLV_load_font("Woodcut.ttf", 30); */

/*     cree_bouton(retour, nom_bouton_retour[0], 60, 1, police); */
/*     afficher_text(*retour, police); */

/*     MLV_free_font(police);  */
/*     MLV_actualise_window(); */
/* } */       

void fonctionnement(){
    bouton t_bouton_m[4], t_bouton_s[4];
    bouton retour;
    char *nom_save[3] = {"save1.txt", "save2.txt", "save3.txt"};
    char text[100];
    int pressed, n, m, retour_menu_p;
    tableau ta;
    cases c;
    joueur j;

    n = 4;
    m = 4;
    retour_menu_p = 1;

    while (retour_menu_p == 1){
        menu_depart(t_bouton_m);
        pressed = clic_bouton(t_bouton_m, 4);

        switch(pressed){
        case 0:
            ta = initialisation_tableau(n, m);
            initialisation_cases(&c);
            j.score = 0;
            jeu(&ta, &c, &j);
            break;

        case 1:
            printf("Menu save \n");
            menu_save(t_bouton_s);
            while(retour_menu_p == 1){
                pressed = clic_bouton(t_bouton_s, 4);

                if(pressed < 3){
                    printf("Save %s\n", nom_save[pressed]);
                    if(charger(nom_save[pressed], &j, &ta) == 1){
                        printf("Score chargé: %d\n", j.score);
                        jeu(&ta, &c, &j);
                        retour_menu_p = 0;
                    }
                    else{
                        sprintf(text, "Il n'y a pas de donnée(s) de sauvegardes dans la Save %d", pressed+1);
                        afficher_box(text);
                        retour_menu_p = 0;
                    }
                }
                else if(pressed == 3){
                    retour_menu_p = 0;
                }
            }
            break;

        case 2:
            menu_rules(&retour);
            while(retour_menu_p == 1){
                pressed = clic_bouton(&retour, 1);
                if(pressed == 0){
                    retour_menu_p = 0;
                }
            }
            break;
            
        case 3:
            printf("Au revoir \n");
            return ;                
        }
        retour_menu_p = 1;
    }
    MLV_free_window();
}