#include "DefaultAgentStrategy.h"
#include "Game.h"

Gaming::DefaultAgentStrategy::DefaultAgentStrategy()
{
}

Gaming::DefaultAgentStrategy::~DefaultAgentStrategy()
{
	//TODO:
}

Gaming::ActionType Gaming::DefaultAgentStrategy::operator()(const Surroundings & s) const
{
	Position here(1, 1);	// position of piece
	std::vector<int> positions;
	for (int i = 0; i < 9; i++) {	// search for advantage
		if ( s.array[i] == ADVANTAGE)
			positions.push_back(i);
	}

	if (positions.size() == 0) {		// search for food
		for (int i = 0; i < 9; i++) {	
			if (s.array[i] == FOOD)
				positions.push_back(i);
		}
	}

	if (positions.size() == 0) {		// search for empty position
		for (int i = 0; i < 9; i++) {
			if (s.array[i] == EMPTY)
				positions.push_back(i);
		}
	}

	if (positions.size() == 0) {		// search for simple agent
		for (int i = 0; i < 9; i++) {
			if (s.array[i] == SIMPLE)
				positions.push_back(i);
		}
	}

	if (positions.size() > 0) {			// go to whatever you found
		Position p = Game::randomPosition(positions);
		return Game::reachSurroundings(here, p);
	}

	return STAY;		// if all else fails, stay put
}
