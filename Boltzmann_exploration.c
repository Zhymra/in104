#include <math.h>
#include <stdio.h>

action Bolt_exp(int ligne, int colonne){
  
  /* nombre flottant aléatoire entre 0 et 1 */
	double ran_nb = ((double) rand())/RAND_MAX;
  
  /* calcul des probabilités des différentes actions */ 
  double proba[4];
  double expo_total = 0;
  for (int i=0;i<4;++i){
    proba[i] = exp(Q[ligne][colonne][i]);
    expo_total = expo_total + proba[i];
  }
  for (int i=0;i<4;++i){
    proba[i] = proba[i]/expo_total;
  }
  
  /* choix de l'action selon les probas */  
	enum action action_choisie;
  int i=0;
  int done = 0;
  while (i<4 && done = 0){
    if (ran_nb<=proba[i]){
      done = 1;
    } else {
      ran_nb = ran_nb - proba[i];
      i = i+1;
    }
  }
  
  /* vérification du bon fonctionnement */
  if (done=1){
    action_choisie = i;
  } else {
    printf("Erreur dans Boltzmann_exploration\n");
    action_choisie = env_action_sample();
  }
  return(action_choisie);
}
