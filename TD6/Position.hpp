/**
 * Nom :         Position.hpp
 * Description : Represente une position sur l'echiquier
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once

namespace modele {

constexpr int TAILLE_ECHIQUIER = 8;

struct Position {
    int ligne = 0;
    int colonne = 0;

    bool estValide() const {
        return ligne >= 0 && ligne < TAILLE_ECHIQUIER 
            && colonne >= 0 && colonne < TAILLE_ECHIQUIER;
    }

    bool operator==(const Position& autre) const {
        return ligne == autre.ligne && colonne == autre.colonne;
    }

    bool operator!=(const Position& autre) const {
        return !(*this == autre);
    }
};

}