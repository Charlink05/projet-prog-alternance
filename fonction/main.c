#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "tableau.h"
#include "cases.h"
#include "vider_buffer.h"

int main(){
    int n = 4,
        m = 4,
        ok,
        sauvegarde_effectue = 1,
        cases_vides,
        fusion_oui_non;      
    tableau ta, prec;
    cases c;
    char dir;

    srand(time(NULL));

    cases_vides = 16;
    ta = initialisation_tableau(n, m);  
    spawn_2_cases(&c, &ta);
    cases_vides = 14;
    aff_tableau(ta);
    ok = 1;
    while(ok == 1){
        printf("nombre cases vides : %d \n", cases_vides);
        if(cases_vides == 0 && peux_bouger(&ta, &prec) == 1){
            printf("Vous avez perdu ! \n");
            exit(EXIT_FAILURE);
        }
        if(sauvegarde_effectue == 1){
            printf("Entrez une direction (z/q/s/d) pour déplacer et a pour quitter : "); /* permet de différencier le 1er coup des suivants */
        }
        else{
            printf("Entrez une direction (z/q/s/d) pour déplacer, r pour revenir en arrière et a pour quitter : ");
        }
        dir = getchar(); /* récupère le caractère pour choisir quoi faire  */
        viderBuffer(); /* remet le caractère récupérer à vide */

        if(dir == 'a'){
            printf("Au revoir ! \n");
            ok = 0;
        }
        else if(dir == 'z' || dir == 'q' || dir == 's' || dir == 'd'){
            sauvegarde_tableau(&ta, &prec);
            deplacement_et_fusion(&ta, dir);
            
            if(peux_bouger(&ta, &prec) == 0){
                fusion_oui_non = fusion_effectue(&ta);

                                
                if(fusion_oui_non == 1){
                    cases_vides -= 1;
                }
                
                if(fusion_oui_non == 0 && compte_fusion(&ta) > 1){
                    printf("compte fusion = %d \n", compte_fusion(&ta));
                    cases_vides += compte_fusion(&ta);
                }
                
                spawn_1_cases(&c, &ta);    
                aff_tableau(ta);
                sauvegarde_effectue = 0;
            }
            
            else{
                printf("Pas de mouvements possibles \n");
                aff_tableau(ta);
            }                
        }
        else if(dir == 'r' && sauvegarde_effectue == 0){
            printf("Tableau précédent \n");
            retour_arriere(&ta, &prec);
            aff_tableau(ta);
        }
        else if(dir == 'r' && sauvegarde_effectue == 1){
            printf("Vous ne pouvez pas revenir en arrière si vous n'avez pas joué de coups. \n");
        }
        else{
            printf("Mauvaise direction : entrez bien 'z', 'q', 's', ou 'd' \n");
        }
    }
    exit(EXIT_SUCCESS);
}
    