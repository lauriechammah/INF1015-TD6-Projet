/**
 * Nom :         Piece.hpp
 * Description : Classe abstraite de base pour les pieces d'echecs
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Position.hpp"
#include <string>

class Echiquier;  // Declaration anticipee (forward declaration)

class Piece {
public:
    Piece(Position position, bool estBlanc);
    virtual ~Piece() = default;

    // Methode virtuelle pure : chaque sous-classe definit ses mouvements
    virtual bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const = 0;

    virtual std::string getSymbole() const = 0;

    // Getters
    Position getPosition() const { return position_; }
    bool     estBlanc()    const { return estBlanc_; }

    void setPosition(const Position& position);

protected:
    Position position_;
    bool     estBlanc_;
};