#pragma once
#include <iostream>
#include <vector>
#include <queue>


class State 
{
private:
	void swap(int, int, int, int);

	int** currentGrid;
	int getBoard(int **);

public:
	State();
	State addState(int **, int, int, int);

	int ** nextMoves(int);
	int** board;
	int cost;
	int parent;
	int depth;
	int manhattenDistance(int **) const;


	void printBoard() const;
	void operator=(const State S);
	bool operator==(const State S)const;
};

