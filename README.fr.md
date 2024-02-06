[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/minishell/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/minishell/blob/master/README.fr.md)

*Langage de programmation C* • *Gestion des processus* • *Descripteurs de fichiers et redirections* • *Parsing exhaustif* • *Gestion des signaux* • *Gestion des erreurs* • *Gestion de la mémoire* • *Conformité aux normes* • *Automatisation de la compilation avec Makefile*

# Minishell

Ce projet consiste à créer un petit bash pour apprendre les processus et les descripteurs de fichiers.

| Clé | Valeur |
|--|--|
| Nom du programme | minishell |
Langage | C
Fichiers à rendre | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re` 
Fonct. externes | `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

**Fonctionnalités Bash POSIX prises en charge**:
- Afficher un prompt lorsqu'on attend une nouvelle commande.
- Avoir un historique fonctionnel.
- Rechercher et lancer le bon exécutable (basé sur la variable `PATH` ou en utilisant un chemin relatif ou absolu).
- Ne pas utiliser plus d'une variable globale (pour indiquer un signal reçu). Cette approche garantit que le gestionnaire de signal n'accédera pas aux structures de données principales.
- `’` (guillemet simple) qui empêche le shell d'interpréter les métacaractères dans la séquence citée.
- `"` (guillemet double) qui empêche le shell d'interpréter les métacaractères dans la séquence citée, sauf pour `$` (signe dollar).
- Redirections :
	- `<` redirige l'entrée.
	- `>` redirige la sortie.
	- `<<` heredoc : redirige l'entrée à partir d'une chaîne suivant la commande.
    - `>>` redirige la sortie en mode append.
- `|` (caractère de pipe). La sortie de chaque commande dans le pipeline est connectée à l'entrée de la commande suivante via un pipe.
- `$` : Variables d'environnement (`$` suivi d'une séquence de caractères devant se développer en leurs valeurs).
- `$?` qui doit se développer en le statut de sortie du pipeline en avant-plan le plus récemment exécuté.
- En mode interactif :
    - `ctrl-C` affiche une nouvelle invite sur une nouvelle ligne.
    - `ctrl-D` quitte le shell.
    - `ctrl-\` ne fait rien.
- Les commandes internes suivantes :
    - `echo` avec l'option `-n`
    - `cd` avec seulement un chemin relatif ou absolu
    - `pwd` sans options
    - `export` sans options
    - `unset` sans options
    - `env` sans options ni arguments
    - `exit` sans options

> La fonction `readline()` peut causer des fuites de mémoire, mais aucune des fuites n'est reachable en dehors de la bibliothèque `readline()` elle-même.

## Utilisation


```shell
git clone git@github.com:nfauconn/minishell.git
cd minishell/Projet
make
```

```shell
./minishell
```