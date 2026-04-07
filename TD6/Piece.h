/**
 * Nom :         Piece.h
 * Description : Classe abstraite de base pour les pièces d'échecs
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Position.h"
#include <string>

class Echiquier;  // Déclaration anticipée (forward declaration)

class Piece {
public:
    Piece(Position position, bool estBlanc);
    virtual ~Piece() = default;

    // Méthode virtuelle pure : chaque sous-classe définit ses mouvements
    virtual bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const = 0;

    virtual std::string getSymbole() const = 0;

    // Getters (petits ? inline dans le .h)
    Position getPosition() const { return position_; }
    bool     estBlanc()    const { return estBlanc_; }

    void setPosition(const Position& position);

protected:
    Position position_;
    bool     estBlanc_;
};