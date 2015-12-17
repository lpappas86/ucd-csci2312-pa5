#include"AggressiveAgentStrategy.h"

const double Gaming::AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Gaming::Game::STARTING_AGENT_ENERGY * 0.75;

Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
{
	__agentEnergy = agentEnergy;
}

Gaming::AggressiveAgentStrategy::~AggressiveAgentStrategy()
{
	//TODO:
}

Gaming::ActionType Gaming::AggressiveAgentStrategy::operator()(const Surroundings & s) const
{
	Position here(1,1);	// position of piece
	std::vector<int> positions;

	if (__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
		for (int i = 0; i < 9; i++) {	// search for agents to attack
			if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC)
				positions.push_back(i);
		}
	}

	if (positions.size() == 0) {
		for (int i = 0; i < 9; i++) {	// search for advantage
			if (s.array[i] == ADVANTAGE)
				positions.push_back(i);
		}
	}

	if (positions.size() == 0) {
		for (int i = 0; i < 9; i++) {	// search for food
			if (s.array[i] == FOOD)
				positions.push_back(i);
		}
	}

	if (positions.size() == 0) {
		for (int i = 0; i < 9; i++) {	// search for empty position
			if (s.array[i] == EMPTY)
				positions.push_back(i);
		}
	}

	if (positions.size() > 0) {			// if there are resources return move to one of them
		Position p = Game::randomPosition(positions);
		return Game::reachSurroundings(here, p);
	}
	return STAY;			// if no agents, resources, or empty positions, stay put
}
