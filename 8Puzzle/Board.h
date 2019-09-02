#pragma once
#include "State.h"
#include "compare.h"

class Board
{
private:
	State * currState;
	State * Goal;

	std::priority_queue< State *, std::vector<State *>, compare > gameState;
	std::vector <State *> visited;

	int **goalArr[3][3];
	int ** initGoalArr();

	int goalCheck(State *);
	void findMoves(State * current, int depth);

public:
	Board();
	~Board();

	int aStarMeth();
};

