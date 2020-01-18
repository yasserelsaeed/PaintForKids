#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
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
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case ITM_PALETTE: if(x<ITM_PALETTE*UI.MenuItemWidth+UI.MenuItemWidth/5)
							  {return COLOR_BLACK;}
							  else if(x<ITM_PALETTE*UI.MenuItemWidth+UI.MenuItemWidth*2/5)
							  {return COLOR_WHITE;}
							  else if(x<ITM_PALETTE*UI.MenuItemWidth+UI.MenuItemWidth*3/5)
							  {return COLOR_RED;}
							  else if(x<ITM_PALETTE*UI.MenuItemWidth+UI.MenuItemWidth*4/5)
							  {return COLOR_GREEN;}
							  else 
							  {return COLOR_BLUE;}
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_TRI: return DRAW_TRI;
			case ITM_LINE: return DRAW_LINE;
			case ITM_CHANGECDC: return CHNG_C_DRAW_CLR;
			case ITM_CHANGECFC: return CHNG_C_FILL_CLR;
			case ITM_SELECT: return SELECT;
			case ITM_SAVEGRAPH: return SAVE;
			case ITM_LOADGRAPH: return LOAD;
			case SITM_CHANGEFIGDC: return RESIZE;
			case STIM_CHANGEFIGFC: if(x<STIM_CHANGEFIGFC*UI.MenuItemWidth+UI.MenuItemWidth/2)
							  {return BRING_BACK;}
							  else 
							  {return SEND_FRONT;}
			case SITM_DELFIG: return DEL;
			case SITM_CPYFIG: return COPY;
			case SITM_CUTFIG: return CUT;
			case SITM_PSTFIG: return PASTE;
			case ITM_SWITCHPM: return TO_PLAY;
			case ITM_EXITD: return EXIT;

			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_COLOUR: return PICK_COLOUR;
			case ITM_SHAPE: return PICK_SHAPE;
			case ITM_BOTH: return PICK_BOTH;
			case ITM_RESTART: return RESTART;
			case ITM_SWITCHDM: return TO_DRAW;
			case ITM_EXITP: return EXIT;
			default:EMPTY;
			}
		}		
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
			//just for now. This should be updated
		if (y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
