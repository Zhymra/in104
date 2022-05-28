#include "dfs.h"
#include "mazeEnv.h"
#include "qlearningmur.h"


int main(){
   printf("Veuillez rentrer les valeurs des doubles suivants : alpha,gamma,epsilon\n");
   scanf("%lf,%lf,%lf",&alpha,&gamma_temp,&epsilon);
   printf("Choisissez le type d'algorithme : 0 pour Qlearning, 1 pour Sarsa\n");
   scanf("%d",&type_algo);
   printf("Choisissez l'algorithme de choix : 0 pour Epsilon-greedy, 1 pour Boltzmann-exploration\n");
   scanf("%d",&type_choix); 
   maze_make("maze.txt");

   printf("%d, %d, %d \n", rows, cols, etages);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   tableau();
   maze_render();
    //printf("%d , %d , %d, %d , %d , %d",start_row,start_col,start_etage,goal_row,goal_col,goal_etage);

   free(Q);
   free(maze);
   return 0;
}


