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
	// reseting grid
	std::fill_n(m_Grid, m_Columns * m_Rows, 0);

	// pick a random location in maze to use as the start of the path
	m_StartLoc = std::make_pair<int, int>(rand() % (m_Columns-2)+1, rand() % (m_Rows-2)+1);
	m_Grid[ConvertToIndex(m_StartLoc)] = 1;

	// add surrounding cells to check if those can be set to path
	AddSurroundingCellsToQueue(m_StartLoc);

	while (!m_CellsToCheck.empty())
	{
		auto cell = m_CellsToCheck.front();
		m_CellsToCheck.pop();

		if (cell.first == 0 || cell.first == m_Columns - 1 || cell.second == 0 || cell.second == m_Rows - 1) continue; // early exit if cell is on edge of maze

		// check how many neighbours are cell path
		int neighbours{};
		if (m_Grid[ConvertToIndex(cell.first - 1, cell.second)] == 1) ++neighbours;
		if (m_Grid[ConvertToIndex(cell.first, cell.second + 1)] == 1) ++neighbours;
		if (m_Grid[ConvertToIndex(cell.first + 1, cell.second)] == 1) ++neighbours;
		if (m_Grid[ConvertToIndex(cell.first, cell.second - 1)] == 1) ++neighbours;

		if (neighbours < 2)
		{
			m_Grid[ConvertToIndex(cell)] = 1;
			AddSurroundingCellsToQueue(cell);
		}

		/// <summary>
		/// PSEUDO CODE TRYING TO FIGURE OUT THE OLD PYTHON LOOP
		/// if cell is on edge -> go to next cell
		/// check how many neighbours of cell are path
		/// if neighbours < 2 -> cell becomes path -> add neighbours to list 
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