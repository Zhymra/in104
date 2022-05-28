#include "dfs.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "mazeEnv.h"
#include "functions.h"
#include "qlearningmur.h"
#include "choix_action.h"

action epsi_greed(){
    /*Au hasard selon epsilon on choisit soi d'avancer dans une direction au hasard soi de choisir la valeur qui maximise Q*/
    double ran_nb = ((double) rand())/RAND_MAX;
    enum action action_choisie;
    action_choisie = env_action_sample();

    if (ran_nb>epsilon) {
        int max=-100;
        for (int i=0;i<number_actions;++i){
            if (Q[state_row_true(state_row)][state_col][state_etage][i]>max){
                max = Q[state_row_true(state_row)][state_col][state_etage][i];
              
        action_choisie = i;
          }
      }
  } 
  return(action_choisie);
}


action Bolt(){
  
  /* nombre flottant aléatoire entre 0 et 1 */
	double ran_nb = ((double) rand())/RAND_MAX;
  
  /* calcul des probabilités des différentes actions */ 
  double proba[number_actions];
  double expo_total = 0;
  for (int i=0;i<number_actions;++i){
    proba[i] = exp(Q[state_row_true(state_row)][state_col][state_etage][i]);
    expo_total = expo_total + proba[i];
  }
  for (int i=0;i<number_actions;++i){
    proba[i] = proba[i]/expo_total;
  }
  
  /* choix de l'action selon les probas */  
	enum action action_choisie;
  int i=0;
  int done = 0;
  while (i<number_actions && done == 0){
    if (ran_nb<=proba[i]){
      done = 1;
    } else {
      ran_nb = ran_nb - proba[i];
      i = i+1;
    }
  }
  
  /* vérification du bon fonctionnement */
  if (done==1){
    action_choisie = i;
  } else {
    printf("Erreur dans Boltzmann_exploration\n");
    action_choisie = env_action_sample();
  }
  return(action_choisie);
}
