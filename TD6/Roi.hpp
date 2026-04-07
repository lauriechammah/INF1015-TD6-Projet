/**
 * Nom :         Roi.hpp
 * Description : Piece Roi - se deplace d'une case dans toutes les directions
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"

class Roi : public Piece {
public:
    Roi(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};