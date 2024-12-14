#ifndef _CASES_H_
#define _CASES_H_

void aff_cases(cases *c);

void initialisation_cases(cases *c);

int calculer_cases_vides(tableau *ta);

void spawn_2_cases(tableau *ta, cases *c);
void spawn_1_cases(tableau *ta, cases *c);

void sauvegarde_tableau(tableau *ta, tableau *prec);
void retour_arriere(tableau *ta, tableau *prec);

int deplacement_a_droite(tableau *ta, joueur *j, int compte_fusion);
int deplacement_a_gauche(tableau *ta, joueur *j, int compte_fusion);
int deplacement_en_bas(tableau *ta, joueur *j, int compte_fusion);
int deplacement_en_haut(tableau *ta, joueur *j, int compte_fusion);

int peux_bouger(tableau *ta, tableau *ta2);

int check_game_over(tableau *ta);
int check_victoire(tableau *ta);

#endif