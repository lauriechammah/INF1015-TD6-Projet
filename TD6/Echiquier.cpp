/**
 * Nom :         Echiquier.h
 * Description : Implémentation de l'échiquier
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Echiquier.h"
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

    // Retirer une pièce capturée si présente
    auto it = std::remove_if(pieces_.begin(), pieces_.end(),
        [&](const std::unique_ptr<Piece>& p) {
            return p->getPosition() == destination;
        });
    pieces_.erase(it, pieces_.end());

    // Simuler le mouvement pour vérifier qu'on ne se met pas en échec
    Position anciennePos = piece->getPosition();
    piece->setPosition(destination);

    if (estEnEchec(piece->estBlanc())) {
        // Mouvement illégal : on se met en échec
        piece->setPosition(anciennePos);
        return false;
    }

    return true;
}

bool Echiquier::estEnEchec(bool estBlanc) const
{
    const Piece* roi = trouverRoi(estBlanc);
    if (roi == nullptr)
        return false;

    // Vérifier si une pièce adverse peut atteindre le roi
    for (const auto& piece : pieces_) {
        if (piece->estBlanc() != estBlanc) {
            if (piece->estMouvementValide(roi->getPosition(), *this))
                return true;
        }
    }
    return false;
}