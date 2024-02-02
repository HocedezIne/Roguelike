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
	int GetColumns() { return m_Columns; };
	int GetRows() { return m_Rows; };
	auto GetGrid() { return m_Grid; };
	int GetGridValue(int column, int row) { return m_Grid[ConvertToIndex(column, row)]; };

	void GenerateMaze();


private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	int ConvertToIndex(int column, int row);
	int ConvertToIndex(std::pair<int, int> coord) { return ConvertToIndex(coord.first, coord.second); };

	void AddSurroundingCellsToQueue(int column, int row);
	void AddSurroundingCellsToQueue(std::pair<int, int> coord) { AddSurroundingCellsToQueue(coord.first, coord.second); };

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	const int m_Columns{ 20 };
	const int m_Rows{ 20 };
	float* m_Grid{};
	std::queue<std::pair<int,int>> m_CellsToCheck{};

	std::pair<int,int> m_StartLoc{};
};

 
