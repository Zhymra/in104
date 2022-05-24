#include "dfs.h"
#include "mazeEnv.h"
#include "qlearningmur.h"


int dfs(int row, int col){
    int* current = &visited[row][col];

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}

void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
          }
     }
     maze[start_row][start_col]= 's';
}

int main(){
   printf("Veuillez rentrer les valeurs des doubles suivants : alpha,gamma,epsilon\n");
   scanf("%lf,%lf,%lf",&alpha,&gamma_temp,&epsilon);
   printf("Choisissez le type d'algorithme : 0 pour Qlearning, 1 pour Sarsa\n");
   scanf("%d",&type_algo);
   printf("Choisissez l'algorithme de choix : 0 pour Epsilon-greedy, 1 pour Boltzmann-exploration\n");
   scanf("%d",&type_choix); 
   maze_make("maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   tableau();
   maze_render();
   free(Q);
   free(maze);
   free(visited);
   return 0;
}


