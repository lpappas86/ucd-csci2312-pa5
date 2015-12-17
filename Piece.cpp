#include"Piece.h"

unsigned int Gaming::Piece::__idGen = 0;

Gaming::Piece::Piece(const Game & g, const Position & p) : __game(g)
{
	__id = ++__idGen;
	__position = p;
	__finished = false;
}

Gaming::Piece::~Piece()
{
	//TODO: Put something here
}

bool Gaming::operator<(const Piece &p1, const Piece &p2)
{
	if (p1.__id < p2.__id)
		return true;
	return false;
}

std::ostream & Gaming::operator<<(std::ostream & os, const Piece & piece)
{
	if (&piece == nullptr)
		os << std::left /* << std::setw(5) << std::setfill(' ')*/ << "";
	else
		piece.print(os);
	return os;
}
