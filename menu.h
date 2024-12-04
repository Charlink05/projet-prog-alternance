#ifndef MENU_H
#define MENU_H

int verif(bouton bouton, int coord_x, int coord_y);

void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police);

void afficher_text(bouton bouton , MLV_Font *police);

void menu_depart(bouton t_bouton_m[4]);

void menu_save(bouton t_bouton_s[4]);

int charger(char *nom, joueur *jo, tableau *ta);

int save_p(char *nom, joueur *jo, tableau *ta);

void menu_score(bouton *retour);

int clic_bouton(bouton bout[], int lng);

void fonctionnement();

#endif