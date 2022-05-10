#include "mazeEnv.h"
#include "functions.h"

/*	/!\ placeholders - à compléter /!\	*/
double alpha = 0.5;
double gamma_temp =1;
double epsilon=0.15;

double max_Q(double Q[][cols][4], int ligne, int colonne){
	double max=-100;
	for (int i=0;i<4;++i){
		if (Q[ligne][colonne][i]>max){
			max = Q[ligne][colonne][i];
		}
	}
	return (max);
}

action epsi_greed(double Q[][cols][4], int ligne, int colonne){
  double ran_nb = rand()/RAND_MAX;
  enum action action_choisie;
  if (ran_nb<epsilon) {
    action_choisie = rand()%4;
  } 
  else {
    double max=-100;
    int ind_max = 0;
	  for (int i=0;i<4;++i){
		  if (Q[ligne][colonne][i]>max){
			  max = Q[ligne][colonne][i];
        ind_max = i;
	 	  }
	  }
  action_choisie = ind_max;
  } 
  return(action_choisie);
}
                                   
    

double* Q() {
	double Q[rows][cols][4];
		for (int i=0;i<rows;++i) {
			for (int j=0;j<cols;++j) {
				for (int k=0;k<4;++k) {
					Q[i][j][k]=0;
				}
			}
		}
	int etat_ligne=start_row;
	int etat_col=start_col;
	int ancienne_ligne;
	int ancienne_col;
	action prochaine_action;
	envOutput nouvel_etat;
	int i =0;
	while (nouvel_etat.done!=1 && i<200) {
		
		
		prochaine_action=epsi_greed(Q,etat_ligne,etat_col); 
		nouvel_etat = maze_step(prochaine_action);
		
		/* on update les anciennes valeurs */
		ancienne_ligne=etat_ligne;
		ancienne_col=etat_col;
		
		/* on update les nouvelles valeurs */
		etat_ligne=nouvel_etat.new_row;
		etat_col=nouvel_etat.new_col;

		/* on update Q */
		Q[ancienne_ligne][ancienne_col][prochaine_action] = Q[ancienne_ligne][ancienne_col][prochaine_action] + alpha*(nouvel_etat.reward + gamma_temp*max_Q(Q,etat_ligne,etat_col) - Q[ancienne_ligne][ancienne_col][prochaine_action]);
		i=i+1;
	
	}
	if (nouvel_etat.done==1) {
		printf("%d Tu es magnifique",i);
	}
	else {
		printf("Tu es une merde");
	}
    }
