Bienvenue sur le github du projet IN104 d'apprentissage par renforcement, par Paul-Louis "Zhymra" ETIENNEY et Etienne "PoulpobossMG" CHARNAVEl!

Ce projet est divisé en deux dossiers, le dossier principal Q_learning_mur et le dossier "version 3D" Q_learning_3D.
Chacun de ces dossiers est indépendant (évidemment, c'est une simple adaptation donc 90% du code est redondant).

Le dossier Q_learning_mur couvre les deux méthodes d'exploration que sont Epsilon-Greedy et Boltzmann-exploration, ainsi que les deux types d'algorithmes Q-learning et Sarca. Le main est toujours dans dfs.c.

Le dossier Q_learning_3D contient notre "changement d'environnement". Il s'agit également d'une résolution de labyrinthe, mais cette fois-ci en 3D : il n'y a plus un unique étage, mais 4, et l'algorithme doit trouver un chemin du départ de l'étage 1 à l'arrivée de l'étage 4. Il s'agit donc d'une adaptation assez proche du problème initial de labyrinthe 2D.

De façon générale, nous avons rencontré quelques soucis avec la réalisation d'un makefile fonctionnel. Le makefile de Q_learning_mur marche désormais, mais uniquement au bout de deux essais : il ne semble pas compiler au premier car il ne trouve pas la fonction clean. Il n'y a pas de makefile fonctionnel pour Q_learning_3D. Durant la majorité du projet, nous avons opté pour une simple compilation (gcc +les différents noms de fichiers les uns après les autres) afin de pouvoir avancer dans les autres aspects et réaliser un algorithme qui fonctionne.

Enfin, pour les détails de la compilation de chaque dossier, veuillez lire chacun de leurs ReadMe.
