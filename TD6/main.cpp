/**
 * Nom :         main.cpp
 * Description : Point d'entrée avec tests préliminaires et lancement de l'interface
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Echiquier.h"
#include "Roi.h"
#include "Tour.h"
#include "Cavalier.h"
#include "FenetreJeu.h"
#include <QApplication>
#include <iostream>
#include <cassert>

void executerTests()
{
    using std::cout;
    cout << "=== Tests preliminaires ===\n\n";

    // --- Tests du Roi ---
    {
        Echiquier e;
        e.ajouterPiece(std::make_unique<Roi>(Position{4, 4}, true));

        // Mouvement valide : 1 case en diagonale
        assert(e.getPiece(Position{4, 4})->estMouvementValide(Position{5, 5}, e));
        // Mouvement valide : 1 case horizontale
        assert(e.getPiece(Position{4, 4})->estMouvementValide(Position{4, 5}, e));
        // Mouvement invalide : 2 cases
        assert(!e.getPiece(Position{4, 4})->estMouvementValide(Position{6, 4}, e));
        // Mouvement invalide : rester sur place
        assert(!e.getPiece(Position{4, 4})->estMouvementValide(Position{4, 4}, e));

        cout << "  Roi : OK\n";
    }

    // --- Tests de la Tour ---
    {
        Echiquier e;
        e.ajouterPiece(std::make_unique<Tour>(Position{0, 0}, true));
        e.ajouterPiece(std::make_unique<Roi>(Position{3, 3}, false)); // Bloqueur

        // Mouvement valide : horizontale
        assert(e.getPiece(Position{0, 0})->estMouvementValide(Position{0, 7}, e));
        // Mouvement valide : verticale
        assert(e.getPiece(Position{0, 0})->estMouvementValide(Position{7, 0}, e));
        // Mouvement invalide : diagonale
        assert(!e.getPiece(Position{0, 0})->estMouvementValide(Position{3, 3}, e));

        // Test blocage : pièce sur le chemin
        Echiquier e2;
        e2.ajouterPiece(std::make_unique<Tour>(Position{0, 0}, true));
        e2.ajouterPiece(std::make_unique<Roi>(Position{0, 3}, true)); // Allié sur le chemin
        assert(!e2.getPiece(Position{0, 0})->estMouvementValide(Position{0, 5}, e2));

        cout << "  Tour : OK\n";
    }

    // --- Tests du Cavalier ---
    {
        Echiquier e;
        e.ajouterPiece(std::make_unique<Cavalier>(Position{4, 4}, true));

        // Mouvements valides en L
        assert(e.getPiece(Position{4, 4})->estMouvementValide(Position{6, 5}, e));
        assert(e.getPiece(Position{4, 4})->estMouvementValide(Position{2, 3}, e));
        assert(e.getPiece(Position{4, 4})->estMouvementValide(Position{3, 6}, e));
        // Mouvement invalide : ligne droite
        assert(!e.getPiece(Position{4, 4})->estMouvementValide(Position{4, 6}, e));
        // Mouvement invalide : diagonale
        assert(!e.getPiece(Position{4, 4})->estMouvementValide(Position{6, 6}, e));

        cout << "  Cavalier : OK\n";
    }

    // --- Test d'échec ---
    {
        Echiquier e;
        e.ajouterPiece(std::make_unique<Roi>(Position{0, 0}, true));
        e.ajouterPiece(std::make_unique<Roi>(Position{7, 7}, false));
        e.ajouterPiece(std::make_unique<Tour>(Position{5, 7}, true)); // Tour blanche menace roi noir

        assert(!e.estEnEchec(true));  // Blanc pas en échec
        assert(e.estEnEchec(false));  // Noir en échec

        cout << "  Echec : OK\n";
    }

    // --- Test déplacement qui se met en échec ---
    {
        Echiquier e;
        e.ajouterPiece(std::make_unique<Roi>(Position{0, 0}, true));
        e.ajouterPiece(std::make_unique<Tour>(Position{1, 0}, true));  // Protège le roi
        e.ajouterPiece(std::make_unique<Tour>(Position{7, 0}, false)); // Tour noire vise la colonne

        // Déplacer la tour alliée hors de la colonne exposerait le roi
        bool resultat = e.deplacerPiece(Position{1, 0}, Position{1, 5});
        assert(!resultat);

        cout << "  Protection echec : OK\n";
    }

    cout << "\n=== Tous les tests passent ===\n\n";
}

int main(int argc, char* argv[])
{
    executerTests();

    QApplication app(argc, argv);
    FenetreJeu fenetre;
    fenetre.show();
    return app.exec();
}