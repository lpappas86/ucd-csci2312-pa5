#include "Food.h"

const char Gaming::Food::FOOD_ID = 'F';

Gaming::Food::Food(const Game & g, const Position & p, double capacity) : Resource(g,p,capacity)
{
	//TODO:
}

Gaming::Food::~Food()
{
	//TODO:
}

void Gaming::Food::print(std::ostream & os) const
{
	os << FOOD_ID /*<< std::left << std::setw(4) << std::setfill(' ') */ << __id;
}
