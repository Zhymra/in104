#include "mazeEnv.h"
#include "functions.h"

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
	action ancienne_action;
	envoutput nouvel_etat;
	int i =0;
	while (nouvel_etat.done!=1 && i<100) {
		nouvel_etat = maze_step(prochaine_action);
		/* on update les anciennes valeurs */
		ancienne_ligne=etat_ligne;
		ancienne_col=etat_col;
		ancienne_action=prochaine_action;
		/* on update les nouvelles valeurs */
		etat_ligne=nouvel_etat.new_row;
		etat_col=nouvel_etat.new_col;
		prochaine_action=epsilon_greedy(etat_ligne,etat_col,Q);
		/* on update Q */
		Q[ancienne_ligne,ancienne_col,ancienne_action] = Q[ancienne_ligne,ancienne_col,ancienne_action] + alpha*(nouvel_etat.reward + gamma*
		
	}
    }
