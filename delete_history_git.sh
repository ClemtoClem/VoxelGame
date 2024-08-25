#!/bin/bash

# Assurez-vous d'être dans le répertoire du dépôt Git
if [ ! -d ".git" ]; then
    echo "Ce script doit être exécuté à la racine d'un dépôt Git."
    exit 1
fi

# Optionnel: demande de confirmation à l'utilisateur
read -p "Êtes-vous sûr de vouloir supprimer tout l'historique de Git et conserver uniquement l'état actuel? (oui/non) " -r
if [[ ! $REPLY =~ ^[Oo][Uu][Ii]$ ]]; then
    echo "Opération annulée."
    exit 1
fi

# Vérifier si le dépôt est propre (aucune modification non validée)
if [[ -n $(git status --porcelain) ]]; then
    echo "Le dépôt contient des modifications non validées. Veuillez valider ou nettoyer ces modifications avant de continuer."
    exit 1
fi

# Créer une branche temporaire pour le nettoyage
git checkout --orphan temp-branch

# Ajouter tous les fichiers à l'index
git add -A

# Valider avec un nouveau commit
git commit -m "Initial commit avec l'état actuel des fichiers"

# Supprimer toutes les branches et récupérer la branche actuelle
git branch -D main
git branch -m main

# Nettoyer les objets Git non utilisés et réduire la taille du dépôt
git reflog expire --expire=now --all
git gc --prune=now --aggressive

# Pousser la branche nettoyée à l'origine (en forçant)
# Attention : cette étape réécrira l'historique du dépôt sur le serveur distant
git push -f origin main

echo "Historique supprimé et dépôt réinitialisé à un seul commit."
