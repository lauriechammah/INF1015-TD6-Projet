/**
 * Nom :         Tour.h
 * Description : Implémentation de la Tour
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Tour.h"
#include "Echiquier.h"
#include <algorithm>

Tour::Tour(Position position, bool estBlanc)
    : Piece(position, estBlanc)
{
}

bool Tour::estMouvementValide(const Position& destination,
                               const Echiquier& echiquier) const
{
    if (!destination.estValide())
        return false;

    int dLigne   = destination.ligne   - position_.ligne;
    int dColonne = destination.colonne - position_.colonne;

    // La tour se déplace en ligne droite uniquement
    if (dLigne != 0 && dColonne != 0)
        return false;
    if (dLigne == 0 && dColonne == 0)
        return false;

    // Vérifier qu'aucune pièce ne bloque le chemin
    int stepLigne   = (dLigne   != 0) ? (dLigne   > 0 ? 1 : -1) : 0;
    int stepColonne = (dColonne != 0) ? (dColonne > 0 ? 1 : -1) : 0;

    Position courante = { position_.ligne + stepLigne,
                          position_.colonne + stepColonne };

    while (courante != destination) {
        if (echiquier.getPiece(courante) != nullptr)
            return false;
        courante.ligne   += stepLigne;
        courante.colonne += stepColonne;
    }

    // La case destination ne doit pas contenir une pièce alliée
    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Tour::getSymbole() const
{
    return estBlanc_ ? "T" : "t";
}