#ifndef _CASES_H_
#define _CASES_H_

void aff_cases(cases *c);

void initialisation(cases *c);

void spawn_2_cases(cases *c, tableau *ta);
void spawn_1_cases(cases *c, tableau *ta);

void deplacement_a_droite(tableau *ta);
void deplacement_a_gauche(tableau *ta);
void deplacement_en_bas(tableau *ta);
void deplacement_en_haut(tableau *ta);

void deplacement(tableau *ta, char dir);

int fusion_droite(tableau *ta);
int fusion_gauche(tableau *ta);
int fusion_haut(tableau *ta);
int fusion_bas(tableau *ta);

int deplacement_et_fusion(tableau *ta, char dir);

void sauvegarde_tableau(tableau *ta, tableau *prec);
void retour_arriere(tableau *ta, tableau *prec);

int peux_bouger_droite(tableau *ta);
int peux_bouger_gauche(tableau *ta);
int peux_bouger_haut(tableau *ta);
int peux_bouger_bas(tableau *ta);
int peux_bouger(tableau *ta, tableau *ta2);

int check_game_over(tableau *ta);
int check_victoire(tableau *ta);
/* int fusion_effectue(tableau *ta); */
/* int compte_fusion(tableau *ta, tableau *prec); */

#endif