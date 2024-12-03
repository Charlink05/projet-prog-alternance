#ifndef _CASES_H_
#define _CASES_H_

void aff_cases(cases *c);

void initialisation_cases(cases *c);

void spawn_2_cases(tableau *ta, cases *c);
void spawn_1_cases(tableau *ta, cases *c);

void sauvegarde_tableau(tableau *ta, tableau *prec);
void retour_arriere(tableau *ta, tableau *prec);

void deplacement_a_droite(tableau *ta);
void deplacement_a_gauche(tableau *ta);
void deplacement_en_bas(tableau *ta);
void deplacement_en_haut(tableau *ta);

void pause();

int fusion_droite(tableau *ta);
int fusion_gauche(tableau *ta);
int fusion_haut(tableau *ta);
int fusion_bas(tableau *ta);

int peux_bouger(tableau *ta, tableau *ta2);

void retour_coup(tableau *ta, tableau *prec, int a_bouge);

void deplacement(tableau ta, tableau prec, cases c, int a_bouge);

/* int deplacement_et_fusion(tableau *ta, char dir); */

/* int peux_bouger_droite(tableau *ta); */
/* int peux_bouger_gauche(tableau *ta); */
/* int peux_bouger_haut(tableau *ta); */
/* int peux_bouger_bas(tableau *ta); */

int check_game_over(tableau *ta);
int check_victoire(tableau *ta);

#endif