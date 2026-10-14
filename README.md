# My_LS

## Description
`my_ls` est une reproduction simple de la commande UNIX `ls`. Ce projet en langage C permet de lister le contenu d'un répertoire avec une option de tri alphabétique et la gestion des fichiers cachés.

## Fonctionnalités
* Affichage de la liste des fichiers et dossiers du répertoire courant.
* Tri alphabétique automatique des résultats.
* Gestion de l'option `-a` pour afficher les fichiers cachés (commençant par un point `.`).
* Compilation sécurisée avec les flags stricts (`-Wall -Wextra -Werror`).

## Prérequis
* Un environnement Linux / WSL (Windows Subsystem for Linux).
* Un compilateur C (`gcc`) et `make`.

### Installation des outils (sur Ubuntu / WSL)
```bash
sudo apt update
sudo apt install build-essential -y
