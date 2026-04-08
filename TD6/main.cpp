/**
 * Nom :         main.cpp
 * Description : 
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "Echiquier.hpp"
#include "Roi.hpp"
#include "Tour.hpp"
#include "Cavalier.hpp"
#include "FenetreJeu.hpp"

#include <QApplication>
#include <iostream>
#include <cassert>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

void executerTests()
{
	using std::cout;
	cout << "=== Tests preliminaires ===\n\n";

	// --- Tests du Roi ---
	{
		modele::Echiquier e;
		e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{4, 4}, true));

		assert(e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{5, 5}, e));
		assert(e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{4, 5}, e));
		assert(!e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{6, 4}, e));
		assert(!e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{4, 4}, e));

		cout << "  Roi : OK\n";
	}

	// --- Tests de la Tour ---
	{
		modele::Echiquier e;
		e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{0, 0}, true));
		e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{3, 3}, false));

		assert(e.getPiece(modele::Position{0, 0})->estMouvementValide(modele::Position{0, 7}, e));
		assert(e.getPiece(modele::Position{0, 0})->estMouvementValide(modele::Position{7, 0}, e));
		assert(!e.getPiece(modele::Position{0, 0})->estMouvementValide(modele::Position{3, 3}, e));

		modele::Echiquier e2;
		e2.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{0, 0}, true));
		e2.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{0, 3}, true));
		assert(!e2.getPiece(modele::Position{0, 0})->estMouvementValide(modele::Position{0, 5}, e2));

		cout << "  Tour : OK\n";
	}

	// --- Tests du Cavalier ---
	{
		modele::Echiquier e;
		e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{4, 4}, true));

		assert(e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{6, 5}, e));
		assert(e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{2, 3}, e));
		assert(e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{3, 6}, e));
		assert(!e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{4, 6}, e));
		assert(!e.getPiece(modele::Position{4, 4})->estMouvementValide(modele::Position{6, 6}, e));

		cout << "  Cavalier : OK\n";
	}

	// --- Test d'échec ---
	{
		modele::Echiquier e;
		e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{0, 0}, true));
		e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{7, 7}, false));
		e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{5, 7}, true));

		assert(!e.estEnEchec(true));
		assert(e.estEnEchec(false));

		cout << "  Echec : OK\n";
	}

	// --- Test déplacement qui se met en échec ---
	{
		modele::Echiquier e;
		e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{0, 0}, true));
		e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{1, 0}, true));
		e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{7, 0}, false));

		bool resultat = e.deplacerPiece(modele::Position{1, 0}, modele::Position{1, 5});
		assert(!resultat);

		cout << "  Protection echec : OK\n";
	}

	cout << "\n=== Tous les tests passent ===\n\n";
}

int main(int argc, char *argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	executerTests();

	vue::FenetreJeu fenetre;
	fenetre.show();
	return app.exec();
}
