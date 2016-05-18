#include "maze.h"
#include "iostream"
#include "fstream"
using namespace std;

int main()
{
	ifstream inputFile("input.txt");
	ofstream out;
	out.open("output.txt");

	int mazeSize;
	inputFile >> mazeSize;
	inputFile >> mazeSize;
	Maze mazeJimInput(mazeSize, inputFile);

	inputFile >> mazeSize;
	inputFile >> mazeSize;
	Maze mazeSmallInput(mazeSize, inputFile);

	mazeJimInput.BFS(out);
	mazeSmallInput.BFS(out);

	return 0;
}
