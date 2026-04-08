/**
 * Nom :         Cavalier.hpp
 * Description : Piece Cavalier - se deplace en L
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"

namespace modele {

class Cavalier : public Piece {
public:
    Cavalier(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
                             const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};

}