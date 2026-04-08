/**
 * Nom :         DeplacementTemp.hpp
 * Description : Classe RAII qui deplace une piece temporairement.
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"
#include "Position.hpp"

namespace modele {

class DeplacementTemp {
public:
    DeplacementTemp(Piece* piece, const Position& nouvellePosition)
    : piece_(piece), anciennePosition_(piece->getPosition())
    {
        piece_->setPosition(nouvellePosition);
    }

    ~DeplacementTemp()
    {
        piece_->setPosition(anciennePosition_);
    }

    DeplacementTemp(const DeplacementTemp&) = delete;
    DeplacementTemp& operator=(const DeplacementTemp&) = delete;

private:
    Piece* piece_;
    Position anciennePosition_;
};

}
