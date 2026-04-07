/**
 * Nom :         Roi.h
 * Description : Pièce Roi — se déplace d'une case dans toutes les directions
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.h"

class Roi : public Piece {
public:
    Roi(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};
