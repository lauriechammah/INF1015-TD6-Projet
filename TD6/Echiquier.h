/**
 * Nom :         Echiquier.h
 * Description : Gère l'état du jeu et les vérifications d'échec
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.h"
#include <vector>
#include <memory>

class Echiquier {
public:
    Echiquier() = default;

    void ajouterPiece(std::unique_ptr<Piece> piece);
    bool deplacerPiece(const Position& source, const Position& destination);

    const Piece* getPiece(const Position& position) const;
    bool estEnEchec(bool estBlanc) const;

    const std::vector<std::unique_ptr<Piece>>& getPieces() const { return pieces_; }

private:
    std::vector<std::unique_ptr<Piece>> pieces_;

    Piece* getPieceMutable(const Position& position);
    const Piece* trouverRoi(bool estBlanc) const;
};
