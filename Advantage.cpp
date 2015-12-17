#include "Advantage.h"

const char Gaming::Advantage::ADVANTAGE_ID = 'D';
const double Gaming::Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Gaming::Advantage::Advantage(const Game & g, const Position & p, double capacity) : Resource(g,p,capacity)
{
}

Gaming::Advantage::~Advantage()
{
	//TODO
}

void Gaming::Advantage::print(std::ostream & os) const
{
	os << ADVANTAGE_ID /*<< std::left << std::setw(4) << std::setfill(' ') */<< __id;
}

double Gaming::Advantage::getCapacity() const
{
	return __capacity * ADVANTAGE_MULT_FACTOR;
}

double Gaming::Advantage::consume()
{
	//TODO:
	return 0.0;
}
