#include "Agent.h"
#include "Resource.h"
#include"Food.h"
#include"Advantage.h"

const double Gaming::Agent::AGENT_FATIGUE_RATE = 0.3;

Gaming::Agent::Agent(const Game & g, const Position & p, double energy) : Piece(g,p)
{
	__energy = energy;
}

Gaming::Agent::~Agent()
{
	//TODO:
}

void Gaming::Agent::age()
{
	__energy -= AGENT_FATIGUE_RATE;
	if (__energy <= 0)
		finish();
}

Gaming::Piece & Gaming::Agent::operator*(Piece & other)
{
	Piece *p = dynamic_cast<Agent*>(&other);
	if(p)
		return interact(dynamic_cast<Agent*>(&other));

	Piece *p1 = dynamic_cast<Resource*>(&other);
	if(p1)
		return interact(dynamic_cast<Resource*>(&other));
}

Gaming::Piece & Gaming::Agent::interact(Agent *agent)
{
	if (__energy == agent->getEnergy()) {
		agent->finish();
		finish();
	}
	else if (__energy > agent->getEnergy()) {
		__energy -= agent->getEnergy();
		agent->finish();
	}
	else {
		agent->__energy -= __energy;
		finish();
	}
	return *this;
}

Gaming::Piece & Gaming::Agent::interact(Resource *resource)
{
	Resource *r = dynamic_cast<Food*>(resource);
	if (r) {
		__energy += r->getCapacity();
		resource->interact(this);
	}
	Resource *r1 = dynamic_cast<Advantage*>(resource);
	if (r1) {
		__energy += r1->getCapacity();
		resource->interact(this);
	}
	return *this;
}
