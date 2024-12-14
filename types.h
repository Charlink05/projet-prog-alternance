#ifndef _TYPE_H_
#define _TYPE_H_


#define LX 1280
#define LY 720
#define N 4


typedef struct{
    int tab[N][N];
    int n;
    int m;
    int cases_vides;
} tableau;

typedef struct{
    int x;
    int y;
    int valeur;
} cases;

typedef struct{
    /* char pseudo[100]; */
    int score;
    int meilleur_score;
} joueur;

/* Menu */
#define L 20

typedef struct{
    int x;
    int y;
    int hauteur;
    int largeur;
    char txt[L];
} bouton;
#endif