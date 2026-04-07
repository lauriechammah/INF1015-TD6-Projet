/**
 * Nom :         Piece.cpp
 * Description : Implementation de la classe Piece
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#include "Piece.hpp"

Piece::Piece(Position position, bool estBlanc)
    : position_(position), estBlanc_(estBlanc)
{
}

void Piece::setPosition(const Position& position)
{
    position_ = position;
}