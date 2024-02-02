#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <utility>
#include <queue>

//-----------------------------------------------------
// Maze Class									
//-----------------------------------------------------
class Maze final
{
public:
	Maze();					// Constructor
	~Maze();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Maze(const Maze& other)					{}
	Maze(Maze&& other) noexcept				{}
	Maze& operator=(const Maze& other)		{}
	Maze& operator=(Maze&& other)	noexcept	{}

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	void GenerateMaze();

	int ConvertToIndex(int column, int row);
	int ConvertToIndex(std::pair<int, int> coord) { return ConvertToIndex(coord.first, coord.second); };

	void AddSurroundingCellsToQueue(int column, int row);
	void AddSurroundingCellsToQueue(std::pair<int, int> coord) { AddSurroundingCellsToQueue(coord.first, coord.second); };

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	const int m_Columns{ 10 };
	const int m_Rows{ 20 };
	float* m_Grid{};
	std::queue<std::pair<int,int>> m_CellsToCheck{};

	std::pair<int,int> m_StartLoc{};
};

 
