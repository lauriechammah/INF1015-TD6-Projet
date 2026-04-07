/**
 * Nom :         Cavalier.h
 * Description : Implémentation du Cavalier
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Cavalier.h"
#include "Echiquier.h"
#include <cmath>

Cavalier::Cavalier(Position position, bool estBlanc)
    : Piece(position, estBlanc)
{
}

bool Cavalier::estMouvementValide(const Position& destination,
                                   const Echiquier& echiquier) const
{
    if (!destination.estValide())
        return false;

    int dLigne   = std::abs(destination.ligne   - position_.ligne);
    int dColonne = std::abs(destination.colonne - position_.colonne);

    // Le cavalier se déplace en «L» : 2+1 ou 1+2
    bool formeL = (dLigne == 2 && dColonne == 1) ||
                  (dLigne == 1 && dColonne == 2);

    if (!formeL)
        return false;

    // Le cavalier saute par-dessus les pièces, vérifier seulement la destination
    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Cavalier::getSymbole() const
{
    return estBlanc_ ? "C" : "c";
}