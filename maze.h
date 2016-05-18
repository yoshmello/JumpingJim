#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <vector>
#include <cmath>
using namespace std;

class Maze {
public:
	Maze(int dim, ifstream &input);
	~Maze();
	friend istream &operator>>(istream &input, Maze &maze);
	void adjList();
	void BFS(ofstream&);
	void getPath(ofstream&);

private:
	enum CONDITION { UNDISCOVERED, DISCOVERED, EXPLORED };
	int dimSize;
	queue <int> bfsQueue;
	vector <list <int> > graph;
	vector <int> square;
	vector <int> prev;
	vector <int> pos;
	vector <int> condition;
};

#endif
