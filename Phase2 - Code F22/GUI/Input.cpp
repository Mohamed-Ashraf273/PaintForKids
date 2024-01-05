#include "Input.h"
#include "Output.h"

int h = 0;
Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
void Input::ClearDrawToolBar() const
{
	h = 0;
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(UI.MenuItemWidth * PLAY_ITM_COUNT, 0, UI.width, UI.ToolBarHeight);

}
void Input::Display_colors()const
{
	h = 1;
	string MenuItemImages[6];
	MenuItemImages[0] = "images\\MenuItems\\red.jpg";
	MenuItemImages[1] = "images\\MenuItems\\blue.jpg";
	MenuItemImages[2] = "images\\MenuItems\\yellow.jpg";
	MenuItemImages[3] = "images\\MenuItems\\green.jpg";
	MenuItemImages[4] = "images\\MenuItems\\orange.jpg";
	MenuItemImages[5] = "images\\MenuItems\\black.jpg";
	for (int i = 0; i < 6; i++)
		pWind->DrawImage(MenuItemImages[i], (i + 5) * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_SQUARE:return DRAW_SQUARE;
			case ITM_CIRC:return DRAW_CIRCLE;
			case ITM_HEXA:return DRAW_HEXA;
			case ITM_TRI:return DRAW_TRI;
			case ITM_FRAM:return C_FRAM;
			case ITM_RED:return C_RED;
			case ITM_BLUE:return C_BLUE;
			case ITM_YELLOW:return C_YELLOW;
			case ITM_GREEN:return C_GREEN;
			case ITM_ORANGE:return C_ORANGE;
			case ITM_BLACK:return C_BLACK;
			case ITM_SELECT:return TO_SELECT;
			case ITM_MOVE:return TO_MOVE;
			case ITM_SAVE:return TO_SAVE;
			case ITM_CLEAN:return TO_CLEAN;
			case ITM_START:return TO_START;
			case ITM_PLAY_RECORD:return TO_PLAY_RECORD;
			case ITM_STOP:return TO_STOP;
			case ITM_UNDO:return TO_UNDO;
			case ITM_REDO:return TO_REDO;
			case ITM_LOAD:return TO_LOAD;
			case ITM_EXIT: return EXIT;
			case ITM_PLAY:return TO_PLAY;
			case ITM_DELETE:return TO_DELETE;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_HIDE:return TO_HIDE;
			case ITM_PICK:return TO_PICK;
			case ITM_DRAW:return TO_DRAW;
			case ITM_RED:if (h) return C_RED; break;
			case ITM_BLUE:if (h) return C_BLUE; break;
			case ITM_YELLOW:if (h) return C_YELLOW; break;
			case ITM_GREEN:if (h) return C_GREEN; break;
			case ITM_ORANGE:if (h) return C_ORANGE; break;
			case ITM_BLACK:if (h) return C_BLACK; break;
			case ITM_PICK_COLOR:return TO_PICK_COLOR;
			case ITM_PICK_COLORED_FIGURE:return TO_PICK_COLORED_FIGURE;
			}

		}

		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		if (x >= UI.MenuItemWidth * PLAY_ITM_COUNT && y <= UI.ToolBarHeight)
		{
			return DRAWINGTOOLBAR;
		}
		else
		{
			if (y > UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight))
			{
				return DRAWING_AREA;
			}
			else
			{
				return STATUS;	//just for now. This should be updated
			}
		}
	}

}
/////////////////////////////////

Input::~Input()
{
}
