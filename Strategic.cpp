#include "Strategic.h"

const char Gaming::Strategic::STRATEGIC_ID = 'T';

Gaming::Strategic::Strategic(const Game & g, const Position & p, double energy, Strategy * s) : Agent(g,p,energy)
{
	__strategy = s;
}

Gaming::Strategic::~Strategic()
{
	//TODO: Fill in
}

void Gaming::Strategic::print(std::ostream & os) const
{
	os << STRATEGIC_ID /*<< std::left << std::setw(4) << std::setfill(' ') */ << __id;
}

Gaming::ActionType Gaming::Strategic::takeTurn(const Surroundings & s) const
{
	return (*__strategy)(s);
}


