/**
 * Nom :         Roi.hpp
 * Description : Piece Roi - se deplace d'une case dans toutes les directions
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"
#include "RoiEnTropException.hpp"

namespace modele {

class Roi : public Piece {
public:
    Roi(Position position, bool estBlanc);
    ~Roi();

    bool estMouvementValide(const Position& destination,
        const Echiquier& echiquier) const override;

    std::string getSymbole() const override;

    static int getNombreRois();

private:
        static int compteur_;
};

}