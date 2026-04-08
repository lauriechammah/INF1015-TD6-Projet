/**
 * Nom :         Roi.cpp
 * Description : Implementation du Roi
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "Roi.hpp"
#include "Echiquier.hpp"
#include <cmath>

namespace modele {

int Roi::compteur_ = 0;

Roi::Roi(Position position, bool estBlanc)
    : Piece(position, estBlanc)
{
    if (compteur_ >= 2) 
    {
        throw RoiEnTropException(
            "Impossible de creer un 3e roi : il y en a deja 2 sur l'echiquier.");
    }
    ++compteur_;
}

Roi::~Roi()
{
    --compteur_;
}

int Roi::getNombreRois()
{
    return compteur_;
}

bool Roi::estMouvementValide(const Position& destination,
    const Echiquier& echiquier) const
{
    if (!destination.estValide())
        return false;

    int dLigne = std::abs(destination.ligne - position_.ligne);
    int dColonne = std::abs(destination.colonne - position_.colonne);

    if (dLigne > 1 || dColonne > 1)
        return false;
    if (dLigne == 0 && dColonne == 0)
        return false;

    const Piece* cible = echiquier.getPiece(destination);
    if (cible != nullptr && cible->estBlanc() == estBlanc_)
        return false;

    return true;
}

std::string Roi::getSymbole() const
{
    return estBlanc_ ? "♔" : "♚";
}

}