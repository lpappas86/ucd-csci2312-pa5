#include<iostream>
#include "Simple.h"
#include "Game.h"

using namespace std;
using namespace Gaming;

int main() {
	//Game g;
	//Position p(1,1);
	//Simple s(g, p, 10);
	//Simple s1(g, p, 10);
	//Simple s2(g, p, 10);
	//cout << s << endl;
	//cout << s1 << endl;
	//cout << s2 << endl;

	//std::vector<Piece *> __grid;
	//for (int i = 0; i < 9; i++)
	//	__grid.push_back(nullptr);
	//__grid[2] = new Simple(g, p, 10);

	
		//std::default_random_engine gen;
		//std::uniform_int_distribution<int> f(0, 20);
		//int num1 = f(gen);
		//std::uniform_int_distribution<int> f1(0, 20 - num1);
		//int num2 = f1(gen);
		//int num3 = 20 - num2 - num1;

		//cout << num1 << endl << num2 << endl << num3 << endl << endl;


	/*Game g(9, 7, false);
	cout << g << endl;
	*/
	/*int x = 12;
	cout << x / 5 << endl << x % 5 << endl;*/

	Game g;
	g.play();

	return 0;
}