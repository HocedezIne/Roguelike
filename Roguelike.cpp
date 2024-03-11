//-----------------------------------------------------------------
// Main Game File
// C++ Source - Roguelike.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Roguelike.h"						

//-----------------------------------------------------------------
// Roguelike methods																				
//-----------------------------------------------------------------

Roguelike::Roguelike() 																	
{
	// nothing to create
}

Roguelike::~Roguelike()																						
{
	// nothing to destroy
}


void Roguelike::Initialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("Roguelike"));					
	GAME_ENGINE->RunGameLoop(true);		
	
	// Set the optional values
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);

	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (TCHAR) VK_LEFT;
	//buffer << (TCHAR) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void Roguelike::Start()
{
	// Insert the code that needs to be executed at the start of the game
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	try {
		m_pDungeon = new Dungeon{ /*GAME_ENGINE->GetWidth()*/1000, /*GAME_ENGINE->GetHeight()*/800, 75, 250};
	}
	catch (const IncorrectInput& e)
	{
		m_ErrorMsg = e.GetExceptionMessage();
	}

	//m_Maze.GenerateMaze();
}

void Roguelike::End()
{
	// Insert the code that needs to be executed at the closing of the game
	delete m_pDungeon;
}

void Roguelike::Paint(RECT rect)
{
	GAME_ENGINE->SetColor(RGB(255, 0, 0));
	GAME_ENGINE->DrawString(m_ErrorMsg.c_str(), 50, 50);


	GAME_ENGINE->SetColor(RGB(255, 255, 255));
	PaintDungeon(m_pDungeon->GetBSP());


	for (auto& room : m_pDungeon->GetRooms())
	{
		GAME_ENGINE->FillRect(room.x, room.y, room.width, room.height);
	}

	//int x{ GAME_ENGINE->GetWidth() / 2 - (m_Maze.GetColumns() / 2) * m_MazeCellSize };
	//int y{ GAME_ENGINE->GetHeight() / 2 - (m_Maze.GetRows() / 2) * m_MazeCellSize };
	//for (int rowidx{}; rowidx < m_Maze.GetRows(); ++rowidx)
	//{
	//	for (int colidx{}; colidx < m_Maze.GetColumns(); ++colidx)
	//	{
	//		GAME_ENGINE->DrawRect(x + m_MazeCellSize * colidx, y + m_MazeCellSize * rowidx, m_MazeCellSize, m_MazeCellSize);
	//	if(m_Maze.GetGridValue(colidx,rowidx) == 1) GAME_ENGINE->FillRect(x + m_MazeCellSize * colidx, y + m_MazeCellSize * rowidx, m_MazeCellSize, m_MazeCellSize);
	//	}
	//}
}

void Roguelike::Tick()
{
	// Insert non-paint code that needs to be executed each tick 
}

void Roguelike::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the game registers a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{	
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
}

void Roguelike::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void Roguelike::MouseMove(int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the mouse pointer moves across the game window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox(_T("Da mouse wuz here."));
		}
	}
	*/
}

void Roguelike::CheckKeyboard()
{	
	// Here you can check if a key of choice is held down
	// Is executed once per frame if the Game Loop is running 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void Roguelike::KeyPressed(TCHAR cKey)
{	
	// DO NOT FORGET to use SetKeyList() !!

	// Insert the code that needs to be executed when a key of choice is pressed
	// Is executed as soon as the key is released
	// You first need to specify the keys that the game engine needs to watch by using the SetKeyList() method

	/* Example:
	switch (cKey)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox(_T("Moving left."));
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox(_T("Moving down."));
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox(_T("Moving right."));
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox(_T("Moving up."));
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox(_T("Escape menu."));
	}
	*/
}

void Roguelike::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
}

void Roguelike::PaintDungeon(Node* node)
{
	if (node)
	{
		if (node->hasChild == true) {
			PaintDungeon(node->left);
			PaintDungeon(node->right);
		}
		else
		{
			GAME_ENGINE->DrawRect(node->topLeft.first, node->topLeft.second, node->dimension.first, node->dimension.second);
		}
	}
}




