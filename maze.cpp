#include "maze.h"
#include "iostream"
using namespace std;

Maze::Maze(int dim, ifstream &input)
{
	this->dimSize = dim;
	this->graph.resize(dim*dim);
	for (int i = 0; i < dim*dim; i++)
	{
		input >> *this;
	}
	for (int i = dim*dim; i <dim*dim; i++)
	{
		this->square.push_back(square.at(i - dim*dim));
	}
	this->adjList();
}

Maze::~Maze()
{
	square.clear();
	graph.clear();
	prev.clear();
	pos.clear();
	condition.clear();
}

istream &operator>>(istream &input, Maze &maze)
{
	int temp;
	input >> temp;
	maze.square.push_back(temp);
	return input;
}

void Maze::adjList()
{
	//iterates up to the size of the maze
	for (int i = 0; i < this->dimSize * this->dimSize; i++)
	{
		int trampoline = this->square.at(i);
		int loc = i % this->dimSize;

		if (square.at(i) > 0)
		{
			//right traversal
			if (loc + trampoline <= this->dimSize - 1)
			{
				//right move to the adjacency list
				this->graph.at(i).push_back(trampoline + i);
			}

			//down traversal
			if ((trampoline * this->dimSize + i) <= (this->dimSize * this->dimSize - 1))
			{
				//down move to the adjacency list
				this->graph.at(i).push_back(trampoline * this->dimSize + i);
			}

			//ledt traversal
			if (loc - trampoline >= 0)
			{
				//left move to the adjacency list
				this->graph.at(i).push_back(i - trampoline);
			}

			//up traversal
			if ((i - trampoline * this->dimSize) >= 0)
			{
				//up move to the adjacency list
				this->graph.at(i).push_back(i - trampoline * this->dimSize);
			}
		}
	}
}

void Maze::BFS(ofstream &out)
{
	this->condition.resize(this->dimSize * this->dimSize);
	this->prev.resize(this->dimSize * this->dimSize);
	this->pos.resize(this->dimSize * this->dimSize);

	//mark all vertices as undiscovered
	for (int i = 0; i < this->dimSize * this->dimSize; i++)
	{
		this->condition.at(i) = Maze::UNDISCOVERED;
		this->prev.at(i) = -1;
		this->pos.at(i) = -1;
	}

	//mark the first vertex as discovered
	this->prev.at(0) = -1;
	this->pos.at(0) = 0;
	this->bfsQueue.push(0);
	this->condition.at(0) = Maze::DISCOVERED;

	//BFS while the queue is not empty
	while (this->bfsQueue.size() != 0)
	{
		int element = this->bfsQueue.front();
		this->bfsQueue.pop();

		for (list<int>::iterator iter = this->graph.at(element).begin(); iter != this->graph.at(element).end(); iter++)
		{
			if (this->condition.at(*iter) == Maze::UNDISCOVERED)
			{
				this->condition.at(*iter) = Maze::DISCOVERED;
				this->pos.at(*iter) = this->pos.at(element) + 1;
				this->prev.at(*iter) = element;
				this->bfsQueue.push(*iter);
			}
		}
		this->condition.at(element) = Maze::EXPLORED;
	}
	this->getPath(out);
}

void Maze::getPath(ofstream &out)
{
	vector <int> shortestPath;
	shortestPath.push_back(this->dimSize * this->dimSize - 1);
	//push back to shortestPath vector
	while (shortestPath.at(shortestPath.size() - 1) != 0)
	{
		shortestPath.push_back(this->prev.at(shortestPath.at(shortestPath.size() - 1)));
	}

	//get and prints the directions both on terminal and in output.txt
	while (shortestPath.size() != 1)
	{
		if (shortestPath.at(shortestPath.size() - 1) / dimSize == shortestPath.at(shortestPath.size() - 2) / dimSize)
		{
			if (shortestPath.at(shortestPath.size() - 1) < shortestPath.at(shortestPath.size() - 2))
			{
				out << "E ";
				cout << "E ";
			}
			else
			{
				out << "W ";
				cout << "W ";
			}
		}
		else if (shortestPath.at(shortestPath.size() - 1) % dimSize == shortestPath.at(shortestPath.size() - 2) % dimSize)
		{
			if (shortestPath.at(shortestPath.size() - 1) < shortestPath.at(shortestPath.size() - 2))
			{
				out << "S ";
				cout << "S ";
			}
			else
			{
				out << "N ";
				cout << "N ";
			}
		}
		else
		{}
		shortestPath.pop_back();
	}
	out << endl << endl;
	cout << endl << endl;
}
