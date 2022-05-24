#include "mazeEnv.h"
#include "functions.h"
#include "qlearningmur.h"
#include "choix_action.h"
#include <time.h>
#include <stdlib.h>






/*Création du tableau de Qlearning, defini comme variable dans le qlearningmur.h*/             
void init_Q() {
       Q = (double***)malloc((rows + 1) * sizeof(double**));
 
    if (Q == NULL)
    {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
 
    for (int i = 0; i < rows + 1; i++)
    {
        Q[i] = (double**)malloc((cols +1) * sizeof(double*));
 
        if (Q[i] == NULL)
        {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
 
        for (int j = 0; j < cols + 1; j++)
        {
            Q[i][j] = (double*)malloc(5 * sizeof(double));
            if (Q[i][j] == NULL)
            {
                fprintf(stderr, "Out of memory");
                exit(0);
            }
        }
    }
 
    for (int i = 0; i < rows +1; i++)
    {
        for (int j = 0; j < cols + 1; j++)
        {
            for (int k = 0; k < 5; k++) {
                Q[i][j][k] = 0;
            }
        }
    }   
}

/*algorithme de recherche de maximum*/
double max_Q(int ligne, int colonne){
    double max=-100;
    for (int i=0;i<4;++i){
        if (Q[ligne][colonne][i]>max){
            max = Q[ligne][colonne][i];
        }   
    }
    return (max);
}

void tableau() {
        init_Q();
        int ancienne_ligne;
        int ancienne_col;
        action prochaine_action;
        action ancienne_action;
        envOutput nouvel_etat;
        srand(time(NULL));
        int i;
        /*initialisation des paramètres*/
        alpha = 0.9;
        gamma_temp =1;
        epsilon=0.01;
        int nombre_essais=2000;
        int nombre_coups_max=1000;
        int sarsa=1;
        /*on choisit si on utilise du sarsa ou du q learning*/
        if (sarsa==0) {
            for (int u=0;u<nombre_essais;++u) { 
                /*a partir d'ici on relance une nouvelle exploration du labyrinthe*/
                i = 0;
                nouvel_etat.done=0;
                state_row=start_row;
                state_col=start_col;
                /*si le robot fait trop d'explorations (i>nombre_coups_max) on l'arrete*/
                while (nouvel_etat.done!=1 && i<nombre_coups_max) {
                    if (u<nombre_essais-1) {

                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        prochaine_action=epsi_greed(); 

                        nouvel_etat = maze_step_mur(prochaine_action);

                        /*surveille que l'algorithme ne rencontre pas de mur*/
                        if (maze[ancienne_ligne][ancienne_col]=='+') {
                            printf("aie\n");
                        }

                        Q[ancienne_ligne][ancienne_col][prochaine_action] = Q[ancienne_ligne][ancienne_col][prochaine_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*max_Q(state_row,state_col) - 
                        Q[ancienne_ligne][ancienne_col][prochaine_action]);
                        i=i+1;
                    }
                    /*on affiche les cases choisies sur le dernier passage*/
                    /*sur le dernier essai on n'admet plus de hasard et on prend le meilleur chemin selon le tableau Q*/
                    else {
                        epsilon=0;
                           
                        /* on place les points sur le labyrinthe */
                        if (i!=0){
                        	maze[state_row][state_col]='.';
                        } 
                           
                        printf("%d , %d et ensuite l'action : ", state_row, state_col);
                        
                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        prochaine_action=epsi_greed(); 
                           
                        printf("%d qui donne : ", prochaine_action);
                        nouvel_etat = maze_step_mur(prochaine_action);
                        printf("%d , %d\n", state_row, state_col);

                        Q[ancienne_ligne][ancienne_col][prochaine_action] = Q[ancienne_ligne][ancienne_col][prochaine_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*max_Q(state_row,state_col) - 
                        Q[ancienne_ligne][ancienne_col][prochaine_action]);
                        i=i+1;
                    }
                }
                    if (nouvel_etat.done==1) {
                        printf("Sortie du labyrinthe trouvée en %d coups\n",i);
                    }
                    else {
                        printf("Sortie non trouvée\n");
                    }            }
        }
        else {
            for (int u=0;u<nombre_essais;++u) { 
                i = 0;
                nouvel_etat.done=0;
                state_row=start_row;
                state_col=start_col;
                prochaine_action=epsi_greed(state_row,state_col);
                while (nouvel_etat.done!=1 && i<nombre_coups_max) {
                    if (u<nombre_essais-1) {
                        ancienne_ligne=state_row;
                        ancienne_col=state_col;     
                        nouvel_etat = maze_step_mur(prochaine_action);

                        /*surveille que l'algorithme ne rencontre pas de mur*/
                        if (maze[ancienne_ligne][ancienne_col]=='+') {
                            printf("aie\n");
                        }

                        
                        ancienne_action=prochaine_action;
                        prochaine_action=epsi_greed(); 


                        /* on update Q via sarsa*/
                        Q[ancienne_ligne][ancienne_col][ancienne_action] = Q[ancienne_ligne][ancienne_col][ancienne_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*Q[state_row][state_col][prochaine_action]- 
                        Q[ancienne_ligne][ancienne_col][ancienne_action]);        

                        i=i+1;
                    }
                    else {
                        epsilon=0;
                           
                        /* on place les points sur le labyrinthe */
                        if (i!=0){
                        	maze[state_row][state_col]='.';
                        }
                        
                        printf("on était en %d , %d et on passe en ", state_row, state_col);
                        ancienne_ligne=state_row;
                        ancienne_col=state_col; 
                        
                        nouvel_etat = maze_step_mur(prochaine_action);
                        printf("%d , %d\n", state_row, state_col);
                        ancienne_action=prochaine_action;
                        prochaine_action=epsi_greed(state_row,state_col); 

                        /* on update Q */
                        Q[ancienne_ligne][ancienne_col][ancienne_action] = Q[ancienne_ligne][ancienne_col][ancienne_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*Q[state_row][state_col][prochaine_action]- 
                        Q[ancienne_ligne][ancienne_col][ancienne_action]);        

                        i=i+1;                        
                    }                 
                }        
                    if (nouvel_etat.done==1) {
                        printf("Sortie du labyrinthe trouvée en %d coups\n",i);
                    }
                    else {
                        printf("Sortie non trouvée\n");
                    }               }
        }

    
  /* print le tableau
  for (int i = 0; i < rows + 1; i++)
    {
        for (int j = 0; j < cols + 1; j++)
        {
            for (int k = 0; k < 5; k++) {
                printf("%f ", Q[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
   */
    /*on print la valeur maximale de chaque case de Q*/
  for (int i = 0; i < rows + 1; i++)
    {
        for (int j = 0; j < cols + 1; j++)
        {
           
                printf("%f ", max_Q(i,j));
           
        }
        printf("\n");
    }
   
}
