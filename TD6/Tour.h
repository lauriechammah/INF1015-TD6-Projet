/**
 * Nom :         Tour.h
 * Description : Pièce Tour — se déplace en ligne droite (horizontal/vertical)
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.h"

class Tour : public Piece {
public:
    Tour(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
                             const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};
