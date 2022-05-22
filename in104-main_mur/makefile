prog: dfs.o functions.o mazeEnv.o 
	gcc dfs.o functions.o mazeEnv.o qlearning.o
dfs.o: dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c
functions.o: functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c
mageEnv.o: mageEnv.c mageEnv
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c
qlearning.o: qlearning.c qlearning
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c
	clean
	rm -f prog dfs.o functions.o mazeEnv.o qlearning.o

