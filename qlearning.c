#include "mazeEnv.h"
#include "functions.h"

/*	/!\ placeholders - à compléter /!\	*/
double alpha = 0.5;
double gamma_temp =1;

double max_Q(double*** Q, int ligne, int colonne){
	double max=-100;
	for (int i=0;i<4;++i){
		if (Q[ligne][colonne][i]>max){
			max = Q[ligne][colonne][i];
		}
	}
	return (max);
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
	while (nouvel_etat.done!=1 && i<100) {
		"placeholder - à compléter"
		prochaine_action = left;
		/* prochaine_action=epsilon_greedy(etat_ligne,etat_col,Q); */
		nouvel_etat = maze_step(prochaine_action);
		
		/* on update les anciennes valeurs */
		ancienne_ligne=etat_ligne;
		ancienne_col=etat_col;
		
		/* on update les nouvelles valeurs */
		etat_ligne=nouvel_etat.new_row;
		etat_col=nouvel_etat.new_col;

		/* on update Q */
		Q[ancienne_ligne,ancienne_col,prochaine_action] = Q[ancienne_ligne,ancienne_col,prochaine_action] + alpha*(nouvel_etat.reward + gamma_temp*max_Q(Q,etat_ligne,etat_col) - Q[ancienne_ligne,ancienne_col,prochaine_action])
		
	}
    }
