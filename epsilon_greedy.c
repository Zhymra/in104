#include "mazeEnv.h"
#include "functions.h"

action epsi_greed(double epsilon, int ligne, int colonne, double Q[][cols][4]){
  double ran_nb = rand()/RAND_MAX; /* placeholders: double entre 0 et 1 randomized */;
  if (ran_nb<epsilon) {
    action action_choisie = action(rand()%4);
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
  action action_choisie = action(ind_max);
  } 
  return(action_choisie);
}
                                   
    
