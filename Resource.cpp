#include "Resource.h"

const double Gaming::Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Gaming::Resource::Resource(const Game & g, const Position & p, double capacity) : Piece(g,p)
{
	__capacity = capacity;
}

Gaming::Resource::~Resource()
{
	//TODO:
}

double Gaming::Resource::consume()
{
	//TODO:
	return 0.0;
}

void Gaming::Resource::age()
{
	__capacity /= RESOURCE_SPOIL_FACTOR;
}

Gaming::ActionType Gaming::Resource::takeTurn(const Surroundings & s) const
{
	return STAY;
}

Gaming::Piece & Gaming::Resource::operator*(Piece & other)
{
	// TODO: 
	return other;
}

Gaming::Piece & Gaming::Resource::interact(Agent *)
{
	finish();
	return *this;
}

Gaming::Piece & Gaming::Resource::interact(Resource *res)
{
	finish();
	return *this;
}
