/**
 * Nom :         Roi.h
 * Description : Implémentation du Roi
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Roi.h"
#include "Echiquier.h"
#include <cmath>

Roi::Roi(Position position, bool estBlanc)
    : Piece(position, estBlanc)
{
}

bool Roi::estMouvementValide(const Position& destination,
    const Echiquier& echiquier) const
{
    if (!destination.estValide())
        return false;

    int dLigne = std::abs(destination.ligne - position_.ligne);
    int dColonne = std::abs(destination.colonne - position_.colonne);

    // Le roi bouge d'exactement 1 case dans n'importe quelle direction
    if (dLigne > 1 || dColonne > 1)
        return false;
    if (dLigne == 0 && dColonne == 0)
        return false;

    // Vérifier que la destination n'est pas occupée par une pièce alliée
    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Roi::getSymbole() const
{
    return estBlanc_ ? "R" : "r";
}