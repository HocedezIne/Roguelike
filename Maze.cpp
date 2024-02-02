//---------------------------
// Includes
//---------------------------
#include "Maze.h"
#include <random>

//---------------------------
// Constructor & Destructor
//---------------------------
Maze::Maze()
{
	/// <summary>
	/// maze layout lengend
	/// 0 - wall
	/// 1 - path
	/// </summary>

	m_Grid = new float[m_Columns * m_Rows] {}; // fill with 0 to indicate wall
	//std::fill_n(m_Grid, m_Columns * m_Rows, 0);

	GenerateMaze();
}

Maze::~Maze()
{
	delete[] m_Grid;
}

//---------------------------
// Member functions
//---------------------------

void Maze::GenerateMaze()
{
	// pick a random location in maze to use as the start of the path
	m_StartLoc = std::make_pair<int, int>(rand() % (m_Columns-2)+1, rand() % (m_Rows-2)+1);
	m_Grid[ConvertToIndex(m_StartLoc)] = 1;

	// add surrounding cells to check if those can be set to path
	AddSurroundingCellsToQueue(m_StartLoc);

	while (!m_CellsToCheck.empty())
	{
		auto cell = m_CellsToCheck.front();
		m_CellsToCheck.pop();

		/// <summary>
		/// PSEUDO CODE TRYING TO FIGURE OUT THE OLD PYTHON LOOP
		/// 
		/// </summary>
	}
}

int Maze::ConvertToIndex(int column, int row)
{
	return column + (column * row);
}

void Maze::AddSurroundingCellsToQueue(int column, int row)
{
	std::pair<int, int> left{ column - 1,row };
	std::pair<int, int> top{ column, row + 1 };
	std::pair<int, int> right{ column + 1, row };
	std::pair<int, int> bottom{ column, row - 1 };

	m_CellsToCheck.push(left);
	m_CellsToCheck.push(top);
	m_CellsToCheck.push(right);
	m_CellsToCheck.push(bottom);
}