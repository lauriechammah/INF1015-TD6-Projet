# Jeu d'échecs — INF1015 Projet Final

**Auteurs -** CHAMMAH (2451396) et SARKIS (2461138)

## Description

Jeu d'échecs de fins de parties avec interface graphique Qt.
Pièces implémentées : Roi, Tour, Cavalier.

## Prérequis

- Visual Studio 2022
- Qt 6.x (Qt MSVC 64-bit)
- Extension Qt Visual Studio Tools

## Comment compiler et exécuter

1. Ouvrir le fichier `ProjetTestQt.sln` dans Visual Studio
2. S'assurer que la configuration est en **Debug x64**
3. Faire **Générer → Regénérer la solution** (Ctrl+Alt+F7)
4. Lancer avec **Déboguer → Exécuter sans débogage** (Ctrl+F5)

## Comment jouer

1. Au lancement, choisir une position de départ dans le menu :
   - **Partie Standard** — configuration classique avec Rois, Tours et Cavaliers
   - **Duel de Rois** — deux rois face à face pour tester les mouvements de base
   - **Fin de partie (Tours)** — position de fin de partie avec Tours
2. Cliquer sur une pièce de sa couleur pour la sélectionner (cases vertes = mouvements valides)
3. Cliquer sur une case verte pour déplacer la pièce
4. Les blancs jouent en premier, puis les noirs
5. Le jeu détecte les situations d'échec
6. Cliquer **Nouvelle Partie** pour recommencer

## Structure du projet

```
├── Header Files/
│   ├── Cavalier.hpp                  
│   ├── DeplacementTemp.hpp           — Classe RAII
│   ├── Echiquier.hpp                 
│   ├── FenetreJeu.hpp 
│   ├── Piece.hpp                     — Classe abstraite de base
│   ├── Position.hpp                  — Structure de position
│   ├── Roi.hpp                       
│   ├── RoiEnTropException.hpp        — Exception personnalisée
│   ├── tests.hpp                     
│   └── Tour.hpp                      
│
├── Source Files/
│   ├── Cavalier.cpp                  — Cavalier
│   ├── Echiquier.cpp                 — Logique du jeu
│   ├── FenetreJeu.cpp                — Interface graphique Qt
│   ├── main.cpp                      — Point d'entrée du code
│   ├── Piece.cpp                     - Définition de setPosition
│   ├── Roi.cpp                       — Roi (compteur, exception)
│   ├── tests.cpp                     — Déclaration des tests
│   └── Tour.cpp                      — Tour
│
├── Sources Bibliotheques/
│   ├── bibliotheque_cours.cpp                       
│   ├── gtest-all.cc                     
│   └── verification_allocation.cpp                      
│
└── README.md
```

## Tests

Les tests Google Test couvrent le modèle complet (Roi, Tour, Cavalier, Echiquier, RAII).
Ils s'exécutent automatiquement au lancement via l'Explorateur de tests de Visual Studio,
ou affichés dans la console au démarrage du programme.
