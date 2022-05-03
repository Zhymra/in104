#include "mazeEnv.h"

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
	int i =0;
	action prochaine_action;
	envoutput a;
	while (etat_ligne!=goal_row || etat_col!=goal_col && i<100) {
		a = maze_step(prochaine_action);
		etat_ligne=a.new_row;
		etat_col=a.new_col;
		prochaine_action=epsilon_greedy(etat_ligne,etat_col,Q);
		Q[etat,tab[2],
		
	}
    }
