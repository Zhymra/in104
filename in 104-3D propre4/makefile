prog: dfs.o functions.o mazeEnv.o  qlearningmur.o choix_action.o
	gcc dfs.o functions.o mazeEnv.o qlearningmur.o choix_action.o -lm -g
dfs.o: dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c
functions.o: functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c
mageEnv.o: mageEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c
qlearningmur.o: qlearningmur.c qlearningmur.h
	gcc -c -Wall -Werror -Wfatal-errors qlearningmur.c
choix_action.o: choix_action.c choix_action.h
	gcc -c -Wall -Werror -Wfatal-errors choix_action.c 
	clean
	rm -f prog dfs.o functions.o mazeEnv.o qlearningmur.o choix_action.o

