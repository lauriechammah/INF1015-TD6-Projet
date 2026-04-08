/**
 * Nom :         Piece.hpp
 * Description : Classe abstraite de base pour les pieces d'echecs
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once
#include "Position.hpp"
#include <string>

namespace modele {

class Echiquier;

class Piece {
public:
    Piece(Position position, bool estBlanc);
    virtual ~Piece() = default;

    virtual bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const = 0;

    virtual std::string getSymbole() const = 0;

    Position getPosition() const { return position_; }
    bool     estBlanc()    const { return estBlanc_; }

    void setPosition(const Position& position);

protected:
    Position position_;
    bool     estBlanc_;
};

}