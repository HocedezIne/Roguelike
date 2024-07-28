//---------------------------
// Includes
//---------------------------
#include "Dungeon.h"
//#include <algorithm>
#include <iostream>

//---------------------------
// Constructor & Destructor
//---------------------------
Dungeon::Dungeon(const int _totalWidth, const int _totalHeight, const int _minRoomSize, const int _maxRoomSize, const int _minCorridorSize):
	m_TotalWidth(_totalWidth), m_TotalHeight(_totalHeight), m_MinRoomSize(_minRoomSize), m_MaxRoomSize(_maxRoomSize), m_MinCorridorSize(_minCorridorSize)
{
	if (m_MinRoomSize > m_MaxRoomSize) throw IncorrectInput(L"Minimum room size must be less than maximum room size.");
	//if (m_MaxRoomSize > m_TotalWidth) throw IncorrectInput(L"Maximum room size must be less than total width.");
	//if (m_MaxRoomSize > m_TotalHeight) throw IncorrectInput(L"Maximum room size must be less than total height.");

	m_BSPTree = CreateBSPTree(m_TotalWidth, m_TotalHeight);
	CreateRooms(m_BSPTree);
	CreateCorridors(m_BSPTree);
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
 	if ((_width <= m_MaxRoomSize || _width < m_MinRoomSize * 2) && (_height <= m_MaxRoomSize || _height<m_MinRoomSize * 2))
	{
		Node* child = new Node{};
		child->topLeft = _topLeft;
		child->dimension = { _width, _height };

		return child;
	}

	Node* node = new Node{};
	node->topLeft = _topLeft;
	node->hasChild = true;

	bool splitVertically{ rand() % 2 == 0 };
	if ((_width <= m_MaxRoomSize || _width < m_MinRoomSize * 2)) splitVertically = true;
	else if (_height <= m_MaxRoomSize || _height < m_MinRoomSize * 2) splitVertically = false;


	if (splitVertically == 0)
	{
		const int splitPosition = std::max(std::rand() % (_width - m_MinRoomSize), m_MinRoomSize);

		node->dimension.first = _width; //splitPosition;
		node->dimension.second = _height;

		node->left = CreateBSPTree(splitPosition, _height, _topLeft);
		node->right = CreateBSPTree(_width - splitPosition, _height, { splitPosition + _topLeft.first, _topLeft.second });
	}
	else
	{
		const int splitPosition = std::max(std::rand() % (_height - m_MinRoomSize), m_MinRoomSize);

		node->dimension.first = _width;
		node->dimension.second = _height;

		node->left = CreateBSPTree(_width, splitPosition, _topLeft);
		node->right = CreateBSPTree(_width, _height - splitPosition, { _topLeft.first, splitPosition + _topLeft.second });
	}

	return node;
}

void Dungeon::CreateRooms(Node* node) 
{
	if (node)
	{
		if (node->hasChild == true) {
			CreateRooms(node->left);
			CreateRooms(node->right);
		}
		else
		{
			int x{}, y{};
			if ((node->dimension.first - m_MinRoomSize) > 0) x = rand() % (node->dimension.first - m_MinRoomSize);
			if ((node->dimension.second - m_MinRoomSize) > 0) y = rand() % (node->dimension.second - m_MinRoomSize);
			node->room = { x + node->topLeft.first, y + node->topLeft.second, std::max(rand() % (node->dimension.first - x), m_MinRoomSize), std::max(rand() % (node->dimension.second - y), m_MinRoomSize) };
			m_Rooms.push_back(&node->room);
		}
	}
}

//void Dungeon::CreateCorridors(Node* node)
std::vector<Room*> Dungeon::CreateCorridors(Node* node)
{
#pragma region LeafVersion
	//// works for all leafs
	//if (node->hasChild && !node->left->hasChild && !node->right->hasChild)
	//{
	//	m_Corridors.push_back(ConnectRooms(node->left->room, node->right->room));
	//}
	//else
	//{
	//	if(node->left) CreateCorridors(node->left);
	//	if(node->right) CreateCorridors(node->right);
	//}
#pragma endregion LeafVersion

#pragma region ParentAttemptOne
	//if (node)
	//{
	//	//if (node->left && node->right) m_Corridors.push_back(ConnectRooms(node->left->room, node->right->room));

	//	//if (node->left->hasChild) CreateCorridors(node->left);
	//	//if (node->right->hasChild) CreateCorridors(node->right);

	//	if (node->left && node->right)
	//	{
	//		if (node->left->room.width == 0 || node->left->room.height == 0 || 
	//			node->right->room.width == 0 || node->right->room.height == 0)
	//		{
	//			// code for connecting level
	//			auto c1 = node->left;
	//			auto c2 = node->right;
	//			Node* c1CNode{};
	//			Node* c2CNode{};

	//			bool overlap = false;
	//			do
	//			{
	//				int option{ rand() % 4 };
	//				switch (option)
	//				{
	//				case 0:
	//					c1CNode = c1->left;
	//					c2CNode = c2->left;
	//					break;
	//				case 1:
	//					c1CNode = c1->left;
	//					c2CNode = c2->right;
	//					break;
	//				case 2:
	//					c1CNode = c1->right;
	//					c2CNode = c2->left;
	//					break;
	//				case 3:
	//					c1CNode = c1->right;
	//					c2CNode = c2->right;
	//					break;
	//				}

	//				// check if chosen nodes have overlapping rooms
	//				if (abs(c1CNode->room.x - c2CNode->room.x) <= c1CNode->room.width ||
	//					abs(c1CNode->room.y - c2CNode->room.y) <= c1CNode->room.height)
	//				{
	//					overlap = true;
	//					m_Corridors.push_back(ConnectRooms(c1CNode->room, c2CNode->room));
	//				}
	//			} while (true);

	//			// recall for children
	//			if (node->left->hasChild) CreateCorridors(node->left);
	//			if (node->right->hasChild) CreateCorridors(node->right);
	//		}
	//		else m_Corridors.push_back(ConnectRooms(node->left->room, node->right->room)); // connecting leaf nodes
	//	}
	//}
#pragma endregion ParentAttemptOne

#pragma region ParentAttemptTwo
	if (node && node->left && node->right) // node is valid and has valid children
	{
		if (node->left->room.width > 0 && node->right->room.width > 0) // both child nodes have rooms
		{
			// connect the 2 rooms and return them
			m_Corridors.push_back(ConnectRooms(&node->left->room, &node->right->room));
			return { &node->left->room, & node->right->room };
		}
		
		else
		{
			std::vector<Room*> leftRooms, rightRooms;

			// if child room invalid -> call function again on grandchildren
			// if child room valid -> store in vector
			if (node->left->room.width > 0) leftRooms.push_back(&node->left->room);
			else leftRooms = CreateCorridors(node->left);

			if (node->right->room.width > 0) rightRooms.push_back(&node->right->room);
			else rightRooms = CreateCorridors(node->right);

			// repeating if no overlap was found
			Room corridor{};
			do
			{
				// optionally choose room index
				int leftIdx = rand() % leftRooms.size();
				int rightIdx = rand() % rightRooms.size();

				// connect rooms call on chosen rooms
				corridor = ConnectRooms(leftRooms[leftIdx], rightRooms[rightIdx]);

			} while (corridor.width <= 0);
			m_Corridors.push_back(corridor); // add corridor to collection
			
			// return both room vectors as 1 vec
			leftRooms.insert(leftRooms.end(), rightRooms.begin(), rightRooms.end());
			return leftRooms;
		}
	}

#pragma endregion ParentAttemptTwo

	return{};
}

Room Dungeon::ConnectRooms(const Room const* r1, const Room const* r2)
{
	int overlapSize{};
	std::pair<int, int> topLeft{};
	int maxCorrSize{};
	int width{};
	int height{};

	if (abs(r1->x - r2->x) <= r1->width)
	{
		std::cout << "x overlap\n";

		overlapSize = r1->x - r2->x;

		topLeft.first = std::max(r1->x - overlapSize, r1->x);
		topLeft.second = r1->y + r1->height;

		maxCorrSize = std::min(r1->x + r1->width - topLeft.first, r2->x + r2->width - topLeft.first);
		height = abs(r2->y - r1->y - r1->height);

		if (maxCorrSize > m_MinCorridorSize) width = rand() % (maxCorrSize - m_MinCorridorSize + 1) + m_MinCorridorSize;
		else width = maxCorrSize;

		int startOffset = rand() % (maxCorrSize - width + 1);
		topLeft.first += startOffset;
	}
	if (abs(r1->y - r2->y) <= r1->height)
	{
		std::cout << "y overlap\n";

		overlapSize = r1->y - r2->y;

		topLeft.first = r1->x + r1->width;
		topLeft.second = std::max(r1->y - overlapSize, r1->y);

		maxCorrSize = std::min(r1->y + r1->height - topLeft.second, r2->y + r2->height - topLeft.second);
		width = abs(r2->x - r1->x - r1->width);

		if (maxCorrSize > m_MinCorridorSize) height = rand() % (maxCorrSize - m_MinCorridorSize + 1) + m_MinCorridorSize;
		else height = maxCorrSize;

		int startOffset = rand() % (maxCorrSize - height + 1);
		topLeft.second += startOffset;
	}

	return {topLeft.first, topLeft.second, width, height};
}