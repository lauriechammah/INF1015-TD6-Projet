/**
 * Nom :         Tour.hpp
 * Description : Piece Tour - se deplace en ligne droite (horizontal/vertical)
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"

class Tour : public Piece {
public:
    Tour(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
                             const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};