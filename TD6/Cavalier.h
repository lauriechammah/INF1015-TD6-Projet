/**
 * Nom :         Cavalier.h
 * Description : Pièce Cavalier — se déplace en «L»
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.h"

class Cavalier : public Piece {
public:
    Cavalier(Position position, bool estBlanc);

    bool estMouvementValide(const Position& destination,
                             const Echiquier& echiquier) const override;

    std::string getSymbole() const override;
};
