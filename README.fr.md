Bien sûr, voici la traduction en français :

# Projet : Minishell

## 🏁 Objectif 🏁

Ce projet consiste à écrire notre implémentation de bash pour découvrir les processus et les descripteurs de fichiers.

## 🚀 Utilisation 🚀

```shell
git clone git@github.com:nfauconn/minishell.git
cd minishell/Projet
make
```

```shell
./minishell
```

## 💡 Compétences 💡

- **Compréhension des opérations du Shell** :
   - Connaissance approfondie de l'exécution des commandes shell
   - Familiarité avec les fonctionnalités d'un shell standard

- **Gestion des processus** :
   - Compréhension de la création et de la gestion des processus à l'aide d'appels système tels que `fork`, `execve`, `wait`, et `signal`
   - Connaissance de la communication inter-processus et de la gestion de plusieurs processus

- **Descripteur de fichier et redirection** :
   - Gestion des descripteurs de fichiers pour les opérations d'entrée/sortie
   - Maîtrise de la mise en œuvre des redirections (`>`, `>>`, `<`, `<<`) et des pipes (`|`)

- **Gestion des signaux** :
   - Compétences dans la gestion des signaux pour le contrôle des processus (`ctrl-C`, `ctrl-D`, `ctrl-\`)
   - Compréhension de la manière d'écrire des programmes robustes qui gèrent les signaux de manière élégante

- **Analyse syntaxique et exécution des commandes** :
    - Compétences dans l'analyse de l'entrée de l'utilisateur et l'exécution des commandes en conséquence
    - Compréhension de la manière de gérer différents types d'entrées utilisateur, y compris l'expansion des variables d'environnement et les citations

- **Gestion des modes interactif et non interactif** :
    - Expérience dans la gestion du comportement du shell en modes interactif et non interactif

- **Programmation en C** :
   - Maîtrise du langage C, compréhension de sa syntaxe et de sa sémantique. Nous avons vraiment approfondi notre rigueur en programmation en C avec ce projet
   - Capacité à écrire un code efficace, maintenable et réutilisable

- **Gestion de la mémoire** :
   - Compréhension approfondie de l'allocation et de la libération dynamique de la mémoire
   - Capacité à prévenir et à gérer les fuites de mémoire et à assurer une utilisation efficace de la mémoire

- **Gestion des erreurs et conformité aux normes** :
   - Capacité à écrire un code qui gère robustement les erreurs et les cas exceptionnels
   - Adhésion aux normes et standards de codage pour la lisibilité et la maintenabilité

## 📋 Instructions du Projet 📋

### Instructions Communes

- **Langage** : Le projet doit être écrit en C.
- **Conformité aux Normes** : Le code doit adhérer aux normes de l'école.
- **Gestion des erreurs** : Les programmes ne doivent pas se terminer de manière inattendue (par exemple, faute de segmentation, erreur de bus, double libération). De tels incidents rendront le projet non fonctionnel et entraîneront une note de 0.
- **Gestion de la mémoire** : Toute la mémoire allouée sur le tas doit être correctement libérée. Les fuites de mémoire ne sont pas tolérées.
- **Exigences du Makefile** :
   - Doit compiler les fichiers sources pour obtenir le résultat requis avec les flags `-Wall`, `-Wextra`, et `-Werror`.
   - Ne doit pas relier à nouveau.

### Règles

| | |
|--|--|
| Nom du programme | minishell |
Fichiers à rendre | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re`
Arguments | 
Fonctions externes | `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close `, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`
Libft autorisé | Oui
Description | Écrire un shell

Le shell doit :
- Afficher une invite en attendant une nouvelle commande.
- Avoir un historique fonctionnel.
- Rechercher et lancer le bon exécutable (en fonction de la variable `PATH` ou en utilisant un chemin relatif ou absolu).
- Éviter d'utiliser plus d'une variable globale pour indiquer un signal reçu. Cette approche garantit que le gestionnaire de signaux n'accédera pas aux structures de données principales.
	> Cette variable globale ne peut fournir aucune autre information ou accès aux données que le numéro d'un signal reçu. Par conséquent, l'utilisation de structures de type "norme" dans le domaine global est interdite.

- Ne pas interpréter les citations non fermées ou les caractères spéciaux qui ne sont pas requis par le sujet tels que `\` (antislash) ou `;` (point-virgule).
- Gérer `’` (apostrophe) qui devrait empêcher le shell d'interpréter les métacaractères dans la séquence citée.
- Gérer `"` (guillemet) qui devrait empêcher le shell d'interpréter les métacaractères dans la séquence citée, à l'exception de `$` (signe dollar).
- Implémenter les redirections :
	- `<` devrait rediriger l'entrée.
	- `>` devrait rediriger la sortie.
	- `<<` devrait être donné un délimiteur, puis lire l'entrée jusqu'à ce qu'une ligne contenant le délimiteur soit vue (*heredoc*). Cependant, il n'est pas nécessaire de mettre à jour l'historique.
    - `>>` devrait rediriger la sortie en mode ajout.
- Implémenter les pipes (caractère `|`). La sortie de chaque commande dans le pipeline est connectée à l'entrée de la commande suivante via un pipe.
- Gérer les variables d'environnement (`$` suivi d'une séquence de caractères) qui devraient se développer en leurs valeurs.
- Gérer `$?` qui devrait se développer en le statut de sortie du pipeline de premier plan le plus récemment exécuté.
- Gérer `ctrl-C`, `ctrl-D` et `ctrl-\` qui devraient se comporter comme dans bash.
- En mode interactif :
    - `ctrl-C` affiche une nouvelle invite sur une nouvelle ligne.
    - `ctrl-D` sort du shell.
    - `ctrl-\` ne fait rien.
- Implémenter les commandes intégrées suivantes :
    - `echo` avec l'option `-n`
    - `cd` avec seulement un chemin relatif ou absolu
    - `pwd` sans options
    - `export` sans options
    - `unset` sans options
    - `env` sans options ou arguments
    - `exit` sans options

> La fonction `readline()` peut causer des fuites de mémoire. Seules autorisées.

> Tout ce qui n'est pas demandé n'est pas nécessaire. Référence = bash