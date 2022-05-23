#include "mazeEnv.h"
#include "functions.h"
#include "qlearningmur.h"
#include <time.h>
#include <stdlib.h>



/*initialisation des paramètres*/
double alpha = 0.9;
double gamma_temp =1;
double epsilon=0.1;

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
                Q[i][j][k] = -0.05;
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
/*Un maze_step qui interdit l'accès aux murs*/
envOutput maze_step_mur(action a){
    int reward = 0;
    int done = 0;
    envOutput stepOut;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 
    int test_state_row=state_row;
    int test_state_col=state_col;


    if (a==up){
       test_state_row = max(0,state_row -1);
    }else if (a==down){
       test_state_row = min(rows-1,state_row +1);
    }else if (a==right){
       test_state_col = min(cols-1,state_col +1);
    }else if (a==left){
       test_state_col = max(0,state_col -1);
    }

    if (maze[test_state_row][test_state_col]!='+') {
        state_row=test_state_row;
        state_col=test_state_col;
        stepOut.new_col = test_state_col;
        stepOut.new_row = test_state_row; 
    }
    if (maze[test_state_row][test_state_col]=='+')  {
    	Q[state_row][state_col][a]= -1000;
    	//printf("%f\n",Q[test_state_row][test_state_col][a] );

    }

    if((state_row == goal_row) && (state_col == goal_col)){
       reward = 1;
       done   = 1;
    }


    stepOut.reward = reward;
    stepOut.done   = done;

   return stepOut;
}

action epsi_greed(int ligne, int colonne){
	/*Au hasard selon epsilon on choisit d'avancer dans une direction au hasard ou de choisir la valeur qui maximise Q*/
	double ran_nb = ((double) rand())/RAND_MAX;
	enum action action_choisie;
  if (ran_nb<epsilon) {
    action_choisie = env_action_sample();
  } 
  else {
    int max=-100;
    int ind_max = env_action_sample();
	  for (int i=0;i<4;++i){
	  	//printf("Q possibles : %f", Q[ligne][colonne][i]);
		  if (Q[ligne][colonne][i]>max){
			  max = Q[ligne][colonne][i];
			  
        ind_max = i;
	 	  }
	 	  //printf("\n");
	  }
  action_choisie = ind_max;
  //printf("random choisi si boucle : %d\n", action_choisie);
  } 
  return(action_choisie);
}


void tableau() {
		init_Q();
		int ancienne_ligne;
		int ancienne_col;
		action prochaine_action;
		envOutput nouvel_etat;
		srand(time(NULL));
		int i;
	
	for (int u=0;u<1000;++u) { 
		/*a partir d'ici on relance une nouvelle exploration du labyrinthe*/
		i = 0;
		nouvel_etat.done=0;
		state_row=start_row;
		state_col=start_col;
		/*si le robot fait trop d'explorations (i>1000) on l'arrete*/
		while (nouvel_etat.done!=1 && i<1000) {
			printf("%d , %d et ensuite l'action : ", state_row, state_col);
			
			ancienne_ligne=state_row;
			ancienne_col=state_col;
			prochaine_action=epsi_greed(state_row,state_col); 
			printf("%d qui donne : ", prochaine_action);
		
			nouvel_etat = maze_step_mur(prochaine_action);
			/* on update les anciennes valeurs */

			
			/* on update les nouvelles valeurs */

			printf("%d , %d\n", state_row, state_col);

			/* on update Q */
			//printf("%f\n", Q[1][0][2] );
			if (maze[ancienne_ligne][ancienne_col]=='+') {
				printf("aie\n");
			}
/*
			if (Q[ancienne_ligne][ancienne_col][prochaine_action]== -1000) {
				//printf("wesh\n");
			}
*/	
			Q[ancienne_ligne][ancienne_col][prochaine_action] = Q[ancienne_ligne][ancienne_col][prochaine_action] +
			alpha*(nouvel_etat.reward + gamma_temp*max_Q(state_row,state_col) - 
			Q[ancienne_ligne][ancienne_col][prochaine_action]) - 0.7;
			i=i+1;
		}
		if (nouvel_etat.done==1) {
			printf("Sortie du labyrinthe trouvée en %d coups\n",i);
		}
		else {
			printf("Sortie non trouvée\n");
		}
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
