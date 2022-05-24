prog: dfs.o functions.o mazeEnv.o  qlearningmur.o
	gcc dfs.o functions.o mazeEnv.o qlearningmur.o
dfs.o: dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c
functions.o: functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c
mageEnv.o: mageEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c
qlearningmur.o: qlearningmur.c qlearningmur.h
	gcc -c -Wall -Werror -Wfatal-errors qlearningmur.c
	clean
	rm -f prog dfs.o functions.o mazeEnv.o qlearningmur.o

