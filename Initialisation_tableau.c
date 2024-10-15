#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 20

void afficher_tableau(int tableau[N][N], int n, int m){
    int i, j;
    printf("----+---+---+----");
    printf("\n");
    for(i = 0; i < n; i++){
        printf("|");
        for(j = 0; j < m; j++){
            tableau[i][j] = 0;
            printf(" %d |", tableau[i][j]);
        }
        printf("\n");
        printf("----+---+---+----");
        printf("\n");
    }
}

void deplacement(){
    char * s;
    char c;
    int i;
    printf("Veuillez entrer un caractère qui est : \n soit z pour haut ; \n soit q pour gauche ; \n soit s pour bas ; \n soit d pour droite : ");
    i = 0;
    while(i == 0){
        c = fgetc(stdin);
        if(c != 'z' && c != 'q' && c != 's' && c != 'd'){
            ;
        }
        else{
            i += 1;
        }
    }
    if(c == 'z'){
        s = "haut";
        printf("Le carac %c est correct, vous vous déplacez en %s \n", c, s);
    }
    if(c == 'q'){
        s = "gauche";
        printf("Le carac %c est correct, vous vous déplacez à %s \n", c, s);
    }
    if(c == 's'){
        s = "bas";
        printf("Le carac %c est correct, vous vous déplacez en %s \n", c, s);
    }
    if(c == 'd'){
        s = "droite";
        printf("Le carac %c est correct, vous vous déplacez à %s \n", c, s);
    }
}

void spawn(int tableau[N][N], int nb_cases_vides, int n, int m){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if(



    
int main(){
    int tableau[N][N];

    srand(time(NULL));
    printf("voici le tableau du jeu 2048 : \n");
    afficher_tableau(tableau, 4, 4);
    deplacement();
    exit(EXIT_SUCCESS);
}