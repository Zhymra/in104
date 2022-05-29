#include "dfs.h"
#include "mazeEnv.h"
#include "functions.h"
#include "qlearningmur.h"
#include "choix_action.h"
#include <time.h>
#include <stdlib.h>






/*Création du tableau de Qlearning, defini comme variable dans le qlearningmur.h*/             
void init_Q() {
       Q = (double*****)malloc((rows) * sizeof(double****));
 
        if (Q == NULL)
        {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
 
        for (int i = 0; i < rows; i++)
        {
            Q[i] = (double****)malloc((cols) * sizeof(double***));
     
            if (Q[i] == NULL)
            {
                fprintf(stderr, "Out of memory");
                exit(0);
            }
     
            for (int j = 0; j < cols; j++)
            {
                Q[i][j] = (double***)malloc((etages) * sizeof(double**));
                if (Q[i][j] == NULL)
                {
                    fprintf(stderr, "Out of memory");
                    exit(0);
                }
                for (int k = 0; k < etages; k++)
                {
                    Q[i][j][k] = (double**)malloc(etages4 * sizeof(double*));
                    if (Q[i][j][k] == NULL)
                    {
                        fprintf(stderr, "Out of memory");
                        exit(0);
                    }

                    for (int l = 0; l < etages4; l++)
                    {
                        Q[i][j][k][l] = (double*)malloc(number_actions * sizeof(double));
                        if (Q[i][j][k][l] == NULL)
                        {
                            fprintf(stderr, "Out of memory");
                            exit(0);
                        }
                    }
                }
            }
        }
     
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                for (int k = 0; k < etages ; k++) 
                {
                    for (int l = 0; l < etages4; l++) 
                    {
                        for (int m = 0; m < number_actions; m++) 
                        {
                            Q[i][j][k][l][m] = 0;
                        }
                    }
                }
            }
        }   
}

/*algorithme de recherche de maximum*/
double max_Q(int ligne, int colonne, int etage, int etage4){
    double max=-100;
    for (int i=0;i<number_actions;++i){
        if (Q[ligne][colonne][etage][etage4][i]>max){
            max = Q[ligne][colonne][etage][etage4][i];
        }   
    }
    return (max);
}

void tableau() {
        init_Q();
        int ancienne_ligne;
        int ancienne_col;
        int ancien_etage;
        int ancien_etage4;
        action prochaine_action;
        action ancienne_action;
        envOutput nouvel_etat;
        srand(time(NULL));
        int i;
        /*initialisation des paramètres*/
        int nombre_essais=1000;
        int nombre_coups_max=5000;
        /*on choisit si on utilise du sarsa ou du q learning*/
        if (type_algo==0) {
            for (int u=0;u<nombre_essais;++u) { 
                /*a partir d'ici on relance une nouvelle exploration du labyrinthe*/
                i = 0;
                nouvel_etat.done=0;
                state_row=start_etage*rows+start_row;
                state_col=start_etage4*cols+start_col;
                state_etage=start_etage;
                state_etage4=start_etage4;
                /*si le robot fait trop d'explorations (i>nombre_coups_max) on l'arrete*/
                while (nouvel_etat.done!=1 && i<nombre_coups_max) {
                    if (u<nombre_essais-1) {

                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        ancien_etage=state_etage;
                        ancien_etage4=state_etage4;
                        
                        if (type_choix==0){
                        	prochaine_action=epsi_greed();
                        } else {
                        	prochaine_action=Bolt(); 
                        }

                        nouvel_etat = maze_step_mur(prochaine_action);

                        /*surveille que l'algorithme ne rencontre pas de mur*/
                        if (maze[ancienne_ligne][ancienne_col]=='+') {
                            printf("aie\n");
                        }

                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action] = 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*max_Q(state_row_true(state_row),state_col_true(state_col),state_etage,state_etage4) - 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action]);
                        i=i+1;
                    }
                    /*on affiche les cases choisies sur le dernier passage*/
                    /*sur le dernier essai on n'admet plus de hasard et on prend le meilleur chemin selon le tableau Q*/
                    else {
                        epsilon=0;
                        printf("%d, %d, %d, %d et ensuite l'action : ", state_row_true(state_row),state_col_true(state_col), state_etage, state_etage4);
                        
                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        ancien_etage=state_etage;
                        ancien_etage4=state_etage4;
                        /* on place les points sur le labyrinthe */
                        if (i!=0){
                        	maze[state_row][state_col]='.';
                        } 
                        prochaine_action=epsi_greed(); 
                        printf("%d qui donne : ", prochaine_action);
                    
                        nouvel_etat = maze_step_mur(prochaine_action);


                        printf("%d, %d, %d, %d\n", state_row_true(state_row),state_col_true(state_col), state_etage, state_etage4);

                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action] = 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action] +
                        alpha*(nouvel_etat.reward + gamma_temp*max_Q(state_row_true(state_row),state_col_true(state_col),state_etage,state_etage4) - 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][prochaine_action]);
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
                state_row=start_etage*rows+start_row;
                state_col=start_etage4*cols+start_col;
                state_etage=start_etage;
                state_etage4=start_etage4;
                prochaine_action=epsi_greed();
                while (nouvel_etat.done!=1 && i<nombre_coups_max) {
                    if (u<nombre_essais-1) {
                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        ancien_etage=state_etage;
                        ancien_etage4=state_etage4;    
                        nouvel_etat = maze_step_mur(prochaine_action);

                        /*surveille que l'algorithme ne rencontre pas de mur*/
                        if (maze[ancienne_ligne][ancienne_col]=='+') {
                            printf("aie\n");
                        }

                        
                        ancienne_action=prochaine_action;
                        if (type_choix==0){
                        	prochaine_action=epsi_greed();
                        } else {
                        	prochaine_action=Bolt(); 
                        }


                        /* on update Q via sarsa*/
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action] = 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action]+
                        alpha*(nouvel_etat.reward + gamma_temp*Q[state_row_true(state_row)][state_col_true(state_col)][state_etage][state_etage4][prochaine_action]- 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action]);        

                        i=i+1;
                    }
                    else {
                        epsilon=0;
                        printf("on était en %d, %d, %d, %d et on passe en ",state_row_true(state_row),state_col_true(state_col), state_etage, state_etage4);
                        ancienne_ligne=state_row;
                        ancienne_col=state_col;
                        ancien_etage=state_etage;
                        ancien_etage4=state_etage4; 
                        /* on place les points sur le labyrinthe */
                        if (i!=0){
                        	maze[state_row][state_col]='.';
                        }   
                        nouvel_etat = maze_step_mur(prochaine_action);
                        printf("%d, %d, %d, %d\n", state_row_true(state_row),state_col_true(state_col), state_etage, state_etage4);
                        ancienne_action=prochaine_action;
                        prochaine_action=epsi_greed(); 

                        /* on update Q */
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action] = 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action]+
                        alpha*(nouvel_etat.reward + gamma_temp*Q[state_row_true(state_row)][state_col_true(state_col)][state_etage][state_etage4][prochaine_action]- 
                        Q[state_row_true(ancienne_ligne)][state_col_true(ancienne_col)][ancien_etage][ancien_etage4][ancienne_action]);       

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

  }  
  /* print le tableau
  for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (int k = 0; k < number_actions; k++) {
                printf("%f ", Q[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
   
    //on print la valeur maximale de chaque case de Q
  for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
           
                printf("%f ", max_Q(i,j));
           
        }
        printf("\n");
    }
   
}*/
