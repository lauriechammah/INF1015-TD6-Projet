/**
 * Nom :         Echiquier.cpp
 * Description : Implementation de l'echiquier
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#include "Echiquier.hpp"
#include <algorithm>

void Echiquier::ajouterPiece(std::unique_ptr<Piece> piece)
{
    pieces_.push_back(std::move(piece));
}

const Piece* Echiquier::getPiece(const Position& position) const
{
    for (const auto& piece : pieces_) {
        if (piece->getPosition() == position)
            return piece.get();
    }
    return nullptr;
}

Piece* Echiquier::getPieceMutable(const Position& position)
{
    for (auto& piece : pieces_) {
        if (piece->getPosition() == position)
            return piece.get();
    }
    return nullptr;
}

const Piece* Echiquier::trouverRoi(bool estBlanc) const
{
    for (const auto& piece : pieces_) {
        if (piece->estBlanc() == estBlanc && piece->getSymbole() == (estBlanc ? "R" : "r"))
            return piece.get();
    }
    return nullptr;
}

bool Echiquier::deplacerPiece(const Position& source, const Position& destination)
{
    Piece* piece = getPieceMutable(source);
    if (piece == nullptr)
        return false;

    if (!piece->estMouvementValide(destination, *this))
        return false;

    // Sauvegarder la piece capturee avant de la retirer
    std::unique_ptr<Piece> pieceCapturee;
    auto it = std::find_if(pieces_.begin(), pieces_.end(),
        [&](const std::unique_ptr<Piece>& p) {
            return p->getPosition() == destination;
        });
    if (it != pieces_.end()) {
        pieceCapturee = std::move(*it);
        pieces_.erase(it);
        piece = getPieceMutable(source);
    }

    Position anciennePos = piece->getPosition();
    piece->setPosition(destination);

    if (estEnEchec(piece->estBlanc())) {
        piece->setPosition(anciennePos);
        if (pieceCapturee)
            pieces_.push_back(std::move(pieceCapturee));
        return false;
    }

    return true;
}

bool Echiquier::estEnEchec(bool estBlanc) const
{
    const Piece* roi = trouverRoi(estBlanc);
    if (roi == nullptr)
        return false;

    for (const auto& piece : pieces_) {
        if (piece->estBlanc() != estBlanc) {
            if (piece->estMouvementValide(roi->getPosition(), *this))
                return true;
        }
    }
    return false;
}