/**
 * Nom :         Echiquier.hpp
 * Description : Gere l'etat du jeu et les verifications d'echec
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#pragma once
#include "Piece.hpp"
#include <vector>
#include <memory>

namespace modele {

class Echiquier {
public:
    Echiquier() = default;

    void ajouterPiece(std::unique_ptr<Piece> piece);
    bool deplacerPiece(const Position& source, const Position& destination);

    const Piece* getPiece(const Position& position) const;
    bool estEnEchec(bool estBlanc) const;

    const std::vector<std::unique_ptr<Piece>>& getPieces() const { return pieces_; }

    void vider();

private:
    std::vector<std::unique_ptr<Piece>> pieces_;

    Piece* getPieceMutable(const Position& position);
    const Piece* trouverRoi(bool estBlanc) const;
};

}