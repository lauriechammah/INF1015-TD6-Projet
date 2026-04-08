/**
 * Nom :         Piece.cpp
 * Description : Implementation de la classe Piece
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "Piece.hpp"

namespace modele {

Piece::Piece(Position position, bool estBlanc)
    : position_(position), estBlanc_(estBlanc)
{
}

void Piece::setPosition(const Position& position)
{
    position_ = position;
}

}