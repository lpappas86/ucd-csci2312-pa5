#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include"AggressiveAgentStrategy.h"
#include"Food.h"
#include"Advantage.h"
#include"Exceptions.h"
#include<set>


const unsigned int Gaming::Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Gaming::Game::NUM_INIT_RESOURCE_FACTOR = 2;
const unsigned Gaming::Game::MIN_WIDTH = 3;
const unsigned Gaming::Game::MIN_HEIGHT = 3;
const double Gaming::Game::STARTING_AGENT_ENERGY = 20;
const double Gaming::Game::STARTING_RESOURCE_CAPACITY = 10;

Gaming::PositionRandomizer Gaming::Game::__posRandomizer;


Gaming::Game::Game()
{
	__round = 0;
	__width = MIN_WIDTH;
	__height = MIN_HEIGHT;


	for (int i = 0; i < __width * __height; i++)
		__grid.push_back(nullptr);


}

Gaming::Game::Game(unsigned width, unsigned height, bool manual)
{
	if (width < MIN_WIDTH || height < MIN_HEIGHT)
		throw Gaming::InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,__width,__height);
	__round = 0;
	__width = width;
	__height = height;
	__status = NOT_STARTED;

	//set up vector
	for (int i = 0; i < __width * __height; i++)
		__grid.push_back(nullptr);

	if (manual == false) {
		populate();
	}
}

Gaming::Game::Game(const Game & another)
{
	__numInitAgents = another.__numInitAgents;
	__numInitResources = another.__numInitResources;

	__width = another.__width;
	__height = another.__height;
	__grid = another.__grid;

	__round = another.__round;

	__status = another.__status;

	__verbose = another.__verbose;
}

Gaming::Game::~Game()
{
	for (int i = 0; i < __width * __height; i++)
		if (__grid[i] != nullptr)
			delete __grid[i];
}

void Gaming::Game::populate()
{
	__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
	__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
	
	
	// get random numbers of agent classes
	std::default_random_engine g;
	std::uniform_int_distribution<int> s(0, __numInitAgents);
	int smpl = s(g);	// number of simple agents
	std::uniform_int_distribution<int> s1(0, __numInitAgents - smpl);
	int aggr = s1(g);	//	number of aggressive agents
	int dflt = __numInitAgents - aggr - smpl;	//	number of default agents

									// get random number of food and advantage
	std::uniform_int_distribution<int> s2(0, __numInitResources);
	int fd = s(g);	// number of food pieces
	int adv = __numInitResources - fd;		// number of advantage pieces


	std::default_random_engine gen;									// for random position
	std::uniform_int_distribution<int> d(0, (__width * __height) - 1);

	// populate Simple agents
	while (smpl > 0) {
		int i = d(gen); // random index in the grid vector
		if (__grid[i] == nullptr) { // is position empty
			Position pos(i / __width, i % __width);
			addSimple(pos);								
		}
		else
			continue;
		smpl--;
	}

	// Populate default strategic agents
	while (dflt > 0) {
		int i = d(gen); // random index in the grid vector
		if (__grid[i] == nullptr) { // is position empty
			Position pos(i / __width, i % __width);
			addStrategic(pos);
		}
		else
			continue;
		dflt--;
	}

	// Populate default strategic agents
	while (aggr > 0) {
		int i = d(gen); // random index in the grid vector
		if (__grid[i] == nullptr) { // is position empty
			Position pos(i / __width, i % __width);
			addStrategic(pos, new Gaming::AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
		}
		else
			continue;
		aggr--;
	}

	// populate Food
	while (fd > 0) {
		int i = d(gen); // random index in the grid vector
		if (__grid[i] == nullptr) { // is position empty
			Position pos(i / __width, i % __width);
			addFood(pos);
		}
		else
			continue;
		fd--;
	}

	// populate Food
	while (adv > 0) {
		int i = d(gen); // random index in the grid vector
		if (__grid[i] == nullptr) { // is position empty
			Position pos(i / __width, i % __width);
			addAdvantage(pos);
		}
		else
			continue;
		adv--;
	}
}

unsigned int Gaming::Game::getNumPieces() const
{
	int count = 0;
	for (int i = 0; i < __width * __height; i++) {
		if (__grid[i] != nullptr)
			count++;
	}
	return count;
}

unsigned int Gaming::Game::getNumAgents() const
{
	int count = 0;
	for (int i = 0; i < __width * __height; i++) {
		Piece *p = dynamic_cast<Agent*>(__grid[i]);
		if (p)
			count++;
	}
	return count;
}

unsigned int Gaming::Game::getNumSimple() const
{
	int count = 0;
	for (int i = 0; i < __width * __height; i++) {
		Piece *p = dynamic_cast<Simple*>(__grid[i]);
		if (p)
			count++;
	}
	return count;
}

unsigned int Gaming::Game::getNumStrategic() const
{
	int count = 0;
	for (int i = 0; i < __width * __height; i++) {
		Piece *p = dynamic_cast<Strategic*>(__grid[i]);
		if (p)
			count++;
	}
	return count;
}

unsigned int Gaming::Game::getNumResources()
{
	int count = 0;
	for (int i = 0; i < __width * __height; i++) {
		Piece *p = dynamic_cast<Resource*>(__grid[i]);
		if (p)
			count++;
	}
	return count;
}

Gaming::PieceType Gaming::Game::getPieceType(Piece *piece) const
{
	Agent *a1 = dynamic_cast<Simple*>(piece);
	if (a1)
		return SIMPLE;
	Agent *a2 = dynamic_cast<Strategic*>(piece);
	if (a2)
		return STRATEGIC;
	Resource *r1 = dynamic_cast<Food*>(piece);
	if (r1)
		return FOOD;
	Resource *r2 = dynamic_cast<Advantage*>(piece);
	if (r2)
		return ADVANTAGE;
	if (piece == nullptr)
		return EMPTY;
}

bool Gaming::Game::addSimple(const Position & position)
{
	
	if (position.y >= __width || position.x >= __height)
		throw Gaming::OutOfBoundsEx(__width, __height, position.x, position.y);
	
	if (__grid[pos2index(position)] != nullptr)		// check if position is available
		return false;

	__grid[pos2index(position)] = new Simple(*this, position, Gaming::Game::STARTING_AGENT_ENERGY);
	return true;
}

bool Gaming::Game::addSimple(unsigned x, unsigned y)
{
	Position pos(x, y);

	return addSimple(pos);
}

bool Gaming::Game::addStrategic(const Position & position, Strategy * s)
{
	if (position.y >= __width || position.x >= __height)
		throw Gaming::OutOfBoundsEx(__width, __height, position.x, position.y);
	if (__grid[pos2index(position)] != nullptr)		// check if position is available
		return false;

	__grid[pos2index(position)] = new Strategic(*this, position, Gaming::Game::STARTING_AGENT_ENERGY,s);
	return true;
}

bool Gaming::Game::addStrategic(unsigned x, unsigned y, Strategy * s)
{
	Position pos(x, y);
	return addStrategic(pos, s);
}

bool Gaming::Game::addFood(const Position & position)
{
	if (position.y >= __width || position.x >= __height)
		throw Gaming::OutOfBoundsEx(__width, __height, position.x, position.y);
	if (__grid[pos2index(position)] != nullptr)		// check if position is available
		return false;
	
	__grid[pos2index(position)] = new Food(*this,position,Gaming::Game::STARTING_RESOURCE_CAPACITY);
	return true;
}

bool Gaming::Game::addFood(unsigned x, unsigned y)
{
	Position pos(x, y);
	return addFood(pos);
}

bool Gaming::Game::addAdvantage(const Position & position)
{
	if (position.y >= __width || position.x >= __height)
		throw Gaming::OutOfBoundsEx(__width, __height, position.x, position.y);
	if (__grid[pos2index(position)] != nullptr)		// check if position is available
		return false;
	
	__grid[pos2index(position)] = new Advantage(*this, position, Gaming::Game::STARTING_RESOURCE_CAPACITY);
	return true;
}

bool Gaming::Game::addAdvantage(unsigned x, unsigned y)
{
	Position pos(x, y);
	return addAdvantage(pos);
}

const Gaming::Surroundings Gaming::Game::getSurroundings(const Position & pos) const
{	
	int cx = pos.x;
	int cy = pos.y;
	Surroundings s;
	int count = 0;
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if ((cx + x) < 0 || (cx + x) >= __height || (cy + y) < 0 || (cy + y) >= __width) {
				s.array[count++] = INACCESSIBLE;
				continue;
			}
			if (x == 0 && y == 0) {
				s.array[count++] = SELF;
				continue;
			}
			Position temp(cx + x, cy + y);
			s.array[count++] = getPieceType(__grid[pos2index(temp)]);
		}
	}
	return s;
}

int Gaming::Game::pos2index(const Position & position) const
{
	return ( (position.x * __width) + position.y % __height);			//CHANGED: position.x % __width) + position.y * __width
}

const Gaming::ActionType Gaming::Game::reachSurroundings(const Position & from, const Position & to)
{
	int fx = from.x, fy = from.y;
	int tx = to.x, ty = to.y;

	if (tx == fx - 1 && ty == fy - 1) return NW;
	if (tx == fx - 1 && ty == fy) return N;
	if (tx == fx - 1 && ty == fy + 1) return NE;
	if (tx == fx && ty == fy - 1) return W;
	if (tx == fx && ty == fy + 1) return E;
	if (tx == fx + 1 && ty == fy - 1) return SW;
	if (tx == fx + 1 && ty == fy) return S;
	if (tx == fx + 1 && ty == fy + 1) return SE;

	return STAY;
}

bool Gaming::Game::isLegal(const ActionType & ac, const Position & pos) const
{
	int x = pos.x, y = pos.y;
	if (ac == NW) { x--; y--; }
	if (ac == N) { x--; }
	if (ac == NE) { x--; y++; }
	if (ac == W) { y--; }
	if (ac == E) { y++; }
	if (ac == SW) { x++; y--; }
	if (ac == S) { x++; }
	if (ac == SE) { x++; y++; }

	if (x < 0 || x >= __height || y < 0 || y >= __width)
		return false;
	
	return true;
}

const Gaming::Position Gaming::Game::move(const Position & pos, const ActionType & ac) const
{	
	Piece *piece = __grid[pos2index(pos)];		// pointer to the piece at position pos

	if (piece == nullptr)	// if there is no piece in position, do nothing
		return pos;

	if (!isLegal(ac, pos))	// if move is not legal, do nothing
		return pos;

	Piece *p = dynamic_cast<Resource*>(piece);		// if piece is a resource, do nothing
	if (p)
		return pos;

	int x = pos.x, y = pos.y;
	if (ac == NW) { x--; y--; }
	if (ac == N) { x--; }
	if (ac == NE) { x--; y++; }
	if (ac == W) { y--; }
	if (ac == E) { y++; }
	if (ac == SW) { x++; y--; }
	if (ac == S) { x++; }
	if (ac == SE) { x++; y++; }

	Position newPos(x, y);
	
	return newPos;
}

void Gaming::Game::round()
{
	__round++;
	
	for (int i = 0; i < __width * __height; i++) {
		if (__verbose)
			__status = OVER;
		Piece *k = __grid[i];
		if (k == nullptr)
			continue;
		if (k->getTurned()) break;
		Surroundings sur = getSurroundings(k->getPosition());
		ActionType ac = k->takeTurn(sur);
		Position p = move(k->getPosition(), ac);
		if (__grid[pos2index(p)] != nullptr)
			if(ac != STAY)
				(*k) * *__grid[pos2index(p)];
		if (k->isViable()) {
			__grid[pos2index(p)] = k;
			__grid[pos2index(k->getPosition())] = nullptr;
			k->setPosition(p);
		}
		k->setTurned(true);
	}

	for (int i = 0; i < __width * __height; i++) {

		Piece *k = __grid[i];
		if (k != nullptr) {
			k->age();
			
			if (!k->isViable()) {
				__grid[pos2index(k->getPosition())] == nullptr;
				//delete k;
			}
			k->setTurned(false);
		}



	}
	

	std::cout << *this;

}

void Gaming::Game::play(bool verbose)
{
	std::cout << *this;
	while (!verbose) {		//until game is over
		for (int i = 0; i < __height*__width; i++) {
			Piece *p = dynamic_cast<Resource*>(__grid[i]);
			if (p)
				break;
			if (i == 8) {
				verbose = true;
				__status = OVER;
			}
			if (verbose == false)
				__status = PLAYING;
		}
		round();
	}
}

std::ostream & Gaming::operator<<(std::ostream & os, const Game & game)
{
	//TODO: Do this right
	os << "Round " << game.__round << ":" << std::endl;
	int count = 0;		//For vector indexing
	for (int i = 0; i < game.__height; i++) {
		for (int j = 0; j < game.__width; j++) {
			os << "[" << *(game.__grid[count++]) << "]";
		}
		os << std::endl;
	}
	os << "Status: ";
	/*if (game.__status == Gaming::Game::NOT_STARTED)
		std::cout << "Not started yet" << std::endl;
	else if (game.__status == Gaming::Game::PLAYING)
		os << "Playing" << std::endl;
	else
		os << "Over" << std::endl;*/
	
	return os;
}


