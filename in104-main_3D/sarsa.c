#include "mazeEnv.h"
#include "functions.h"
#include "sarsa.h"
#include <time.h>
#include <stdlib.h>



/*	/!\ placeholders - à compléter /!\	*/
double alpha = 0.9;
double gamma_temp =1;
double epsilon=0.1;

void init_Q() {
	   Q = (double****)malloc((rows + 1) * sizeof(double***));
 
	    if (Q == NULL)
	    {
	        fprintf(stderr, "Out of memory");
	        exit(0);
	    }
 
	    for (int i = 0; i < rows + 1; i++)
	    {
	        Q[i] = (double***)malloc((cols +1) * sizeof(double**));
	 
	        if (Q[i] == NULL)
	        {
	            fprintf(stderr, "Out of memory");
	            exit(0);
	        }
	 
	        for (int j = 0; j < cols + 1; j++)
	        {
	            Q[i][j] = (double**)malloc((etages +1) * sizeof(double*));
	            if (Q[i][j] == NULL)
	            {
	                fprintf(stderr, "Out of memory");
	                exit(0);
	            }
		        for (int k = 0; k < 6 + 1; k++)
		        {
		            Q[i][j][k] = (double*)malloc(6+1 * sizeof(double));
		            if (Q[i][j][k] == NULL)
		            {
		                fprintf(stderr, "Out of memory");
		                exit(0);
		            }
		        }
	        }
	    }
	 
	    for (int i = 0; i < rows+1; i++)
	    {
	        for (int j = 0; j < cols + 1; j++)
	        {
	            for (int k = 0; k < etages +1 ; k++) {
	                for (int l = 0; l < 6+1; l++) {
	                	Q[i][j][k][l] = 0;
	            	}
	            }
	        }
	    }	
}

double max_Q(int ligne, int colonne, int etage){
	double max=-1000;
	for (int i=0;i<6;++i){
		if (Q[ligne][colonne][etage][i]>max){
			max = Q[ligne][colonne][etage][i];
		}	
	}
	return (max);
}

envOutput maze_step_mur(action a){
    double reward = -1;
    int done = 0;
    envOutput stepOut;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row_true(state_row); 
    stepOut.new_etage = etage(state_row); 
    int test_state_row=state_row; 
    int test_state_col=state_col;
    int test_state_etage = etage(state_row); 

    if (a==north){
       test_state_row = max(0,state_row -1);
    }else if (a==south){
       test_state_row = min(rows-1,state_row+1);
    }else if (a==east){
       test_state_col = min(cols-1,state_col +1);
    }else if (a==west){
       test_state_col = max(0,state_col -1);
    }else if (a==up){
       test_state_etage = min(etages-1,etage(state_row) +1);
       test_state_row=state_row + (test_state_etage -etage(state_row))*12;
    }else if (a==down){
       test_state_etage = max(0,etage(state_row) -1);
       test_state_row=state_row + (test_state_etage -etage(state_row))*12;
    }

    if (maze[test_state_row][test_state_col]!='+') {
        state_row=test_state_row;
        state_col=test_state_col;
        state_etage=test_state_etage;
        stepOut.new_col = test_state_col;
        stepOut.new_row = test_state_row; 
        stepOut.new_etage = test_state_etage; 
    }

    if((state_row_true(state_row) == goal_row) && (state_col == goal_col) && (etage(state_row) == goal_etage) ){
       reward = 5;
       done   = 1;
    }

    stepOut.reward = reward;
    stepOut.done   = done;

   return stepOut;
}


action epsi_greed(){
	double ran_nb = ((double) rand())/RAND_MAX;
	enum action action_choisie;
  if (ran_nb<epsilon) {
    action_choisie = env_action_sample();
  } 
  else {
    int max=-1000;
    int ind_max = env_action_sample();
	  for (int i=0;i<6;++i){
		  if (Q[state_row_true(state_row)][state_col][state_etage][i]>max){
			  max = Q[state_row_true(state_row)][state_col][state_etage][i];
			  
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
		int ancien_etage;
		action prochaine_action;
		action ancienne_action;
		envOutput nouvel_etat;
		srand(time(NULL));
		int i;
		int w=0;

	for (int u=0;u<5000;++u) { 
		i = 0;
		nouvel_etat.done=0;
		state_row=start_row;
		state_col=start_col;
		state_etage=start_etage;
		prochaine_action=epsi_greed();
		if (w>100) {
			epsilon=0.005;
		}
		while (nouvel_etat.done!=1 && i<10000) {

			ancien_etage=etage(state_row);
			ancienne_ligne=state_row_true(state_row);
			ancienne_col=state_col;		

			nouvel_etat = maze_step_mur(prochaine_action);

			ancienne_action=prochaine_action;
			prochaine_action=epsi_greed(); 


			/* on update Q */
			Q[ancienne_ligne][ancienne_col][ancien_etage][ancienne_action] = 
			Q[ancienne_ligne][ancienne_col][ancien_etage][ancienne_action] +
			alpha*(nouvel_etat.reward + 
			gamma_temp*Q[state_row_true(state_row)][state_col][etage(state_row)][prochaine_action]- 
			Q[ancienne_ligne][ancienne_col][ancien_etage][ancienne_action]);		

			i=i+1;


		}
		if (nouvel_etat.done==1) {
			printf("Tu es magnifique %d \n",i);
			w=w+1;
		}
		else {
			printf("Tu es une merde\n");
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
  for (int i = 0; i < rows + 1; i++)
    {
        for (int j = 0; j < cols + 1; j++)
        {
            for (int k = 0; k < etages + 1; k++)
       		 {
                printf("%f ", max_Q(i,j,k));
           
       		 }
        printf("\n");
    }	}
   printf("%f %f %f %f %f %f\n", Q[6][3][0][3],Q[6][3][0][2],Q[6][3][0][1],Q[6][3][0][0],Q[6][3][0][4],Q[6][3][0][5]);
}
