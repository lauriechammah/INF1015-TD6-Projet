/**
 * Nom :         Position.hpp
 * Description : Represente une position sur l'echiquier
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#pragma once

struct Position {
    int ligne = 0;
    int colonne = 0;

    bool estValide() const {
        return ligne >= 0 && ligne < 8 && colonne >= 0 && colonne < 8;
    }

    bool operator==(const Position& autre) const {
        return ligne == autre.ligne && colonne == autre.colonne;
    }

    bool operator!=(const Position& autre) const {
        return !(*this == autre);
    }
};