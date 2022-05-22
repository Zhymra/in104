#include "mazeEnv.h"
#include "qlearningmur.h"

/*
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
*/
int main(){
    etages=4;
    rows=4*12;
    cols=20;
    start_row=6;
    start_col=3;
    start_etage=0;
    goal_row=5;
    goal_col=16;
    goal_etage=3;
   maze_make("maze.txt");
   //init_visited();
   maze_reset();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   //dfs(start_row,start_col);
   //add_crumbs();
   //maze_render();
   tableau();

   return 0;
}

