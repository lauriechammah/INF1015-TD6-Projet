/**
 * Nom :         Tour.cpp
 * Description : Implementation de la Tour
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "Tour.hpp"
#include "Echiquier.hpp"
#include <algorithm>

namespace modele {

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

    if (dLigne != 0 && dColonne != 0)
        return false;
    if (dLigne == 0 && dColonne == 0)
        return false;

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

    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Tour::getSymbole() const
{
    return estBlanc_ ? "♖" : "♜";;
}

}