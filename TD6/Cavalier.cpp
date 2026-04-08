/**
 * Nom :         Cavalier.cpp
 * Description : Implementation du Cavalier
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "Cavalier.hpp"
#include "Echiquier.hpp"
#include <cmath>

namespace modele {

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

    bool formeL = (dLigne == 2 && dColonne == 1) ||
                  (dLigne == 1 && dColonne == 2);

    if (!formeL)
        return false;

    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Cavalier::getSymbole() const
{
    return estBlanc_ ? "♘" : "♞";
}

}