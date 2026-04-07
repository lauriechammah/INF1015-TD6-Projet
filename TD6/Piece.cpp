/**
 * Nom :         Piece.h
 * Description : Implémentation de la classe Piece
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "Piece.h"

Piece::Piece(Position position, bool estBlanc)
    : position_(position), estBlanc_(estBlanc)
{
}

void Piece::setPosition(const Position& position)
{
    position_ = position;
}