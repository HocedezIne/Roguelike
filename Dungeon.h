#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <utility>
#include <vector>
#include <string>

//-----------------------------------------------------
// BSPTree struct
//-----------------------------------------------------
struct Room {
	int x{};
	int y{};
	int width{};
	int height{};
};

struct Node {
	bool hasChild{ false };
	Node* left{};
	Node* right{};
	std::pair<int, int> dimension{};
	std::pair<int, int> topLeft{};
	Room room{};
};

//-----------------------------------------------------
// Exception Class
//-----------------------------------------------------
class IncorrectInput final
{
private:
	std::wstring m_Msg{};
public:
	IncorrectInput(const std::wstring& msg) : m_Msg(msg) {};
	std::wstring GetExceptionMessage() const { return m_Msg; };
};

//-----------------------------------------------------
// Dungeon Class									
//-----------------------------------------------------
class Dungeon final
{
public:
	Dungeon(const int _totalWidth, const int _totalHeight, const int _minRoomSize, const int _maxRoomSize, const int _minCorridorSize);	// Constructor
	~Dungeon();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Dungeon(const Dungeon& other) =delete;
	Dungeon(Dungeon&& other) noexcept = delete;
	Dungeon& operator=(const Dungeon& other) = delete;
	Dungeon& operator=(Dungeon&& other)	noexcept;
	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	Node* GetBSP() const { return m_BSPTree; };
	std::vector<Room*> GetRooms() const { return m_Rooms; };
	std::vector<Room> GetCorridors() const { return m_Corridors; };

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	Node* CreateBSPTree(const int _width, const int _height, const std::pair<int, int> _topLeft = {});

	void CreateRooms(Node* node);
	//void CreateCorridors(Node* node);
	std::vector<Room*> CreateCorridors(Node* node);

	Room ConnectRooms(const Room const * r1,const Room const * r2);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Node* m_BSPTree{};
	std::vector<Room*> m_Rooms{};
	std::vector<Room> m_Corridors{};

	const int m_TotalWidth;
	const int m_TotalHeight;
	const int m_MinRoomSize;
	const int m_MaxRoomSize;
	const int m_MinCorridorSize;
};

 
