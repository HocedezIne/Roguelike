//-----------------------------------------------------------------
// Main Game  File
// C++ Header - Roguelike.h - version v7_02			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Maze.h"
#include "Dungeon.h"

//-----------------------------------------------------------------
// Roguelike Class																
//-----------------------------------------------------------------
class Roguelike : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Roguelike();

	virtual ~Roguelike() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Roguelike(const Roguelike& other) = delete;
	Roguelike(Roguelike&& other) noexcept = delete;
	Roguelike& operator=(const Roguelike& other) = delete;
	Roguelike& operator=(Roguelike&& other) noexcept = delete;

	//---------------------------
	// General Methods
	//---------------------------
	void Initialize(HINSTANCE hInstance) override;
	void Start() override;
	void End() override;
	void Paint(RECT rect) override;
	void Tick() override;
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	void MouseMove(int x, int y, WPARAM wParam) override;
	void CheckKeyboard() override;
	void KeyPressed(TCHAR cKey) override;

	void CallAction(Caller* callerPtr) override;

private:
	//---------------------------
	// Helper Methods
	//---------------------------
	void PaintDungeon(Node* node);

	// -------------------------
	// Datamembers
	// -------------------------
	std::wstring m_ErrorMsg{};

	Maze m_Maze{};
	int m_MazeCellSize{ 30 };

	Dungeon* m_Dungeon{};
};
