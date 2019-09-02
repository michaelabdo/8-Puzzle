#include "State.h"


State::State()
{
	board = new int*[3];

	for (int i = 0; i < 3; i++)											
	{			
		board[i] = new int[3];

		for (int j = 0; j < 3; j++)										
		{
			board[i][j] = -1;
		}
	}

	cost = 0;
	parent = 0;
	depth = 0;

}

State State::addState(int **ovBoard, int ovCost, int ovPar, int ovDep)
{
	State s;
	s.board = ovBoard;
	s.cost = ovCost;
	s.parent = ovPar;
	s.depth = ovDep;

	return s;
}

void State::printBoard() const
{
	for (int xaxis = 0; xaxis < 3; xaxis++)
	{
		for (int yaxis = 0; yaxis < 3; yaxis++)
		{
			if (board[xaxis][yaxis] == 0)
				std::cout << "  ";
			else
				std::cout << board[xaxis][yaxis] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int State::manhattenDistance(int **board) const
{
	int tempDist = 0;
	int horz1 = 0, horz2 = 0, vert1 = 0, vert2= 0;

	for (int j = 0; j < 3 * 3; j++) {

		horz1 = j  % 3;
		vert1 = (int)floor(j / 3);

		for (int i = 0; i < 3 * 3; i++) {

			if (this->board[j % 3][j / 3] == board[i % 3][i / 3]) {
				horz2 = i % 3;
				vert2 = i / 3;
				break;
			}
		}
		tempDist += (abs(horz1 - horz2) + abs(vert1 - vert2));

	}
	return tempDist;
}

int State::getBoard(int ** board)
{
	return **board;
}

bool State::operator==(const State S)const
{
	for (int xaxis = 0; xaxis < 3; xaxis++)
	{
		for (int yaxis = 0; yaxis < 3; yaxis++)
		{
			if (this->board[xaxis][yaxis] != S.board[xaxis][yaxis])
			{
				return 0;
			}
		}
	}
	return 1;
}

void State::operator=(const State S)
{
	for (int xaxis = 0; xaxis < 3; xaxis++)
	{
		for (int yaxis = 0; yaxis < 3; yaxis++)
		{
			this->board[xaxis][yaxis] = S.board[xaxis][yaxis];
		}
	}
}

void State::swap(int x, int y, int xPlus, int yPlus)
{
	int temp = this->board[x][y];
	this->board[x][y] = this->board[xPlus][yPlus];
	this->board[xPlus][yPlus] = temp;
}

int ** State::nextMoves(int move)
{
	State curState;

	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			curState.board[i][j] = this->board[i][j];

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (curState.board[x][y] == 0)
			{
				if (y >= 1 && move == 0)							//Left
					curState.swap(x, y, x, y-1 );
				if (y <= 1 && move == 1)							//Right
					curState.swap(x, y, x, y + 1);
				if (x >= 1 && move == 2)							//Up
					curState.swap(x, y, x - 1, y);
				if (x <= 1 && move == 3)							//Down
					curState.swap(x, y, x + 1, y);
			}
		}
	}

	return curState.board;
}
