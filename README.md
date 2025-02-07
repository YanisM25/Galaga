GALAGA - Jeu MBED

___Description:

Ce projet est une implémentation du jeu de tir spatial GALAGA sur une carte embarquée MBED. Le jeu utilise un écran LCD C12832, un haut-parleur, et des boutons poussoirs pour le contrôle du vaisseau, du tir et des attaques spéciales.

Matériel Utilisé:

Carte MBED compatible avec les bibliothèques utilisées

Écran LCD C12832 (connecté aux broches p5, p7, p6, p8, p11)

Haut-parleur connecté à p26

___Boutons poussoirs pour le contrôle du jeu :

p15 : Haut

p12 : Bas

p13 : Gauche

p16 : Droite

p14 : Centre

___Fonctionnalités Principales:

Déplacement du vaisseau avec les boutons haut et bas.

Tir de projectiles en appuyant sur le bouton droite.

Génération aléatoire d'ennemis qui se déplacent vers le joueur.

Système de score : chaque ennemi détruit rapporte 10 points.

Détection de collision entre les projectiles et les ennemis.

Attaque spéciale (2 codes de triches) pour une destruction massive d'ennemis.

___Cheat codes :

Mode "Ultimate Attack" en réalisant une séquence de touches spéciale.

Bonus de score (+30 points) via une autre séquence.

Écran de fin de jeu en cas de collision avec un ennemi.

___Commandes du Jeu:

Haut (p15):
Monter le vaisseau

Bas (p12):
Descendre le vaisseau

Droite (p16):
Tirer un projectile

Gauche (p13):
Activer l'attaque spéciale

Centre (p14);
(Utilisation non définie)

___Instructions d'Installation et d'Utilisation:

Compiler et flasher le code sur la carte MBED.

Connecter l'écran LCD et les boutons aux broches définies.

Alimenter la carte et attendre l'affichage du menu.

Naviguer dans le menu avec gauche (commandes) et droite (démarrer).

Jouer en esquivant et tirant sur les ennemis.

Atteindre 20 points pour débloquer le mode cheat.

Éviter la collision avec les ennemis pour ne pas perdre.

___Extensions Possibles:

Ajouter plusieurs niveaux de difficulté.

Intégrer des sons plus variés pour une meilleure immersion.

Optimiser le rendu et le rafraîchissement de l'écran.
