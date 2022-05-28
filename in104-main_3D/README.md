Ceci est le ReadMe détaillant le dossier in104-main_3D.

Le labyrinthe à mettre dans maze.txt doit comprendre : les caractéristiques "ligne, colonne, etage" du labyrinthe en première ligne. On représente un étage comme une salle de taille (ligne * colonne) qu'on met après un saut de  ligne de la salle précèdente.

Pour compiler le code, il faut écrire la commande " gcc -Wall -Werror -Wfatal-errors dfs.c functions.c mazeEnv.c qlearningmur.c choix_action.c -lm ",- ou utiliser le makefile avec la commande "make" dans le terminal (utilisez la 2 fois si les .o n'ont pas encore été créés).

Le terminal vous demande alors de rentrer les paramètres (gamma,alpha,epsilon) que vous voulez dans l'ordre demandé et séparés d'une virgule. Puis vous devez faire le choix sur l'utilisation ou non de sarsa, puis l'utilisation des algorithmes de choix Epsilon-greedy ou Boltzmann-exploration.
Quelques suggestions : (0.9,1,0.1) pour Qlearning et (0.7,1,0.05) pour Sarsa.

Le fichier choix_action.c contient les codes des algorithmes de choix Epsilon-greedy et Boltzmann-exploration. Les fonctions correspondantes sont respectivement nommées epsi_greed() et Bolt().

Le noyau du code est dans la fonction qlearningmur.c . Ce fichier contient en réalité à la fois l'algorithme de Q-learning et l'algorithme Sarsa, placés en if/else pour pouvoir choisir le type d'algorithme. La fonction qui initialise le tableau Q est également dans ce fichier.
La fonction principale de ce fichier est tableau(), qui réalise le calcul de Q, itération après itération. Cette fonction est donc divisée en deux morceaux par un premier if/else, pour différencier Sarsa du Q-learning. Chacune de ces options est également divisée en deux morceaux : une première boucle for qui laisse l'algorithme évoluer dans le labyrinthe pendant de nombreuses itérations et met constamment à jour le tableau Q, puis un dernier tour dans lequel l'algorithme suit toujours le maximum du tableau Q final et note le nombre de coups. Cette dernière itération passe par un choix en Espilon-greedy avec Epsilon = 0 pour toujours prendre le coup considéré comme optimal, et place des '.' dans les différentes cases jusqu'à l'arrivée. 

Le fichier dfs.c, comme au tout début du projet, contient le main. Il demande à l'utilisateur de rentrer les paramètres et le mode d'algorithme choisis par des scanf() successifs, affiche le labyrinthe vide une première fois, puis exécute la fonction tableau() de qlearningmur.c . Il affiche alors alors max de chaque case du tableau Q final, puis de nouveau le labyrinthe, cette fois-ci avec le trajet optimal de l'algorithme tracé par des '.' . Le nombre de coups final est également affiché.
