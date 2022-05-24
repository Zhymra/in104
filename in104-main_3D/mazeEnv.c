#include "mazeEnv.h" 
#include "functions.h"

void alloc_maze(){
     maze = malloc(etages*rows * sizeof(char*));

     for(int i=0; i<rows*etages; i++) {
         maze[i] = malloc(cols * sizeof(char*));
     }
}

void maze_make(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");

     if (file) {
  
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      rows_s[rows_i]=c;
                      rows_i++;
               } else {
                      cols_s[cols_i]= c;
                      cols_i++;
               }
         }
     }
  
     alloc_maze();

     for (int i=0; i<rows*etages; i++){
         for (int j=0; j < cols; j++){
             c = getc(file);
             
             if (c=='\n'){
                 c = getc(file);
             }
            
             maze[i][j] = c;
         }
     }

     fclose(file);
}


void maze_render(){
     for (int i=0; i<rows*etages; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", maze[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}


void maze_reset(){
     state_row = start_row;
     state_col = start_col;
     state_etage=start_etage;
}

action env_action_sample(){
  return (enum action)(rand() % 6);
}

