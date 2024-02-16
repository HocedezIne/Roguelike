//---------------------------
// Includes
//---------------------------
#include "Dungeon.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Dungeon::Dungeon(const int _totalWidth, const int _totalHeight, const int _minRoomSize, const int _maxRoomSize):
	m_TotalWidth(_totalWidth), m_TotalHeight(_totalHeight), m_MinRoomSize(_minRoomSize), m_MaxRoomSize(_maxRoomSize)
{
	if (m_MinRoomSize > m_MaxRoomSize) throw IncorrectInput(L"Minimum room size must be less than maximum room size.");
	//if (m_MaxRoomSize > m_TotalWidth) throw IncorrectInput(L"Maximum room size must be less than total width.");
	//if (m_MaxRoomSize > m_TotalHeight) throw IncorrectInput(L"Maximum room size must be less than total height.");

	m_BSPTree = CreateBSPTree(m_TotalWidth, m_TotalHeight);
}

Dungeon::~Dungeon()
{
	delete m_BSPTree;
}

Dungeon& Dungeon::operator=(Dungeon&& other) noexcept
{
	if (this != &other)
	{
		const_cast<int&>(m_TotalWidth) = other.m_TotalWidth;
		const_cast<int&>(m_TotalHeight) = other.m_TotalHeight;
		const_cast<int&>(m_MinRoomSize) = other.m_MinRoomSize;
		const_cast<int&>(m_MaxRoomSize) = other.m_MaxRoomSize;

		delete m_BSPTree;
		m_BSPTree = std::exchange(other.m_BSPTree, nullptr);
	}

	return *this;
}

//---------------------------
// Member functions
//---------------------------
Node* Dungeon::CreateBSPTree(const int _width, const int _height, const std::pair<int, int> _topLeft)
{
	if (_width < m_MinRoomSize || _height < m_MinRoomSize) return nullptr;

	if (_width <= m_MaxRoomSize || _height <= m_MaxRoomSize)
	{
		Node* child = new Node{};
		child->topLeft = _topLeft;
		child->dimension = { _width, _height };

		return child;
	}

	Node* node = new Node{};
	node->topLeft = _topLeft;
	node->hasChild = true;

	bool splitVertically = rand() % 2 == 0;
	int splitPosition{};
	if (splitVertically) splitPosition = rand() % _width;
	else splitPosition = rand() % _height;

	if (splitVertically == 0)
	{
		node->dimension.first = splitPosition;
		node->dimension.second = _height;

		node->left = CreateBSPTree(splitPosition, _height, _topLeft);
		node->right = CreateBSPTree(_width - splitPosition, _height, { splitPosition, _topLeft.second });
	}
	else
	{
		node->dimension.first = _width;
		node->dimension.second = splitPosition;

		node->left = CreateBSPTree(_width, splitPosition, _topLeft);
		node->right = CreateBSPTree(_width, _height - splitPosition, { _topLeft.first, splitPosition });
	}

	return node;
}