#include "Board.h"


Board::Board()
{
	currState = new State();
	int temp;
	int** goalArr = initGoalArr();

	std::cout << "Enter numbers 0 to 8 in any order: \n";

	int ** grid = new int *[3];

	for (int i = 0; i < 3; i++)
	{
		grid[i] = new int[3];

		for (int j = 0; j < 3; j++)
		{
			std::cout << (9 - (i * 3 + j)) << " more numbers: ";
			std::cin >> temp;

			if (temp > 8 || temp < 0)
				j--;
			else
			{
				std::cout << std::endl;
				grid[i][j] = temp;
			}
		}
	}

	std::cout << "Initial State: \n";
	*currState = currState->addState(grid, 0, 0, 0);
	currState->printBoard();

	Goal = new State();
	std::cout << "Goal State: \n";
	*Goal = Goal->addState(goalArr, -1, -1, -1);
	Goal->printBoard();
}

Board::~Board()
{
	delete Goal;
	delete currState;
}

int ** Board::initGoalArr()
{
	int ** retArr = new int*[3];

	for (int i = 0; i < 3; i++)
		retArr[i] = new int[3];

	retArr[0][0] = 1;
	retArr[0][1] = 2;
	retArr[0][2] = 3;
	retArr[1][0] = 8;
	retArr[1][1] = 0;
	retArr[1][2] = 4;
	retArr[2][0] = 7;
	retArr[2][1] = 6;
	retArr[2][2] = 5;

	return retArr;
}

int Board::goalCheck(State *current)
{
	int temp = 0, steps = 0;

	if (*current == *Goal)																			//See if current move is equal to goal board
	{
		std::cout << "Goal State Found!\n\n";
		temp = current->depth;
		std::cout << "Moves : " << current->cost << std::endl;							
		current->printBoard();																		//Print final board

		while (1)
		{
			if ((*current == *currState))
				break;
			steps++;
			visited[current->parent];
			current = visited[current->parent];
		}
		return temp - 1;
	}

}

void Board::findMoves(State *current, int depth)
{
	State *child = new State;
	bool contains = false;

	for (int i = 0; i < 4; i++)																		//For each move
	{
		child = new State;
		child->board = current->nextMoves(i);
		child->cost = Goal->manhattenDistance(current->nextMoves(i)) + current->depth;				// (A* Method) - f(n) = h(n) + g(n)
		child->parent = depth + 1;
		child->depth = current->depth + 1;

		for (std::vector<State *>::iterator it = visited.begin(); it != visited.end(); ++it)		//Iterates through 'visited' vector
		{
			if (*(*it) == *child)
			{
				contains = true;
				if (child->cost >= (*it)->cost)														//overwrites node with better path 
					break;
				else
				{
					(*it)->cost = child->cost;
					(*it)->parent = child->parent;
				}
			}
		}
		if (contains == false)
			gameState.push(child);
		contains = false;
	}
}

int Board::aStarMeth()
{
	std::cout << "Running A*...\n\n";
	int depth = -1;

	if (*currState == *Goal)										//Check if initial input is equal 
	{																//to the goal state
		std::cout << "Initial State is equal to goal state!\n\n";
		currState->printBoard();
		return 0;
	}

	State * current = new State, *child = new State;
	gameState.push(currState);

	while (!gameState.empty())
	{
		current = gameState.top();
		visited.push_back(current);
		gameState.pop();

		goalCheck(current);
		findMoves(current, depth);
		depth++;
	}

	return depth;
}

