#include "Simple.h"

const char Gaming::Simple::SIMPLE_ID = 'S';

Gaming::Simple::Simple(const Game & g, const Position & p, double energy) : Agent(g,p,energy)
{
}

Gaming::Simple::~Simple()
{
	//TODO:
}

void Gaming::Simple::print(std::ostream & os) const
{
	os << SIMPLE_ID /*<< std::left << std::setw(4) << std::setfill(' ') */ << __id;
}

Gaming::ActionType Gaming::Simple::takeTurn(const Surroundings & s) const
{
	Position here(1,1);	// position of piece
	std::vector<int> positions;
	for (int i = 0; i < 9; i++) {	// search for resources
		if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
			positions.push_back(i);
	}
	
	if (positions.size() > 0) {			// if there are resources return move to one of them
		Position p = Game::randomPosition(positions);
		return Game::reachSurroundings(here, p);
	}

	else {		// if there are no resources search for empty position
		for (int i = 0; i < 9; i++) {
			if (s.array[i] == EMPTY)
				positions.push_back(i);
		}
		if (positions.size() > 0) {		// go to an empty position
			Position p = Game::randomPosition(positions);
			return Game::reachSurroundings(here, p);
		}
	}
	return STAY;			// if no resources or empty positions, stay put
}
