#ifndef MENU_H
#define MENU_H

int verif(bouton bouton, int coord_x, int coord_y);

int clic_bouton(bouton bout[], int lng);

void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police);

void afficher_text(bouton bouton , MLV_Font *police);

void menu_depart(bouton t_bouton_m[4]);

void menu_save(bouton t_bouton_s[4]);

int charger(char *nom, joueur *jo, tableau *ta);

int save_p(char *nom, joueur *jo, tableau *ta);

int save_meilleurs_score(char *nom_fichier, joueur *j);

int charger_meilleurs_score(char *nom_fichier, joueur *j);

void menu_rules(bouton *retour);

int ecrasement_save();

void gestion_save(joueur *j, tableau *ta, int pressed);

void menu_pause(bouton t_bouton_pause[3]);

int sauvegarde_jeu(joueur *j, tableau *ta);

int pause_jeu(joueur *j, tableau *ta);

void fonctionnement();

#endif