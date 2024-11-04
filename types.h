#ifndef TYPE_H
#define TYPE_H

#define N 50


typedef struct{
    int tab[N][N];
    int n;
    int m;
} tableau;

typedef struct{
    int couleur;
    int x;
    int y;
    int cases_vides;
} cases;

typedef struct{
    char *pseudo;
    int score;
} joueur;

#endif