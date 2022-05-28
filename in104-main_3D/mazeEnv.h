#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>

char** maze;
int rows;
int cols;
int etages;
int start_row;
int start_col;
int start_etage;
int state_row;
int state_col;
int state_etage;
int goal_row;
int goal_col;
int goal_etage;

enum action{
     north,
     south,
     west,
     east,
     up,
     down,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{
  int new_col;
  int new_row;
  int new_etage;
  double reward;
  int done;

};

typedef struct envOutput envOutput;

void alloc_maze();

void maze_make(char* );

void maze_render(); 

void maze_reset();

envOutput maze_step_mur(action a); 

action env_action_sample();

#endif /* MAZEENV_H */
