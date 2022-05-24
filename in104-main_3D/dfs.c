#include "mazeEnv.h"
#include "qlearningmur.h"

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

