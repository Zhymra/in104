#include "mazeEnv.h" 
#include "functions.h"

void alloc_maze(){
     maze = malloc(etages*rows * sizeof(char*));

     for(int i=0; i<rows*etages; i++) {
         maze[i] = malloc(cols*etages4 * sizeof(char*));
     }
}

void maze_make(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     char etages_s[3] ={'\0'};
     char etages4_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int etages_i = 0;
     int etages4_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");

     if (file) {
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
                } else if (c==',') {
                      swap = swap + 1;
                } else if (swap==0) {
                      rows_s[rows_i]=c;
                      rows_i++;
                } else if (swap==1) {
                      cols_s[cols_i]=c;
                      cols_i++;
                } else if (swap==2) {
                      etages_s[etages_i]=c;
                      etages_i++;
                } else {
                      etages4_s[etages4_i]=c;
                      etages4_i++;
                }
         }     
     }

     /* convertir le string en nombre */
     rows = atoi(rows_s);
     cols = atoi(cols_s);
     etages = atoi(etages_s);
     etages4 = atoi(etages4_s);  
     printf("%d ", etages4);   
     alloc_maze();

     for (int i=0; i<rows*etages; i++){
         for (int j=0; j < cols*etages4; j++){
             c = getc(file);

             if (c=='\n'){
                 c = getc(file);
             } else if (c == 's'){
               start_row = state_row_true(i);
               start_col = state_col_true(j);
               start_etage = etage(i);
               start_etage4 = etage4(j);
             } else if ( c == 'g'){
               goal_row = state_row_true(i);
               goal_col = state_col_true(j);
               goal_etage = etage(i);
               goal_etage4 = etage4(j);
             }

             maze[i][j] = c;
         }
     }

     fclose(file);
}


void maze_render(){
     for (int i=0; i<rows*etages; i++) {
         for (int j=0; j< cols*etages4; j++){
             printf("%c ", maze[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}


void maze_reset(){
     state_row = start_etage*rows+start_row;
     state_col = start_etage4*cols+start_col;
     state_etage = start_etage;
     state_etage4 = start_etage4;
}

/*Un maze_step qui interdit l'accès aux murs*/
envOutput maze_step_mur(action a){
    double reward = -1;
    int done = 0;
    envOutput stepOut;
    stepOut.new_col = state_col_true(state_col);
    stepOut.new_row = state_row_true(state_row); 
    stepOut.new_etage = state_etage;
    stepOut.new_etage4 = state_etage4;
    int test_state_col=state_col; 
    int test_state_row=state_row;
    int test_state_etage=state_etage;
    int test_state_etage4=state_etage4;


    if (a==north){
       test_state_row = max(0,state_row -1);
    }else if (a==south){
       test_state_row = min(rows*etages-1,state_row +1);
    }else if (a==east){
       test_state_col = min(cols*etages4-1,state_col +1);
    }else if (a==west){
       test_state_col = max(0,state_col -1);
    }else if (a==up){
       test_state_etage = min(etages-1,etage(state_row) +1);
       test_state_row=state_row + (test_state_etage -etage(state_row))*rows;
    }else if (a==down){
       test_state_etage = max(0,etage(state_row) -1);
       test_state_row=state_row + (test_state_etage -etage(state_row))*rows;
    }else if (a==up4){
       test_state_etage4 = min(etages4-1,etage4(state_col) +1);
       test_state_col=state_col + (test_state_etage4 -etage4(state_col))*cols;
    }else if (a==down4){
       test_state_etage4 = max(0,etage4(state_col) -1);
       test_state_col=state_col + (test_state_etage4 -etage4(state_col))*cols;
    }

    if (maze[test_state_row][test_state_col]!='+') {
        state_row=test_state_row;
        state_col=test_state_col;
        state_etage=test_state_etage;
        state_etage4=test_state_etage4;
        stepOut.new_col = state_col_true(test_state_col);
        stepOut.new_row = state_row_true(test_state_row); 
        stepOut.new_etage = test_state_etage; 
        stepOut.new_etage4 = test_state_etage4; 
    }

    if((state_row_true(state_row) == goal_row) && (state_col_true(state_col) == goal_col) && 
        (etage(state_row) == goal_etage) && (etage4(state_col) == goal_etage4)){
       reward = 5;
       done   = 1;
    }


    stepOut.reward = reward;
    stepOut.done   = done;

   return stepOut;
}


action env_action_sample(){
  return (enum action)(rand() % number_actions);
}

