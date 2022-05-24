Ce projet est divisé en deux dossiers, le dossier principal in104-main_mur et le dossier "version 3D" in104-main_3D.
Chacun de ces dossiers est indépendant (évidemment, c'est une simple adaptation donc 90% du code est redondant).

Le dossier in104-main__mur couvre les deux méthodes d'exploration que sont Epsilon-Greedy et Boltzmann-exploration, ainsi que les deux types d'algorithmes Q-learning et Sarsa. Le main est toujours dans dfs.c.

Le dossier in104-main_3D contient notre "changement d'environnement". Il s'agit également d'une résolution de labyrinthe, mais cette fois-ci en 3D : il n'y a plus un unique étage, mais 4, et l'algorithme doit trouver un chemin du départ de l'étage 1 à l'arrivée de l'étage 4. Il s'agit donc d'une adaptation assez proche du problème initial de labyrinthe 2D.

Enfin, pour les détails de la compilation de chaque dossier, veuillez lire chacun de leurs ReadMe.
